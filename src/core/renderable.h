//
//  renderable.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-20.
//
//

#ifndef __TrinityCell__renderable__
#define __TrinityCell__renderable__

#include "component.h"

class Renderable : public DCS::Component_T<Renderable, 4096> {
    
    bool  enabled;
    int   materialId;
    int   meshId;
    
    float  bounds[6];
};

#endif /* defined(__TrinityCell__renderable__) */
