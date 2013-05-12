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
#include <memory>

namespace cell {
    class Context;
    class EntitySystemImpl;
    typedef int entity_id_t;
    
    class EntitySystem
    {
        std::unique_ptr<EntitySystemImpl> pImpl;
    public:
        EntitySystem(const Context &ctx);
        ~EntitySystem();
        entity_id_t createEntity();
        void        destroyEntity(entity_id_t id);
        
        template<typename Cmp_T>
        void addComponent(entity_id_t ent);
    };
}

#endif /* defined(__TrinityCell__entity_system__) */
