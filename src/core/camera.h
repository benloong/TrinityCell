//
//  camera.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-19.
//
//

#ifndef __TrinityCell__camera__
#define __TrinityCell__camera__

#include "cmp_base.h"

    
//max camera count set to 32, so we can use an int bit mask for culling
struct Camera  : public cmp_base
{
    enum {
        ID = 12,
        MAX_COUNT = 32
    };
    
    float  fov;
    float  far;
    float  near;
    float  enabled;
    float  aspect;
    
    float  clearColor[3];
    bool   orthographic;
};
#endif /* defined(__TrinityCell__camera__) */
