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

namespace DCS {
    
    class ComponentManager {
        InstancePool<entity_id_t, 1 << 16>      entity_pool;            
        std::map<int, std::unique_ptr<Pool> >  component_instance_pools;
        
    public:
        
        template<typename _Type>
        handle_t addComponent(entity_id_t ent)
        {
            typedef typename InstancePool<_Type, _Type::MAX_COUNT> CompInstancePool;
            CompInstancePool * pool = static_cast<CompInstancePool*> (component_instance_pools[_Type::id].get());
            if(pool == nullptr) 
            {
                pool = new CompInstancePool();
                component_instance_pools[_Type::id].reset(pool);
            }
            handle_t h = pool->allocate();
            _Type * comp = pool->resolve(h);
            if(comp != nullptr)
                comp->init(ent);
            return h;
        }
        
        template<typename _Type>
        void  destroyComponent(handle_t h)
        {
            typedef typename InstancePool<_Type, _Type::MAX_COUNT> CompInstancPool;
            CompInstancPool *pool = static_cast<CompInstancePool*> (component_instance_pools[_Type::id]);
            _Type* comp = pool->resolve(h);
            assert(comp != nullptr && "try to destroy an invalid handle.");
            comp->uninit();
            component_instance_pools[_Type::id]->free(h);
        }
        
    };
    
}

#endif /* defined(__TrinityCell__component_manager__) */
