#include <iostream>
#include <memory>

#include "context.h"
#include "logger.h"
#include "render_system.h"
#include "component.h"
#include <chrono>

#include "timer.h"
#include "component_manager.h"
#include <thread>
#include "transform.h"
using namespace cell;
using namespace std;

struct _Int {
    //entity_id_t ent_id;
    handle_t*    hdl;
    uint32_t     ent_id;
    handle_t     _h;
    handle_t     _h2;
};
int main()
{

    Timer::resetTimer();
    //Timer::setTimeScale(-1.0f);
//    for(int i = 0 ; i < 10; i++)
//    {
//        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000));
//        Timer::update();
//        std::cout << Timer::getDeltaTime() << std::endl;
//        std::cout << Timer::getRealTime() << std::endl;
//        std::cout << Timer::getTime()   << std::endl;
//        std::cout << "==============================\n";
//    }
    cout << sizeof(entity_id_t) << endl;
    cout << sizeof(float) << endl;
    cout << sizeof(handle_t*) << endl;
    cout << sizeof(_Int) << endl;
    getchar();

    if (ctx == nullptr) {
        ctx = new cell::Context();
    }
    do {
        if(!ctx->init()) break;
        ComponentManager cmpMgr;
        Transform* trans = cmpMgr.addComponent<Transform>(10);
        handle_t h1 = *trans->ref_hdl;
        Transform* trans2 = cmpMgr.addComponent<Transform>(12);
        handle_t& h2 = *trans2->ref_hdl;
        cmpMgr.freeComponent<Transform>(h1);
        cmpMgr.freeComponent<Transform>(h2);
        cmpMgr.updateComponent<Transform>();
    } while (0);
    ctx->shutdown();
    return 0;
}
