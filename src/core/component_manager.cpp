//
//  component_manager.cpp
//  TrinityCell
//
//  Created by he qianjun on 13-5-19.
//
//

#include "component_manager.h"

//gloable variable
ComponentManager cmp_mgr;

ComponentManager::ComponentManager() : next_id(1)
{
    
}

EntityInfo* createEntity(const char* name)
{
    entity_id_t id = cmp_mgr.next_id++;
    EntityInfo * ent_info = &cmp_mgr.entities[id];
    ent_info->id = id;
    strcpy(ent_info->name, name);
    ent_info->mgr = &cmp_mgr;
    return ent_info;
}

void destroyEntity(EntityInfo* ent_info)
{
    for (auto it = ent_info->components.begin(); it != ent_info->components.end(); it++) {
        cmp_type_base* cmp_type = cmp_mgr.cmp_types[it->first].get();
        cmp_base* cmp = cmp_type->resolve(*it->second);
        cmp_type->free(cmp);
    }
}

EntityInfo* getEntityByID(entity_id_t id)
{
    return &cmp_mgr.entities[id];
}

void destroyComponent(cmp_base* cmp)
{
    //freeComponent(getCmpType<_Ty>(), cmp);
}