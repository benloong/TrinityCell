//
//  component_roster_base.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-16.
//
//

#ifndef TrinityCell_component_roster_base_h
#define TrinityCell_component_roster_base_h

#include "fixed_size_pool.h"

//on roster per concrete component
struct ComponentManagerBase
{
    
};

template<typename CompType, uint32_t RosterMaxSize>
struct ComponentManagerBaseT : public ComponentManagerBase
{
    static const uint16_t id;
    
    ComponentManagerBaseT()
    {
        reset();
    }
    void reset()
    {
        _count = 0;
        _pool.reset();
    }
    
    Handle create()
    {
        Handle h = _pool.allocate();
        do {
            if(h == invalid_handle)
                break;
            _nodes[_count] = h;
            ++_count;
        } while (0);
        
        return h;
    }
    void   destroy(Handle handle)
    {
        uint32_t idx = handle.idx;
        _nodes[idx] = _nodes[--_count];
        _pool.free(handle);
    }
    
    CompType* get(Handle handle)
    {
        return _pool.resolve(handle);
    }
    typedef FixedSizePool<CompType, RosterMaxSize> CompPool;
    
    Handle          _nodes[RosterMaxSize];
    uint32_t        _count; // current used count;
    CompPool        _pool;
};

#endif
