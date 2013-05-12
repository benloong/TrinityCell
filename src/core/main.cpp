#include <iostream>
#include "context.h"
#include "logger.h"
#include "render_system.h"

using namespace cell;
int main()
{
    if(ctx == nullptr)
        ctx = new Context();
    do {
        ctx->init();
    } while (0);
    ctx->shutdown();
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
    std::cout<<"hello world\n";
	return 0;
}
