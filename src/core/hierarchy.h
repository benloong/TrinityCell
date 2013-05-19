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
#include <iostream>

namespace cell {
    
    class TransformHierarchy;
    struct Transform : public ComponentBaseT<TransformHierarchy>
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
    
    class TransformHierarchy : public ComponentManagerBaseT<Transform, 1<<16 >
    {
    public:
        template<typename OutStreameType>
        void serialize(OutStreameType & bitstream);
        template<typename InStreamType>
        void deserialize(const InStreamType & bitstream);
        
        void    setParent(HandleType handle, HandleType parent = invalid_handle);
        HandleType  root(HandleType handle);
        
        void    destroyTransform(HandleType trans);
        
        void    update();
    };

    template <typename OutStreameType>
    void TransformHierarchy::serialize(OutStreameType& out_stream)
    {
        out_stream.write(&_pool, sizeof(_pool));
    }

    template <typename InStreamType>
    void TransformHierarchy::deserialize(const InStreamType & instream)
    {
        instream.read(&_pool, sizeof(_pool));
    }
}
#endif /* defined(__TrinityCell__hierarchy__) */
