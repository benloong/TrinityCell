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
        
        EntityInfo* ent0 = createEntity("entity 0");
        Transform* trans = addComponent<Transform>(ent0);
        
        EntityInfo* ent1 = createEntity("entity 1");
        Transform* trans2 = addComponent<Transform>(ent1);
        
        assert(ent1->id = trans2->ent_id);
        
        SceneGraph::setParent(trans2, trans);
        Transform* parent = SceneGraph::getParent(trans2);
        assert(parent == trans);
        assert(trans2->level == 1);
        EntityInfo* ent2 = createEntity("Entity2");
        Transform* trans3 = addComponent<Transform>(ent2);
        SceneGraph::setParent(trans3, trans2);
        
        assert(SceneGraph::getParent(trans3) == trans2);
        assert(trans3->level == 2);
        // SceneGraph::setParent(trans3, nullptr);
        
        assert(SceneGraph::getRoot(trans3) == trans);
    } while (0);
    ctx->shutdown();
    return 0;
}
