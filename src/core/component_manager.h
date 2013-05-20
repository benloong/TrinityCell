//
//  component_manager.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-19.
//
//

#ifndef __TrinityCell__component_manager__
#define __TrinityCell__component_manager__

#include <map>
#include <memory>
#include "instance_pool.h"

#include "entity.h"

#include "component_types.h"


typedef int component_id_t;

class ComponentManager {
    InstancePool<entity_id_t, 1 << 16>          entity_pool;
    std::map<int, std::unique_ptr<PoolBase> >   component_instance_pools;
    
    std::map<entity_id_t, std::map<component_id_t, handle_t>> componentByEnt;
    std::map<entity_id_t, component_id_t>   transformByEnt;
    
    
public:
    
    template<typename _Type>
    typename ComponentTraits<_Type>::pool_type* getComponentInstancePool()
    {
        typename ComponentTraits<_Type>::pool_type *pool = static_cast<typename ComponentTraits<_Type>::pool_type*> (component_instance_pools[_Type::id].get());
        if(pool == nullptr)
        {
            pool = new typename ComponentTraits<_Type>::pool_type();
            component_instance_pools[_Type::id].reset(pool);
        }
        return pool;
    }
    
    template<typename _Type>
    handle_t addComponent(entity_id_t ent)
    {
        typedef InstancePool<_Type, _Type::MAX_COUNT> CompInstancePool;
        CompInstancePool * pool = getComponentInstancePool<_Type>();
        handle_t h = pool->allocate();
        _Type * comp = pool->resolve(h);
        if(comp != nullptr) {
            comp->ent = ent;
            comp->init(ent);
        }
        return h;
    }
    
    template<typename _Type>
    void  destroyComponent(handle_t h)
    {
        typedef InstancePool<_Type, _Type::MAX_COUNT> CompInstancePool;
        CompInstancePool *pool = static_cast<CompInstancePool*> (component_instance_pools[_Type::id]);
        _Type* comp = pool->resolve(h);
        assert(comp != nullptr && "try to destroy an invalid handle.");
        comp->uninit();
        component_instance_pools[_Type::id]->free(h);
    }
    
    template<typename _Type>
    _Type* resolveHandle(handle_t h)
    {
        typedef InstancePool<_Type, _Type::MAX_COUNT> CompInstancePool;
        CompInstancePool *pool = static_cast<CompInstancePool*> (component_instance_pools[_Type::id].get());
        assert(pool != nullptr && "not register component");
        return pool->resolve(h);
    }
    
    template<typename _Type>
    _Type* getComponent(entity_id_t ent)
    {
        typedef InstancePool<_Type, _Type::MAX_COUNT> CompInstancePool;
        CompInstancePool *pool = static_cast<CompInstancePool*> (component_instance_pools[_Type::id]);
        
        _Type* data = pool->data();
        for(auto it = pool->allocated.begin(); it != pool->allocated.end(); it++ )
        {
            if( data[it->idx].ent == ent) {
                return &data[it->idx];
            }
        }
        return nullptr;
    }
    
};

#endif /* defined(__TrinityCell__component_manager__) */
