//
//  context.cpp
//  TrinityCell
//
//  Created by he qianjun on 13-5-12.
//
//

#include "context.h"
#include "logger.h"
#include "input_system.h"
#include "entity_system.h"
#include "thread_pool.h"
#include "render_system.h"

using namespace cell;
namespace cell {
    Context *ctx = nullptr;
}

bool Context::init()
{
    _input_system = new InputSystem();
    _logger = new Logger("trinity_cell.log");
    _render_system = new RenderSystem(*this);
    _entity_system = new EntitySystem(*this);
    
    return true;
}

void Context::shutdown()
{
    delete _input_system;
    delete _logger;
    
    delete _entity_system;
    delete _render_system;
}