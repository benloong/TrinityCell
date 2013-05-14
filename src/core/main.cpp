#include <iostream>
#include <memory>

#include "context.h"
#include "logger.h"
#include "render_system.h"
#include "component.h"
#include <chrono>
#include "entity.h"
#include "type_identifier.h"

struct Class2 : public identifier<Class2> {
    
};

struct Class1 : public identifier<Class1> {
    
};

struct Class3 : public identifier<Class3> {
    
};

class MyComponent : public cell::ComponentBase<MyComponent> {
    int x;
    int y;
    int z;
    
public:
};

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
    
    prealloc_object<entity_t>::TypeArray  &array = entity_t::__allocated;
    std::cout<<Class2::id.id<<std::endl;
    std::cout<<Class1::id.id<<std::endl;
    std::cout<<Class3::id.id<<std::endl;
	return 0;
}
