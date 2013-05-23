//
//  component_manager.cpp
//  TrinityCell
//
//  Created by he qianjun on 13-5-19.
//
//

#include "component_manager.h"
#include "transform.h"

template<>
void ComponentManager::updateComponent<Transform>()
{
    int x = 0;
    assert(x == 0);
    Transform trans;
    assert(&trans);
}