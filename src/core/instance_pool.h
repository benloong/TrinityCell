//
//  instance_pool.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-19.
//
//

#ifndef __TrinityCell__instance_pool__
#define __TrinityCell__instance_pool__

#include "types.h"

struct PoolBase {
    virtual ~PoolBase() {}
    virtual void update() = 0;
    virtual handle_t allocate() = 0;
    virtual void free(handle_t) = 0;
};

template<typename _Ty, size_t _PoolSize>
class InstancePool : public PoolBase
{
public:
    
    static_assert(_PoolSize <= 1 << 16, "_PoolSize out of index. _PoolSize must be smaller than 1<<_BitWidth.");
    typedef _Ty DataType;

    
    index_t     keys[_PoolSize];
    index_t     indices[_PoolSize];
    DataType    data[_PoolSize];
    
	index_t     next_idx;
    
	InstancePool() {
        reset();
	}
    
    ~InstancePool() {
        
    }
    
    void reset()
    {
        next_idx = 0;
        for(size_t i = 0; i < _PoolSize; ++i )
        {
            indices[i] = i;
            keys[i] = 1;
        }
    }
    
    handle_t allocate()
    {
        if (next_idx == _PoolSize || next_idx == 1<<16) {
            return MAKE_HANDLE(0, 0);
        }
        uint32_t idx = next_idx++;
        return MAKE_HANDLE(idx, keys[idx]);
    }
    
    void free(handle_t h)
    {
        uint16_t idx = HANDLE_INDEX(h);
        uint16_t last_idx = next_idx-1;
        assert(h != 0 && "try to free an invalid handle.");
        assert(idx < _PoolSize);
        data[indices[idx]].~DataType();
        keys[idx] += 1;
        
        DataType* last = &data[indices[last_idx]];
        handle_t newhdl = MAKE_HANDLE(HANDLE_INDEX(h), HANDLE_KEY(*last->ref_handle));
        *last->ref_handle = newhdl;
        std::swap(indices[idx], indices[last_idx]);
        std::swap(keys[idx], keys[last_idx]);
    }
    
    DataType* resolve(handle_t handle)
    {
        DataType* p = nullptr;
        uint16_t idx = HANDLE_INDEX(handle);
        uint16_t key = HANDLE_KEY(handle);
        if(handle != INVALID_HANDLE && idx < _PoolSize && keys[idx] == key)
            p = &data[indices[idx]];
        return p;
    }
    
    void update()
    {
        
    }
    
    inline DataType* getData()
    {
        return data;
    }
};

#endif /* defined(__TrinityCell__instance_pool__) */
