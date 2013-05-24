//
//  render_system.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-12.
//
//

#ifndef __TrinityCell__render_system__
#define __TrinityCell__render_system__

#include<memory>
#include<cstdint>
namespace cell{
    class Context;
    
    class RenderSystemImpl;
    class RenderSystem
    {
        std::unique_ptr<RenderSystemImpl> pImpl;
    public:
        RenderSystem(Context const & ctx);
        ~RenderSystem();
        int createVertexBuffer(unsigned int count, unsigned int stride, const void *init_data);
        void destroyVertexBuffer(int handle);
        
        int createIndexBuffer(unsigned int count, int format, const void *init_data);
        void destroyIndexBuffer(int handle);
    };
}

#endif /* defined(__TrinityCell__render_system__) */
