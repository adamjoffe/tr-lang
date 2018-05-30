#ifndef TR_TYPES_H
#define TR_TYPES_H

#include <exception>
#include <stdexcept>
#include <string>
#include <utility>

#include "exe-components/tr_runtime_exception.h"

#include "user-customisation/vector_impl.h"

/// Default vector if non defined, DO NOT MODIFY
#ifndef VECTOR_IMPLEMENTATION
#include "libs/default_vector.h"
namespace TR {
    using Vector = DefaultVector;
}
#endif

namespace TR {

    /**
     * Enum of all supported TR value types
     *
     * NULL_T is used only when a variable or function doesn't exist
     */
    enum class Type { VOID_T, INT_T, DOUBLE_T, STRING_T, BOOL_T, VECTOR_T, NULL_T, 
                        // float only support for built-ins
                        FLOAT_T };

    /** Complete Generically Typed Variable **/
    class GVar {
    public:
        Type t;

        GVar() : t(Type::NULL_T) {}
        GVar(Type type) : t(type) {}
        GVar(const GVar& obj) : t(obj.t) {}
        virtual ~GVar() {}
    };

    // Forward declarations
    class IntVar;
    class DoubleVar;
    class StringVar;
    class BoolVar;
    class VectorVar;

    class IntVar : public GVar {
    public:
        int val;

        IntVar() : IntVar(0) {}
        IntVar(int v) : GVar(Type::INT_T), val(v) {}
        IntVar(const IntVar& obj) : GVar(obj), val(obj.val) {}
        // Copy coercion operations
    };

    class DoubleVar : public GVar {
    public:
        double val;

        DoubleVar() : DoubleVar(0.0) {}
        DoubleVar(double v) : GVar(Type::DOUBLE_T), val(v) {}
        DoubleVar(const DoubleVar& obj) : GVar(obj), val(obj.val) {}
        // Copy coercion operations
        DoubleVar(const IntVar& obj);
        // Float built-in allowance
        DoubleVar(float v) : DoubleVar(static_cast<double>(v)) {}
    };

    class BoolVar : public GVar {
    public:
        bool val;

        BoolVar() : BoolVar(false) {}
        BoolVar(bool v) : GVar(Type::BOOL_T), val(v) {}
        BoolVar(const BoolVar& obj) : GVar(obj), val(obj.val) {}
        // Copy coercion operations
    };

    class StringVar : public GVar {
    public:
        std::string val;

        StringVar() : StringVar(std::string("")) {}
        StringVar(std::string v) : GVar(Type::STRING_T), val(v) {}
        StringVar(const StringVar& obj) : GVar(obj), val(obj.val) {}
        // Copy coercion constructions
        StringVar(const IntVar& obj);
        StringVar(const DoubleVar& obj);
        StringVar(const BoolVar& obj);
        StringVar(const VectorVar& obj);
    };

    class VectorVar : public GVar {
    public:
        Vector val;

        VectorVar() : VectorVar(Vector()) {}
        VectorVar(Vector v) : GVar(Type::VECTOR_T), val(v) {}
        VectorVar(const VectorVar& obj) : GVar(obj), val(obj.val) {}
        // Copy coercion constructions
    };

    /** Type to String Printing **/
    std::string TypeToString(const Type t);

    /** Wrapper for Generic Type Printing **/
    std::string TypeToString(const GVar* v);

    /** Generic Var Val to String **/
    std::string ValToString(const GVar* v);

    /**
     * Helper SFINAE structs to convert C++ types to enums
     */
    template<typename T> // Catch all unknown type
    struct TypeToEnum {
        static const Type value = Type::NULL_T;
    };

    template<>
    struct TypeToEnum<void> {
        static const Type value = Type::VOID_T;
    };

    template<>
    struct TypeToEnum<int> {
        static const Type value = Type::INT_T;
    };

    template<>
    struct TypeToEnum<float> {
        static const Type value = Type::FLOAT_T;
    };

    template<>
    struct TypeToEnum<double> {
        static const Type value = Type::DOUBLE_T;
    };

    template<>
    struct TypeToEnum<std::string> {
        static const Type value = Type::STRING_T;
    };

    template<>
    struct TypeToEnum<bool> {
        static const Type value = Type::BOOL_T;
    };

    template<>
    struct TypeToEnum<Vector> {
        static const Type value = Type::VECTOR_T;
    };

    /**
     * Helper SFINAE structs to check if C++ type is a valid TR type
     */
    template<typename T>
    struct is_valid_TR_type {
        static const bool value = false;
    };

    template<>
    struct is_valid_TR_type<void> {
        static const bool value = true;
    };

    template<>
    struct is_valid_TR_type<int> {
        static const bool value = true;
    };

    template<>
    struct is_valid_TR_type<float> {
        static const bool value = true;
    };

    template<>
    struct is_valid_TR_type<double> {
        static const bool value = true;
    };

    template<>
    struct is_valid_TR_type<std::string> {
        static const bool value = true;
    };

    template<>
    struct is_valid_TR_type<bool> {
        static const bool value = true;
    };

    template<>
    struct is_valid_TR_type<Vector> {
        static const bool value = true;
    };

    /**
     * Helper SFINAE structs to get TR types as C++ types
     */
    // TODO: use this template in more places for easily getting a GVar value as type
    // when a runtime_error is acceptable
    template<typename T>
    inline T get_gvar_as(GVar* v) {
        throw TR_Runtime_Exception("Unknown type during \'get_as\'");
    }

    template<>
    inline int get_gvar_as<int>(GVar* v) {
        if (IntVar* ivar = dynamic_cast<IntVar*>(v)) {
            return ivar->val;
        } else {
            throw TR_Runtime_Exception("Argument type doesn't match: int expected but got " + TypeToString(v));
        }
    }

    template<>
    inline float get_gvar_as<float>(GVar* v) {
        if (DoubleVar* dvar = dynamic_cast<DoubleVar*>(v)) {
            return static_cast<float>(dvar->val);
        } else if (IntVar* ivar = dynamic_cast<IntVar*>(v)) {
            return static_cast<float>(ivar->val);    
        } else {
            throw TR_Runtime_Exception("Argument type doesn't match: float expected but got " + TypeToString(v));
        }
    }

    template<>
    inline double get_gvar_as<double>(GVar* v) {
        if (DoubleVar* dvar = dynamic_cast<DoubleVar*>(v)) {
            return dvar->val;
        } else if (IntVar* ivar = dynamic_cast<IntVar*>(v)) {
            return static_cast<double>(ivar->val); // can be cast to double from int
        } else {
            throw TR_Runtime_Exception("Argument type doesn't match: double expected but got " + TypeToString(v));
        }
    }

    template<>
    inline std::string get_gvar_as<std::string>(GVar* v) {
        if (StringVar* svar = dynamic_cast<StringVar*>(v)) {
            return svar->val;
        } else if (IntVar* ivar = dynamic_cast<IntVar*>(v)) {
            return std::to_string(ivar->val);
        } else if (DoubleVar* dvar = dynamic_cast<DoubleVar*>(v)) {
            return std::to_string(dvar->val);
        } else if (BoolVar* bvar = dynamic_cast<BoolVar*>(v)) {
            return std::to_string(bvar->val);
        } else if (VectorVar* vvar = dynamic_cast<VectorVar*>(v)) {
            return static_cast<std::string>(vvar->val);
        } else {
            throw TR_Runtime_Exception("Argument type doesn't match: string expected but got " + TypeToString(v));
        }
    }

    template<>
    inline bool get_gvar_as<bool>(GVar* v) {
        if (BoolVar* bvar = dynamic_cast<BoolVar*>(v)) {
            return bvar->val;
        } else {
            throw TR_Runtime_Exception("Argument type doesn't match: bool expected but got " + TypeToString(v));
        }
    }

    template<>
    inline Vector get_gvar_as<Vector>(GVar* v) {
        if (VectorVar* vvar = dynamic_cast<VectorVar*>(v)) {
            return vvar->val;
        } else {
            throw TR_Runtime_Exception("Argument type doesn't match: Vector expected but got " + TypeToString(v));
        }
    }
    
    /**
     * Make Copy
     *
     * Makes a copy of the GVar given, 
     * if type is void, null returns nullptr
     *
     * @param src Source GVar to set value from
     * @return Copy of GVar
     */
    GVar* MakeCopy(const GVar* src);

    /**
     * Type coercion
     *
     * Computes coercion between two Generic Variables and returns either a null value
     * if they are unable to be coerced to the same type, or two generic variables of the
     * same type that can then be operated on
     *
     * @param a First Generic Variable
     * @param b Second Generic Variable
     * @param conv_to_string Whether to allow implicit coercion to strings for this operation, default = false 
     * @return Pair of Generic Variables of same type or null type, if coercion unsuccessful
     */
    std::pair<GVar*,GVar*> doCoercion(const GVar* a, const GVar* b, bool conv_to_string = false);

}

#endif