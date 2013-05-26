#include <iostream>
#include <memory>

#include "context.h"
#include "logger.h"
#include "render_system.h"
#include <chrono>

#include "timer.h"
#include "component_manager.h"
#include <thread>
#include "transform.h"
using namespace cell;
using namespace std;

int main()
{

    Timer::resetTimer();
    
    if (ctx == nullptr) {
        ctx = new cell::Context();
    }
    do {
        if(!ctx->init()) break;
        
        EntityInfo* ent_info = createEntity("entity 0");
        
        Transform* trans = addComponent<Transform>(ent_info);
        destroyEntity(ent_info);
        
        ent_info = createEntity("entity 1");
        Transform* trans2 = addComponent<Transform>(ent_info);
        cout << trans->ent_id << endl;
        //cmpMgr.freeComponent(trans2);
        //assert(trans == cmpMgr.getComponent<Transform>(10));
    } while (0);
    ctx->shutdown();
    return 0;
}
