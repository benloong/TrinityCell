//
//  fixed_size_pool.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-15.
//
//

#ifndef TrinityCell_linear_mem_pool_h
#define TrinityCell_linear_mem_pool_h
#include <cstdint>
#include <assert.h>

template<size_t Bits = 16>
struct Handle_T {
	enum {
		ID_Bits = Bits,
		KEY_Bits = 32-Bits
	};

    uint32_t idx : ID_Bits;
	uint32_t key : KEY_Bits;
    
    inline operator uint32_t() const
    {
        return idx << ID_Bits | key;
    }
    
    Handle_T(uint32_t num = 0) : idx(num>>ID_Bits), key(num)
    {
        
    }
    
    Handle_T(uint32_t idx, uint32_t key): idx(idx), key(key)
    {
        
    }
};

typedef uint32_t handle_t;
const handle_t invalid_handle = -1;

template <typename DataType, uint32_t POOL_SIZE = 1<<16, size_t IDX_Bits = 16 >
struct FixedSizePool {
    typedef Handle_T<IDX_Bits> Handle;
	static_assert(POOL_SIZE <= 1<<IDX_Bits, "POOL_SIZE must below 1<<IDX_Bits");
    struct Entry
    {
        uint32_t    next_free : IDX_Bits;
        uint32_t    key       : 32-IDX_Bits;
    };
    
    uint32_t        first_free;
    Entry           entries[POOL_SIZE];//for indices
    DataType        pool[POOL_SIZE];   // raw array
    
    FixedSizePool() : first_free(0){
        reset();
    }
    
    void reset()
    {
        first_free = 0;
        for(uint32_t i = 0; i < POOL_SIZE; i++)
        {
            entries[i].next_free = i+1;
            entries[i].key = 0;
        }
    }
    
    Handle allocate()
    {
        if (first_free >= POOL_SIZE || first_free >= 1<<IDX_Bits) {
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
    
    DataType* data()
    {
        return pool;
    }
};

#endif
