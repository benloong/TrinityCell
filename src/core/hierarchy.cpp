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
    typedef TransformHierarchy::HandleType HandleType;

    void TransformHierarchy::setParent(HandleType handle, HandleType parent)
    {
        assert(invalid_handle != handle && "Invalid Transform");
        Transform * data = _pool.data();
        Transform & trans = data[handle.idx];

        uint16_t next_id = INVALID_IDX;
        do{
            if(parent == invalid_handle)
                break;
            Transform & parentTrans = data[parent.idx];

            if(parentTrans.first_child != INVALID_IDX)
            {
                next_id = parentTrans.first_child;
                data[parentTrans.first_child].prev_sibling = handle.idx;
            }
            parentTrans.first_child = handle.idx;
        }while(0);

        if(trans.parent != INVALID_IDX && data[trans.parent].first_child == handle.idx) 
        {
            data[trans.parent].first_child = trans.next_sibling;
        }
        if(trans.prev_sibling != -1)
        {
            data[trans.prev_sibling].next_sibling = trans.next_sibling;
        }

        trans.next_sibling = next_id;
        trans.parent = parent; 
    }
    void TransformHierarchy::update()
    {

    }
}
