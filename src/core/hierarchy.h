//
//  hierarchy.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-23.
//
//

#ifndef __TrinityCell__hierarchy__
#define __TrinityCell__hierarchy__

#include "cmp_type.h"
#include "transform.h"
struct Hierarchy : public cmp_type_t<Transform> {
    virtual void update()
    {
        
    }
};
#endif /* defined(__TrinityCell__hierarchy__) */
