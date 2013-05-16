//
//  render_system.cpp
//  TrinityCell
//
//  Created by he qianjun on 13-5-12.
//
//

#include "render_system.h"
#include "context.h"

using namespace cell;

namespace cell {
    
    class RenderSystemImpl
    {
        
    };
    
    RenderSystem::RenderSystem(const Context &ctx):pImpl(new RenderSystemImpl())
    {
        
    }

    RenderSystem::~RenderSystem()
    {
        
    }
}