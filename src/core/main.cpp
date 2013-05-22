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

using namespace cell;
using namespace std;

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
    getchar();

    if (ctx == nullptr) {
        ctx = new cell::Context();
    }
    do {
        if(!ctx->init()) break;
        
        handle_t root = ctx->getCompManager()->addComponent<Transform>(10);
        handle_t child = ctx->getCompManager()->addComponent<Transform>(12);
        Hierarchy::setParent(child, root);
        handle_t parent = Hierarchy::getParent(child);
        assert(Hierarchy::getRoot(child) == root);
        assert(parent == root);
        ctx->getCompManager()->destroyComponent<Transform>(root);
        
    } while (0);
    ctx->shutdown();
    return 0;
}
