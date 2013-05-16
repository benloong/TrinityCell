//
//  hierarchy.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-16.
//
//

#ifndef __TrinityCell__hierarchy__
#define __TrinityCell__hierarchy__

#include "fixed_size_pool.h"
#include "component_detail.h"
#include "component_roster_base.h"

namespace cell {
    
    struct Transform : public ComponentBaseT<Transform>
    {
        uint16_t parent;
        uint16_t first_child;
        uint16_t prev_sibling;
        uint16_t next_sibling;
        uint16_t level;
        uint16_t bitmask; // update bit mask
        
        float  position[3];
        float  scale[3];
        float  rotation[4];
        
        float  world_mat[16];
        float  local_mat[16];
    };
    
    class TransformHierarchy : public ComponentManagerBaseT<Transform, 1<<16>
    {
        enum {
            MAX_COUNT = 1<<16
        };
    public:
        template<typename StreamType>
        void serialize(StreamType & bitstream);
        template<typename StreamType>
        void deserialize(const StreamType & bitstream);
        
        void    setParent(Handle handle, Handle parent);
        Handle  root(Handle handle);
        
        void    destroyTransform(Handle trans);
    };
}
#endif /* defined(__TrinityCell__hierarchy__) */
