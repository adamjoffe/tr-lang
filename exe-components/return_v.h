#ifndef RETURN_V_H
#define RETURN_V_H

#include "../tr_types.h"

namespace TR {

    /**
     * Struct to throw on callable evaluation
     */
    struct ReturnV {
    	ReturnV(GVar* v) : val(v) {}
        GVar* val;
    };

}

#endif