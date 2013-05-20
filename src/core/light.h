//
//  light.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-20.
//
//

#ifndef __TrinityCell__light__
#define __TrinityCell__light__

#include "component.h"

class Light : public DCS::Component_T<Light, 4096>
{
public:
    enum Type{
        DIRECTIONAL,
        SPOT,
        POINT
    };
    float  color[3];
    float  dir[3];
    Type   type;
    float  intensity;
    float  range;
    float  spotRange;
    int    cullingMask;
    
    bool   enabled;
};

#endif /* defined(__TrinityCell__light__) */
