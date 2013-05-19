//
//  context.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-12.
//
//

#ifndef __TrinityCell__context__
#define __TrinityCell__context__

#define TEST
namespace cell {
    class Logger;
    class EntitySystem;
    class InputSystem;
    class ScriptSystem;
    class AudioSystem;
    class RenderSystem;
    class ThreadPool;
    
    class Context
    {
        Logger          * _logger;
        EntitySystem    * _entity_system;
        InputSystem     *  _input_system;
        RenderSystem    * _render_system;
        AudioSystem     * _audio_system;
        ThreadPool      * _thread_pool;
    public:
        bool init();
        void shutdown();
    };
    
    extern Context *ctx;
}

#endif /* defined(__TrinityCell__context__) */
