//
//  transform.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-20.
//
//

#ifndef __TrinityCell__transform__
#define __TrinityCell__transform__
#include <stdint.h>
#include "component.h"

class Transform : public DCS::Component_T<Transform, 1<<16 > {
    
public:
    uint16_t parent;
    uint16_t first_child;
    uint16_t prev_sibling;
    uint16_t next_sibling;
    uint16_t level;
    uint16_t bitmask; // update bit mask
    
    float  position[3];
    float  scale[3];
    float  rotation[4];
    
    float  world_mat[16];
    float  local_mat[16];
    
    
    void setParent(handle_t parentHandle);
    void setParent(Transform* parent);
    
    Transform* getRoot();
    
    int childCount();
    Transform* getChild(int index);
    Transform* getParent();
    
    Transform();
};

namespace TransformUtil
{
    void setParent(handle_t child, handle_t parent);
    handle_t getRoot();
    
}

#endif /* defined(__TrinityCell__transform__) */
