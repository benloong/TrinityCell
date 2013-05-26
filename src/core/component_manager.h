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


//forward declare

struct ComponentManager;

struct EntityInfo {
    entity_id_t id;
    char        name[32];
    uint32_t    flags;
    ComponentManager * mgr;
    std::map<cmp_id_t, handle_t* > components;
    EntityInfo() : id(0), mgr(0)
    {
        memset(name, 0, 32);
    }
};

EntityInfo* createEntity(char const * name);
void        destroyEntity(EntityInfo * ent_info);
EntityInfo* getEntityByID(entity_id_t id);

template <typename _Ty>
_Ty* getComponent(EntityInfo * ent_info);

template <typename _Ty>
_Ty* addComponent(EntityInfo * ent_info);


struct ComponentManager{
    
    std::map<cmp_id_t, std::unique_ptr<cmp_type_base> > cmp_types;
    std::map<entity_id_t, EntityInfo> entities;
    
    entity_id_t  next_id;
    ComponentManager();
};

//////////
template <typename _Ty>
_Ty* getComponent(EntityInfo * ent_info) {
    handle_t h = ent_info->components[_Ty::ID];
    cmp_type_base *cmp_tp = ent_info->mgr->cmp_types[_Ty::ID].get();
    if (cmp_tp == nullptr) {
        cmp_tp = new cmp_type_t<_Ty>();
        ent_info->mgr->cmp_types[_Ty::ID].reset(cmp_tp);
    }
    _Ty* cmp = static_cast<_Ty*>(cmp_tp->resolve(h));
    return cmp;
}

template <typename _Ty>
_Ty* addComponent(EntityInfo * ent_info) {
    cmp_type_base *cmp_tp = ent_info->mgr->cmp_types[_Ty::ID].get();
    if (cmp_tp == nullptr) {
        cmp_tp = new cmp_type_t<_Ty>();
        ent_info->mgr->cmp_types[_Ty::ID].reset(cmp_tp);
    }
    
    _Ty* cmp = static_cast<_Ty*>(cmp_tp->allocate());
    if (cmp) {
        ent_info->components[_Ty::ID] = &cmp->handle;
        cmp->ent_id = ent_info->id;
    }
    return cmp;
}

template <typename _Ty>
void destroyComponent(EntityInfo * ent_info, _Ty* cmp) {
    cmp_type_base * p = ent_info->mgr->cmp_types[_Ty::ID].get();
    assert(p != nullptr && "try to destroy un registered component type.");
    p->free(cmp);
}
#endif /* defined(__TrinityCell__component_manager__) */
