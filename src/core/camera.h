//
//  camera.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-19.
//
//

#ifndef __TrinityCell__camera__
#define __TrinityCell__camera__

#include "component.h"

//template<typename Comp_Type, uint32_t IndexBitWidth>
//const typename Component_T<Comp_Type, IndexBitWidth>::PoolType Component_T<Comp_Type, IndexBitWidth>::pool;
namespace  DCS {
    
    //max camera count set to 32, so we can use an int bit mask for culling
    struct Camera  : public Component_T<Camera, 32>
    {
        float  fov;
        float  far;
        float  near;
        float  enabled;
        float  aspect;
        
        float  clearColor[3];
        bool   orthographic;
    };

}
#endif /* defined(__TrinityCell__camera__) */
