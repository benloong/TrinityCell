//
//  component_traits.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-20.
//
//

#ifndef TrinityCell_component_traits_h
#define TrinityCell_component_traits_h
#include "instance_pool.h"

template<typename _Type>
struct ComponentTraits {
    enum {
        MAX_SIZE = _Type::MAX_COUNT
    };
    
    typedef InstancePool<_Type, MAX_SIZE> pool_type;
};
#endif
