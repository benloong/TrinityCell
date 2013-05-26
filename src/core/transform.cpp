//
//  transform.cpp
//  TrinityCell
//
//  Created by he qianjun on 13-5-20.
//
//

#include "transform.h"
#include "context.h"
#include "cmp_type.h"


template<>
void cmp_type_t<Transform>::update()
{
    
}

template <>
void cmp_type_t<Transform>::free(cmp_base * cmp)
{
    handle_t h = cmp->handle;
    assert(h != INVALID_HANDLE && "try to free an invalid handle.");
    size_t idx = HANDLE_INDEX(h);
    size_t key = HANDLE_KEY(h);
    assert(idx < max_size && "bad handle index.");
    assert(key == keys[idx] && "bad handle key.");
    keys[idx] += 1;
    
    //swap back and idx
    size_t last_idx = --next_idx;
    if(last_idx == idx) return;
    
    cmp_base* last_cmp = at(indices[last_idx]);
    
    std::swap(indices[idx], indices[last_idx]);
    std::swap(keys[idx], keys[last_idx]);
    
    handle_t old_handle =  last_cmp->handle;
    last_cmp->handle = MAKE_HANDLE(idx, HANDLE_KEY(old_handle));
    ((pointer_type)cmp)->~comp_type();
}