//
//  entity_system.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-12.
//
//

#ifndef __TrinityCell__entity_system__
#define __TrinityCell__entity_system__

#include <vector>
#include <string>

namespace cell {
    class Context;
    typedef uint32_t entity_id_t;
    
    class EntitySystem
    {
        
    public:
        EntitySystem(const Context &ctx);
        ~EntitySystem();
        entity_id_t createEntity();
        void        destroyEntity(entity_id_t id);
        
        template<typename Comp_T>
        void addComponent(entity_id_t ent);
        
        
        std::vector<entity_id_t> entities;
        std::vector<std::string> entity_names;
    };
}

#endif /* defined(__TrinityCell__entity_system__) */
