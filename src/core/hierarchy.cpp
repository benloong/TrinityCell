//
//  hierarchy.cpp
//  TrinityCell
//
//  Created by he qianjun on 13-5-16.
//
//

#include "hierarchy.h"
#include "component_types.h"

namespace cell {

    template<>
    const uint16_t ComponentBaseT<TransformHierarchy>::type_id = 1;

    void TransformHierarchy::update()
    {

    }
}
