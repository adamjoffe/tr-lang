#ifndef BI_FUNC_DECL_H
#define BI_FUNC_DECL_H

#include <functional>
#include <string>
#include <tuple>
#include <vector>

// have to include required parts, as won't be included as part of regular AST
#include "ast_callable.h"

// error functions
#include "../exe-components/tr_runtime_exception.h"

namespace TR {

    /**
     * C++11 std::integer_sequence Implementation
     *  SOURCE:
     *      https://blog.galowicz.de/2016/06/24/integer_sequences_at_compile_time/
     */
    template <int ... Ns> struct sequence {};

    // First define the template signature
    template <int ... Ns> struct seq_gen;

    // Recursion case
    template <int I, int ... Ns>
    struct seq_gen<I, Ns...>
    {
        // Take front most number of sequence,
        // decrement it, and prepend it twice.
        // First I - 1 goes into the counter,
        // Second I - 1 goes into the sequence.
        using type = typename seq_gen<
                I - 1, I - 1, Ns...>::type;
    };

    // Recursion abort
    template <int ... Ns>
    struct seq_gen<0, Ns...>
    {
        using type = sequence<Ns...>;
    };

    template <int N>
    using sequence_t = typename seq_gen<N>::type;
    /**---------------------------------**/

    /** Argument Extractor Templates **/
    // all declared inline, since specializations no longer templates
    // Built in functions can be fully coerced to behave similar to TR functions
    template<typename T>
    inline T getVal(GVar* arg) {
        throw TR_Runtime_Exception("Non valid TR lang argument type");
    }

    template<>
    inline int getVal<int>(GVar* arg) {
        if (IntVar* ivar = dynamic_cast<IntVar*>(arg)) {
            return ivar->val;
        } else {
            throw TR_Runtime_Exception("Argument type doesn't match: int expected but got " + TypeToString(arg));
        }
    }

    // allow floats for built-in function args by casting
    template<>
    inline float getVal<float>(GVar* arg) {
        if (DoubleVar* dvar = dynamic_cast<DoubleVar*>(arg)) {
            return static_cast<float>(dvar->val);
        } else if (IntVar* ivar = dynamic_cast<IntVar*>(arg)) {
            return static_cast<float>(ivar->val);    
        } else {
            throw TR_Runtime_Exception("Argument type doesn't match: float expected but got " + TypeToString(arg));
        }
    }

    template<>
    inline double getVal<double>(GVar* arg) {
        if (DoubleVar* dvar = dynamic_cast<DoubleVar*>(arg)) {
            return dvar->val;
        } else if (IntVar* ivar = dynamic_cast<IntVar*>(arg)) {
            return static_cast<double>(ivar->val); // can be cast to double from int
        } else {
            throw TR_Runtime_Exception("Argument type doesn't match: double expected but got " + TypeToString(arg));
        }
    }

    template<>
    inline std::string getVal<std::string>(GVar* arg) {
        if (StringVar* svar = dynamic_cast<StringVar*>(arg)) {
            return svar->val;
        } else if (IntVar* ivar = dynamic_cast<IntVar*>(arg)) {
            return std::to_string(ivar->val);
        } else if (DoubleVar* dvar = dynamic_cast<DoubleVar*>(arg)) {
            return std::to_string(dvar->val);
        } else if (BoolVar* bvar = dynamic_cast<BoolVar*>(arg)) {
            return std::to_string(bvar->val);
        } else if (VectorVar* vvar = dynamic_cast<VectorVar*>(arg)) {
            return static_cast<std::string>(vvar->val);
        } else {
            throw TR_Runtime_Exception("Argument type doesn't match: string expected but got " + TypeToString(arg));
        }
    }

    template<>
    inline bool getVal<bool>(GVar* arg) {
        if (BoolVar* bvar = dynamic_cast<BoolVar*>(arg)) {
            return bvar->val;
        } else {
            throw TR_Runtime_Exception("Argument type doesn't match: bool expected but got " + TypeToString(arg));
        }
    }

    template<>
    inline Vector getVal<Vector>(GVar* arg) {
        if (VectorVar* vvar = dynamic_cast<VectorVar*>(arg)) {
            return vvar->val;
        } else {
            throw TR_Runtime_Exception("Argument type doesn't match: Vector expected but got " + TypeToString(arg));
        }
    }

    /**
     * Built-in Function Declaration Class
     *
     * Function declaration node for built-in functions. Since
     * built-in function types are statically checked due to
     * being in C++, while TR functions are dynamically typed
     * so we need to have 2 different declaration AST nodes.
     * Also the method of calling built-in functions vs TR
     * functions is different.
     */
    template<typename>
    class BIFuncDecl;

    /** Generic Template Case **/
    template<typename R, typename... Args>
    class BIFuncDecl<R(Args...)> : public ASTCallable {
    private:
        // dummy type parameter for member specialization overloads
        // See:
        //      https://stackoverflow.com/questions/5512910/explicit-specialization-of-template-class-member-function
        template<typename T> struct spec_type {};
    public:

        /// Remove default constructor for this
        BIFuncDecl() = delete;

        /**
         * Single node constructor
         *
         * Constructs single AST node with no child or parents
         *
         * @param idAST ASTTerminal child of this node (should be type Ident)
         * @param ty Type enum of the return type
         * @param func Function pointer to callable C++ function
         */
        BIFuncDecl(ASTTerminal* idAST, std::function<R(Args...)> func) :
                callable(func),
                ASTCallable(idAST, DeclType::BIFUNC_DECL, location(), std::string()){
            t = TypeToEnum<R>::value; // done after ASTDecl init, cause it sets it to null
            if (t == Type::NULL_T) {
                throw std::runtime_error("Invalid return type used for built-in: " + (dynamic_cast<Ident*>(idAST))->name);
            } else if (t == Type::FLOAT_T) {
                t = Type::DOUBLE_T; // change float to double, since it will be cast by default
            }
            arity = sizeof...(Args);
            idAST->parent = this;
            unwrapParamType(sequence_t<sizeof...(Args)>{});
        }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete C++ reference, as assumed
         * it's done by C++
         */
        virtual ~BIFuncDecl() {}

        /**
         * Visit Function
         *
         * Calls the abstracted visitor function
         * See Visitor Pattern
         *
         * @param v Pointer to the visitor object
         * @param n Optional pointer to AST node
         * @return Optionally returns a pointer to an AST node
         */
        virtual ASTNode* visit(Visitor* v, ASTNode* n) {
            // Should never be visited
            throw TR_Runtime_Exception("This error shouldn't occur!");
        }

        /**
         * Type conversion of a single parameter
         *
         * Converts the C++ type of a single parameter to Type enum
         *
         * @tparam N Compile time index of parameter to convert
         * @return Type enum of parameter equivalent
         *
         * TODO: Potentially replace std::tuple_element method with one from here
         * TODO: https://ldionne.com/2015/11/29/efficient-parameter-pack-indexing/
         */
        template<std::size_t N>
        Type convertParamType() {
            return TypeToEnum<
                    typename std::tuple_element<
                            N,std::tuple<Args...>
                    >::type
            >::value;
        }

        /**
         * Unwrap C++ Function Parameters
         *
         * Unwraps the function parameter pack and converts C++ types to
         * Type enum and stores it as member data array
         *
         * @tparam IDX Compile time number sequence
         */
        template<int... IDX>
        void unwrapParamType(sequence<IDX...>) {
            Type param_types_[] = { convertParamType<IDX>()... };
            for(int i = 0; i < arity; ++i) {
                param_types[i] = param_types_[i];
            }
        }

        /** Call Wrappers **/
        /**
         * Converts argument vector into C++ parameter pack and builds correct return value
         *
         * @param spec_type Overload parameter for type based on return value
         * @param args Vector of pointers to Generic Variable arguments
         * @tparam T Return type of built-in function
         * @tparam IDX Compile time index sequence for arguments
         *
         */
        // Overload member function specialisation
        template<typename T, int... IDX>
        GVar* call_(spec_type<T> st, std::vector<GVar*>& args, sequence<IDX...>) {
            return new GVar();
        }

        /** int return value **/
        template<int... IDX>
        GVar* call_(spec_type<int> st, std::vector<GVar*>& args, sequence<IDX...>) {
            return new IntVar(callable( getVal<typename std::tuple_element<IDX,std::tuple<Args...>>::type>(args[IDX])... ));
        }

        /** float return value **/
        // allow float by casting return to a double
        template<int... IDX>
        GVar* call_(spec_type<float> st, std::vector<GVar*>& args, sequence<IDX...>) {
            return new DoubleVar(callable( getVal<typename std::tuple_element<IDX,std::tuple<Args...>>::type>(args[IDX])... ));
        }

        /** double return value **/
        template<int... IDX>
        GVar* call_(spec_type<double> st, std::vector<GVar*>& args, sequence<IDX...>) {
            return new DoubleVar(callable( getVal<typename std::tuple_element<IDX,std::tuple<Args...>>::type>(args[IDX])... ));
        }

        /** std::string return value **/
        template<int... IDX>
        GVar* call_(spec_type<std::string> st, std::vector<GVar*>& args, sequence<IDX...>) {
            return new StringVar(callable( getVal<typename std::tuple_element<IDX,std::tuple<Args...>>::type>(args[IDX])... ));
        }

        /** bool return value **/
        template<int... IDX>
        GVar* call_(spec_type<bool> st, std::vector<GVar*>& args, sequence<IDX...>) {
            return new BoolVar(callable( getVal<typename std::tuple_element<IDX,std::tuple<Args...>>::type>(args[IDX])... ));
        }

        /** void return value **/
        template<int... IDX>
        GVar* call_(spec_type<void> st, std::vector<GVar*>& args, sequence<IDX...>) {
            callable( getVal<typename std::tuple_element<IDX,std::tuple<Args...>>::type>(args[IDX])... );
            return new GVar(Type::VOID_T);
        }

        /** Vector return value **/
        template<int... IDX>
        GVar* call_(spec_type<Vector> st, std::vector<GVar*>& args, sequence<IDX...>) {
            return new VectorVar(callable( getVal<typename std::tuple_element<IDX,std::tuple<Args...>>::type>(args[IDX])... ));
        }

        /**
         * FCallable Override Function
         *
         * @param v Visitor passed to call to walk tree
         * @param n Reference to the FCall node that called
         * @throws ReturnV Return value object of callable
         */
        void call(Visitor* v, ASTNode* n) {
            FCall* caller = dynamic_cast<FCall*>(n);
            throw ReturnV(call_(spec_type<R>(), caller->pass_args, sequence_t<sizeof...(Args)>{}));
        }

        std::function<R(Args...)> callable;
        Type param_types[sizeof...(Args)];
    };

}

#endif