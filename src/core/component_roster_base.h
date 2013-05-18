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

//on manager per concrete component type
struct ComponentManagerBase
{
    virtual ~ComponentManagerBase() {}
};

template<typename Type, uint32_t RosterMaxSize>
struct ComponentManagerBaseT : public ComponentManagerBase
{
    static const uint16_t id;
    typedef Type CompType;
    typedef FixedSizePool<CompType, RosterMaxSize> CompPool;
    typedef typename FixedSizePool<CompType, RosterMaxSize>::Handle HandleType;

    ComponentManagerBaseT()
    {
        reset();
    }
    
    void reset()
    {
        _count = 0;
        _pool.reset();
    }
    
    HandleType create(uint32_t ent)
    {
        HandleType h = _pool.allocate();
        do {
            if(h == invalid_handle)
                break;
            _nodes[_count] = h;
            ++_count;
            _pool.data()[h.idx]._ent_id = ent;
        } while (0);
        
        return h;
    }
    
    void destroy(HandleType handle)
    {
        uint32_t idx = handle.idx;
        _nodes[idx] = _nodes[--_count];
        _pool.free(handle);
    }
    
    const CompType* get(HandleType handle)
    {
        return _pool.resolve(handle);
    }
    
    //need cache
    const CompType* getComponent(uint32_t ent)
    {
        const CompType * data = _pool.data();
        for (uint32_t i = 0; i < _count; ++i) {
            if (data[_nodes[i].idx]._ent_id == ent) {
                return &data[_nodes[i].idx];
            }
        }
        return nullptr;
    }
    
    void update()
    {
        
    }
    
    HandleType      _nodes[RosterMaxSize];
    uint32_t        _count; // current used count;
    CompPool        _pool;
};

#endif
