#include "tr_types.h"

namespace TR {

	// Construtor Definitions
	DoubleVar::DoubleVar(const IntVar& obj) : DoubleVar(static_cast<double>(obj.val)) {}

	StringVar::StringVar(const IntVar& obj) : StringVar(std::to_string(obj.val)) {}
	StringVar::StringVar(const DoubleVar& obj) : StringVar(std::to_string(obj.val)) {}
	StringVar::StringVar(const BoolVar& obj): StringVar(std::string(obj.val ? "true" : "false")) {}

	StringVar::StringVar(const VectorVar& obj) : StringVar(static_cast<std::string>(obj.val)) {}

	std::string TypeToString(const Type t) {
	    std::string s;
	    switch(t) {
	        case Type::INT_T:
	            s = "int";
	            break;
            case Type::FLOAT_T:
                s = "float";
                break;
	        case Type::DOUBLE_T:
	            s = "double";
	            break;
	        case Type::STRING_T:
	            s = "string";
	            break;
	        case Type::BOOL_T:
	            s = "bool";
	            break;
	        case Type::VOID_T:
	            s = "void";
	            break;
	        case Type::VECTOR_T:
	            s = "vector";
	            break;
            case Type::NULL_T:
                s = "null";
                break;
	        default:
                throw std::runtime_error("Unknown type during \'TypeToString\'");
	    }
	    return s;
	}

	std::string TypeToString(const GVar* v) {
	    return TypeToString(v->t);
	}	

    std::string ValToString(const GVar* v) {
        if (const IntVar* ivar = dynamic_cast<const IntVar*>(v)) {
            return std::to_string(ivar->val);
        } else if (const DoubleVar* dvar = dynamic_cast<const DoubleVar*>(v)) {
            return std::to_string(dvar->val);
        } else if (const BoolVar* bvar = dynamic_cast<const BoolVar*>(v)) {
            return std::to_string(bvar->val);
        } else if (const StringVar* svar = dynamic_cast<const StringVar*>(v)) {
            return "'" + svar->val + "'";
        } else if (const VectorVar* vvar = dynamic_cast<const VectorVar*>(v)) {
            return static_cast<std::string>(vvar->val);
        } else {
            throw std::runtime_error("Unknown type during \'ValToString\'");
        }
    }

    GVar* MakeCopy(const GVar* src) {
        if (src->t == Type::NULL_T || src->t == Type::VOID_T) {
            return nullptr;
        } else {
            GVar* tmp;
            if (src->t == Type::INT_T) {
                tmp = new IntVar(*dynamic_cast<const IntVar*>(src));
            } else if (src->t == Type::DOUBLE_T) {
                tmp = new DoubleVar(*dynamic_cast<const DoubleVar*>(src));
            } else if (src->t == Type::BOOL_T) {
                tmp = new BoolVar(*dynamic_cast<const BoolVar*>(src));
            } else if (src->t == Type::STRING_T) {
                tmp = new StringVar(*dynamic_cast<const StringVar*>(src));
            } else if (src->t == Type::VECTOR_T) {
                tmp = new VectorVar(*dynamic_cast<const VectorVar*>(src));
            } else {
                throw std::runtime_error("Unknown type during \'SetValue\'");
            }
            return tmp;
        }
    }
	
    std::pair<GVar*,GVar*> doCoercion(const GVar* a, const GVar* b, bool conv_to_string) {
        GVar* reta = nullptr; //new GVar(); // has to be a null var
        GVar* retb = nullptr; //new GVar(); // has to be a null var

        // check for same type
        if (a->t == b->t) {
            reta = MakeCopy(a);
            retb = MakeCopy(b);

        // int to double
        } else if (a->t == Type::INT_T && b->t == Type::DOUBLE_T) {
            reta = new DoubleVar(*dynamic_cast<const IntVar*>(a));
            retb = new DoubleVar(*dynamic_cast<const DoubleVar*>(b));
        } else if (a->t == Type::DOUBLE_T && b->t == Type::INT_T) {
            reta = new DoubleVar(*dynamic_cast<const DoubleVar*>(a));
            retb = new DoubleVar(*dynamic_cast<const IntVar*>(b));

        // int to string
        } else if (conv_to_string && a->t == Type::INT_T && b->t == Type::STRING_T) {
            reta = new StringVar(*dynamic_cast<const IntVar*>(a));
            retb = new StringVar(*dynamic_cast<const StringVar*>(b));
        } else if (conv_to_string && a->t == Type::STRING_T && b->t == Type::INT_T) {
            reta = new StringVar(*dynamic_cast<const StringVar*>(a));
            retb = new StringVar(*dynamic_cast<const IntVar*>(b));

        // double to string
        } else if (conv_to_string && a->t == Type::DOUBLE_T && b->t == Type::STRING_T) {
            reta = new StringVar(*dynamic_cast<const DoubleVar*>(a));
            retb = new StringVar(*dynamic_cast<const StringVar*>(b));
        } else if (conv_to_string && a->t == Type::STRING_T && b->t == Type::DOUBLE_T) {
            reta = new StringVar(*dynamic_cast<const StringVar*>(a));
            retb = new StringVar(*dynamic_cast<const DoubleVar*>(b));

        // bool to string
        } else if (conv_to_string && a->t == Type::BOOL_T && b->t == Type::STRING_T) {
            reta = new StringVar(*dynamic_cast<const BoolVar*>(a));
            retb = new StringVar(*dynamic_cast<const StringVar*>(b));
        } else if (conv_to_string && a->t == Type::STRING_T && b->t == Type::BOOL_T) {
            reta = new StringVar(*dynamic_cast<const StringVar *>(a));
            retb = new StringVar(*dynamic_cast<const BoolVar *>(b));

        // Vector to string
        } else if (conv_to_string && a->t == Type::VECTOR_T && b->t == Type::STRING_T) {
            reta = new StringVar(*dynamic_cast<const VectorVar*>(a));
            retb = new StringVar(*dynamic_cast<const StringVar*>(b));
        } else if (conv_to_string && a->t == Type::STRING_T && b->t == Type::VECTOR_T) {
            reta = new StringVar(*dynamic_cast<const StringVar*>(a));
            retb = new StringVar(*dynamic_cast<const VectorVar*>(b));
        }

        // check if failed coercion
        if (reta == nullptr && retb == nullptr) {
            reta = new GVar();
            retb = new GVar();
        }

        return std::make_pair(reta, retb);
    }
}

