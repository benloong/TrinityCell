#include <iostream>
#include <memory>

#include "context.h"
#include "logger.h"
#include "render_system.h"
#include "component.h"
#include <chrono>
#include "entity.h"

#include "timer.h"
#include <thread>

using namespace cell;
using namespace std;

int main()
{
//    if(ctx == nullptr)
//        ctx = new Context();
//    do {
//        ctx->init();
//    } while (0);
//    ctx->shutdown();
//    {
//    Logger log("hello.log");
//    log.LogWarning("test warning");
//    log.LogError("test error");
//    log.Log("test text");
//    {
//        std::string  s("hell test text");
//        log.Log(s.c_str());
//    }
//    }
//    std::cout<<"hello world\n";
    //Transform::ManagerType *p = new Transform::ManagerType();
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
    //return 0;

    //
//    ComponentManager compMgr;
//    compMgr.registerComponent<MyComponent>(5);
//    
//    int handle = compMgr.addComponent<MyComponent>(1);
//    
//    
//    int_pool pool;
//    
//    Handle h = pool.allocate();
//    int * p = pool.resolve(h);
//    std::cout<<(int)invalid_handle<<std::endl;
//    prealloc_object<entity_t>::TypeArray  &array = entity_t::__allocated;
//    std::cout<<Class2::id<<std::endl;
//    std::cout<<Class1::id<<std::endl;
//    std::cout<<Class3::id<<std::endl;
    
    return 0;
}
