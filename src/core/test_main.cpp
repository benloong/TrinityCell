
#include "camera.h"
#include "context.h"
#include "component_manager.h"
#include <iostream>
#ifdef TEST
using namespace DCS;

int main()
{
    ComponentManager *compMgr = new ComponentManager();
    do
    {
        handle_t h = compMgr->addComponent<Camera>(100);

    } while (0);
    getchar();
    delete compMgr;
    return 0;
}
#endif