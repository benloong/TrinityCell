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
#include "cmp_base.h"
#include <vector>

struct Transform : public cmp_base {

    enum {
        ID = 1,
        MAX_COUNT = 1024
    };
    
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
    
    Transform()
    {
        int x = 0;
        assert(x == 0);
    }
};
namespace SceneGraph {
    
void        setParent(Transform* self, Transform* parent);

Transform*  getParent(Transform* self);

Transform*  getRoot(Transform* self);

int         childCount(Transform* self);

Transform*  getChild(Transform* self, int index);
    
void        update();
}

#endif /* defined(__TrinityCell__transform__) */
