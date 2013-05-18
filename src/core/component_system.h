//
//  component_system.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-17.
//
//

#ifndef __TrinityCell__component_system__
#define __TrinityCell__component_system__
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include "fixed_size_pool.h"
#include "component_roster_base.h"
#include "component_detail.h"
#include "hierarchy.h"

namespace cell {
    //class ComponentManagerBase;
    class ComponentSystem
    {
    public:
        
        std::map<uint32_t, std::unique_ptr<ComponentManagerBase> > _comp_managers;
        std::map<uint32_t, std::function<void (void)> > _updates;//one function per component manager
        //TODO: need some cache protocal
    };
    
    template<typename Type>
    const Type* getComponent(ComponentSystem* comp_system, uint32_t ent)
    {
        typename Type::ManagerType *mgr = (typename Type::ManagerType *)comp_system->_comp_managers[Type::type_id].get();
        if(mgr == nullptr)
            return nullptr;
        return mgr->getComponent(ent);
    }
    
    template<typename Type>
    typename Type::ManagerType::HandleType addComponent(ComponentSystem* comp_system, typename Type::ManagerType::HandleType ent)
    {
        typedef typename Type::ManagerType Manager;
        typedef typename Manager::HandleType  Handle;
        Handle h = invalid_handle;
        typename Type::ManagerType *mgr = (typename Type::ManagerType *)comp_system->_comp_managers[Type::type_id].get();
        if(mgr == nullptr){
            mgr = new typename Type::ManagerType();
            comp_system->_comp_managers[Type::type_id].reset(mgr);
            comp_system->_updates[Type::type_id] = [mgr]() {
                mgr->update();
            };
        }
        h = mgr->create(ent);
        return h;
    }
    
    template<typename Type>
    void destroyComponent(ComponentSystem* comp_system, typename Type::ManagerType::HandleType comp_handle)
    {
        typename Type::ManagerType *mgr = (typename Type::ManagerType *)comp_system->_comp_managers[Type::type_id].get();
        assert(mgr != nullptr && "cannot find the Manager of this comonent type!");
        mgr->destroy(comp_handle);
    }
    
    template<typename Type>
    Type* resolveHandle(ComponentSystem* comp_system, typename Type::ManagerType::HandleType comp_handle)
    {
        typename Type::ManagerType *mgr = (typename Type::ManagerType *)comp_system->_comp_managers[Type::type_id].get();
        assert(mgr != nullptr && "cannot find the Manager of this component type!");
        return mgr->resolve(comp_handle);
    }
    
    template<typename Type>
    Type* valid_cast(ComponentBase* comp){
        if(Type::type_id == comp->_type_id)
        {
            return (Type*)comp;
        }
        return nullptr;
    }
    
    template<typename Type>
    uint32_t getComponents(ComponentSystem* comp_system, Type **result, uint32_t max_count)
    {
        typename Type::ManagerType *mgr = (typename Type::ManagerType *)comp_system->_comp_managers[Type::type_id].get();
        assert(mgr != nullptr && "cannot find the Manager of this comonent type!");
        const uint32_t count = mgr->_count;
        Type * data = mgr->_pool.data();
        uint32_t i = 0;
        for ( ; i < count && i < max_count; ++i) {
            result[i] = &data[mgr->_nodes[i].idx];
        }
        return i;
    }
    
    inline void updateAllComponents(ComponentSystem* comp_system)
    {
        for (auto it = comp_system->_updates.begin(); it != comp_system->_updates.end(); it++) {
            it->second();
        }
    }
}

#endif /* defined(__TrinityCell__component_system__) */
