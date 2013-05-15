//
//  linear_mem_pool.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-15.
//
//

#ifndef TrinityCell_linear_mem_pool_h
#define TrinityCell_linear_mem_pool_h
#include <cstdint>

struct Handle {
    uint32_t idx : 16;
    uint32_t key : 16;
    
    inline operator uint32_t() const
    {
        return idx << 16 | key;
    }
    
    Handle(uint32_t num = 0) : idx(num>>16), key(num)
    {
        
    }
    
    Handle(uint32_t idx, uint32_t key): idx(idx), key(key)
    {
        
    }
};

const Handle invalid_handle = 0xffffffff;

template <typename DataType, uint32_t POOL_SIZE = 1<<16 >
struct LinearPool {
    
    struct Entry
    {
        uint32_t    next_free : 16;
        uint32_t    key       : 16;
    };
    
    uint32_t        first_free;
    Entry           entries[POOL_SIZE];//for indices
    DataType        pool[POOL_SIZE];  // raw array
    
    Handle allocate()
    {
        if (first_free >= POOL_SIZE) {
            return invalid_handle;
        }
        uint32_t idx = first_free;
        first_free = entries[idx].next_free;
        return Handle(idx, entries[idx].key);
    }
    
    void free(Handle handle)
    {
        uint32_t idx = handle.idx;
        assert(idx < POOL_SIZE);
        entries[idx].next_free = first_free;
        entries[idx].key += 1;
        first_free = idx;
    }
    
    DataType* resolve(Handle handle)
    {
        uint32_t idx = handle.idx;
        assert(idx < POOL_SIZE);
        if(handle.key == entries[idx].key)
            return &pool[idx];
        return nullptr;
    }
};

#endif
