#include <iostream>
#include <memory>

#include "context.h"
#include "logger.h"
#include "render_system.h"
#include "component.h"
#include <chrono>
#include "entity.h"
#include "type_identifier.h"
#include "fixed_size_pool.h"
#include "hierarchy.h"


typedef FixedSizePool<int> int_pool;
typedef ComponentManagerBaseT<int, 10> IntMgr ;
using namespace cell;


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
    IntMgr int_mgr;
    
    Handle h1 = int_mgr.create();
    
    int * p = int_mgr.get(h1);
    *p = 1000;
    h1 = int_mgr.create();
    p = int_mgr.get(h1);
    
    *p = 2000;
    
    Handle h2 = int_mgr.create();
    p = int_mgr.get(h2);
    *p = 3000;
    int_mgr.destroy(h1);
    h1 = int_mgr.create();
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
