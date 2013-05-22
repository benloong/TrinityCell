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

class Transform : public DCS::Component_T<Transform, 1<<10 > {
    
public:
    handle_t parent;
    handle_t first_child;
    handle_t prev_sibling;
    handle_t next_sibling;
    uint16_t level;
    uint16_t bitmask; // update bit mask
    
    float  position[3];
    float  scale[3];
    float  rotation[4];
    
    float  world_mat[16];
    float  local_mat[16];
    
    Transform();
    
    ~Transform();
};
    
namespace Hierarchy
{
    void        setParent(handle_t child, handle_t parent);
    handle_t    getParent(handle_t trans);
    handle_t    getRoot(handle_t trans);
    int         childCount(handle_t trans);
    handle_t    getChild(int index);
    
    void        updateHierarchy();
}
#endif /* defined(__TrinityCell__transform__) */
