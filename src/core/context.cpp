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
#include "render_system.h"
#include "component_manager.h"

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
    _comp_manager = new ComponentManager();
    return true;
}

void Context::shutdown()
{
    delete _input_system;
    delete _logger;
    delete _comp_manager;
    delete _entity_system;
    delete _render_system;
}

ComponentManager* Context::getCompManager()
{
    return _comp_manager;
}