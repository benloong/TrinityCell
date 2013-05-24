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
#include "cmp_type.h"

struct EntityInfo {
    entity_id_t id;
    char        name[32];
    std::map<cmp_id_t, handle_t> components;
    EntityInfo() : id(0)
    {
        memset(name, 0, 32);
    }
};

struct ComponentManager{
    
    std::map<cmp_id_t, std::unique_ptr<cmp_type_base> > cmp_types;
    std::map<entity_id_t, EntityInfo> entities;
    
    entity_id_t next_id;
    
    EntityInfo& getEntityByID(entity_id_t id)
    {
        return entities[id];
    }
    
    template<typename _Ty>
    cmp_type_t<_Ty>* regiseterCmpType()
    {
        cmp_type_t<_Ty>* p = new cmp_type_t<_Ty>();
        cmp_types[_Ty::ID].reset(p);
        return p;
    }
    
    template<typename _Ty>
    cmp_type_t<_Ty>* getCmpType()
    {
        cmp_type_t<_Ty>* cmp_t = static_cast<cmp_type_t<_Ty>*> (cmp_types[_Ty::ID].get());
        if (cmp_t == nullptr) {
            cmp_t = regiseterCmpType<_Ty>();
        }
        return cmp_t;
    }
    
    void freeComponent(cmp_type_base* cmp_t, handle_t h)
    {
        cmp_t->free(h);
    }
    
    template<typename _Ty>
    void freeComponent(handle_t h)
    {
        freeComponent(getCmpType<_Ty>(), h);
    }
    
    template<typename _Ty>
    _Ty* getComponent(entity_id_t ent)
    {
        handle_t h = entities[ent].components[_Ty::ID];
        cmp_type_t<_Ty> *cmp_tp = getCmpType<_Ty>();
        _Ty* cmp = static_cast<_Ty*>(cmp_tp->resolve(h));
        return cmp;
    }
    
    template<typename _Ty>
    _Ty* addComponent(entity_id_t ent_id)
    {
        cmp_type_t<_Ty>* cmp_tp = getCmpType<_Ty>();
        handle_t h = cmp_tp->allocate();
        EntityInfo& ent_info = entities[ent_id];
        ent_info.components[_Ty::ID] = h;
        _Ty *cmp = static_cast<_Ty*>(cmp_tp->resolve(h));
        if (cmp) {
            cmp->ref_hdl = &ent_info.components[_Ty::ID];
            cmp->ent_id = ent_id;
        }
        return cmp;
    }
    
    template<typename _Ty>
    void updateComponent()
    {
        
    }
};


struct Transform;
template<>
void ComponentManager::updateComponent<Transform>();
#endif /* defined(__TrinityCell__component_manager__) */
