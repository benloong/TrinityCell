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
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include "types.h"
#include "instance_pool.h"
#include "component_types.h"


struct EntityInfo {
    entity_id_t id;
    char        name[32];
    std::map<cmp_id_t, handle_t> components;
    EntityInfo() : id(0)
    {
        memset(name, 0, 32);
    }
};

struct ComponentTypeBase {
    
    typedef void (*fn_free)(handle_t h);
    typedef handle_t (*fn_alloc)(entity_id_t ent);
    typedef void (*fn_update)();
};
//struct object_pool {
//    virtual ~object_pool () = 0;
//    virtual handle_t allocate(entity_id_t ent) = 0;
//    virtual void free(handle_t h) = 0;
//    virtual void update() = 0;
//};
//
//template <typename _Cmp_Tp, size_t _Size>
//class ComponentInstancePool : public object_pool {
//    typedef _Cmp_Tp DataType;
//    static_assert(_Size < 1<<16, "_Size out of index. _Size must be smaller than 65535.");
//    enum
//    {
//        MAX_COUNT = _Size
//    };
//    
//    struct Handle
//	{
//		handle_t idx : 16;
//        handle_t key : 16;
//        
//        inline operator int()
//        {
//            return idx << 16 | key;
//        }
//        
//        Handle(handle_t h) : idx(h>>16), key(h)
//        {
//        }
//        Handle(int idx, int key) : idx(idx) , key(key)
//        {
//        }
//    };
//            
//    std::array<DataType,MAX_COUNT>  data;
//
//    std::array<index_t, MAX_COUNT>  generations;// current slot generation  
//    std::array<index_t, MAX_COUNT>  indices;    // index to data pool
//    index_t                         next_index; // next index in indices
//
//public:
//    ComponentInstancePool()
//    {
//        for (int i = 0; i < MAX_COUNT; ++i)
//        {
//            indices[i] = i;
//        }
//    }
//    ~ComponentInstancePool()
//    {
//        
//    }
//    
//    handle_t allocate(entity_id_t ent)
//    {
//        if(next_index == MAX_COUNT)
//            return INVALID_HANDLE;
//    }
//    
//    void free(handle_t h)
//    {
//        
//    }
//    
//    void update()
//    {
//        
//    }
//};


class ComponentManager {
    entity_id_t  next_ent_id;
    std::map<cmp_id_t, std::unique_ptr<PoolBase> >   component_instance_pools;
    
    std::map<entity_id_t, std::map<cmp_id_t, handle_t > > cmp_by_ent;
    std::map<entity_id_t, EntityInfo>       entity_info_map;
    std::map<entity_id_t, std::string>      ent_names;
    std::vector<entity_id_t>                active_entities;
    
public:
    ComponentManager() : next_ent_id(1)
    {
        
    }
    
    entity_id_t createNewEntity()
    {
        entity_id_t new_ent = next_ent_id++;
        active_entities.push_back(new_ent);
        return new_ent;
    }
    
    
    void destroyEntity(entity_id_t ent)
    {
        //todo destroy components
        for (auto iter = cmp_by_ent[ent].begin(); iter != cmp_by_ent[ent].end(); iter++) {
            //destroyComponent<Transform>(iter->second);
        }
        std::remove(active_entities.begin(), active_entities.end(), ent);
    }
    
    void setEntityName(entity_id_t ent, const char *name)
    {
        ent_names[ent] = name;
    }
    
    const char* getEntityName(entity_id_t ent)
    {
        return ent_names[ent].c_str();
    }
    
    void destroyComponent(cmp_id_t id, handle_t handle)
    {
        PoolBase *pool = component_instance_pools[id].get();
        pool->free(handle);
    }

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
        cmp_by_ent[ent][_Type::id] = h;
        _Type * comp = pool->resolve(h);
        if(comp != nullptr) {
            cmp_by_ent[ent][_Type::id] = (h);
            comp->ent = ent;
            comp->ref_handle = &cmp_by_ent[ent][_Type::id];
            comp->init(ent);
        }
        return h;
    }
    
    template<typename _Type>
    void  destroyComponent(handle_t h)
    {
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
