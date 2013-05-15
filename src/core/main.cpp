#include <iostream>
#include <memory>

#include "context.h"
#include "logger.h"
#include "render_system.h"
#include "component.h"
#include <chrono>
#include "entity.h"
#include "type_identifier.h"
#include "linear_mem_pool.h"


struct Class2 : public identifier<Class2, 1> {
    
};

struct Class1 : public identifier<Class1, 2> {
    
};

struct Class3 : public identifier<Class3, 3> {
    
};

class MyComponent : public cell::ComponentBase<MyComponent> {
    int x;
    int y;
    int z;
    
public:
};

typedef LinearPool<int> int_pool;
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
    ComponentManager compMgr;
    compMgr.registerComponent<MyComponent>(5);
    
    int handle = compMgr.addComponent<MyComponent>(1);
    
    int_pool pool;
    
    Handle h = pool.allocate();
    int * p = pool.resolve(h);
    std::cout<<(int)invalid_handle<<std::endl;
    prealloc_object<entity_t>::TypeArray  &array = entity_t::__allocated;
    std::cout<<Class2::id<<std::endl;
    std::cout<<Class1::id<<std::endl;
    std::cout<<Class3::id<<std::endl;
	return 0;
}
