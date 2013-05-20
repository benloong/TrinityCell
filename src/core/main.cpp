#include <iostream>
#include <memory>

#include "context.h"
#include "logger.h"
#include "render_system.h"
#include "component.h"
#include <chrono>
#include "entity.h"

#include "timer.h"
#include "component_manager.h"
#include <thread>

using namespace cell;
using namespace std;

int main()
{

    Timer::resetTimer();
    //Timer::setTimeScale(-1.0f);
    for(int i = 0 ; i < 10; i++)
    {
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000));
        Timer::update();
        std::cout << Timer::getDeltaTime() << std::endl;
        std::cout << Timer::getRealTime() << std::endl;
        std::cout << Timer::getTime()   << std::endl;
        std::cout << "==============================\n";
    }
    getchar();

    ComponentManager cmpMgr;
    handle_t h = cmpMgr.addComponent<Transform>(10);
    Transform* trans = cmpMgr.resolveHandle<Transform>(h);
    cout << trans->ent << endl;
    return 0;
}
