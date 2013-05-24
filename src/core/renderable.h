//
//  renderable.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-20.
//
//

#ifndef __TrinityCell__renderable__
#define __TrinityCell__renderable__

#include "cmp_base.h"

struct Renderable : public cmp_base {
    enum {
        ID = E_CType::CT_Renderable,
        MAX_COUNT = 12
    };
    bool  enabled;
    int   materialId;
    int   meshId;
    
    float  bounds[6];
};

#endif /* defined(__TrinityCell__renderable__) */
