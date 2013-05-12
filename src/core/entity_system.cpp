//
//  entity_system.cpp
//  TrinityCell
//
//  Created by he qianjun on 13-5-12.
//
//

#include "entity_system.h"
#include "context.h"

namespace cell{
    
    class EntitySystemImpl {
    
    public:
        EntitySystemImpl(){}
    };
}

using namespace cell;

EntitySystem::EntitySystem(const Context &ctx):pImpl(new EntitySystemImpl())
{
    
}

EntitySystem::~EntitySystem()
{
    
}