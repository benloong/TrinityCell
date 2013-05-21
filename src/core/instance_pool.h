//
//  instance_pool.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-19.
//
//

#ifndef __TrinityCell__instance_pool__
#define __TrinityCell__instance_pool__

#include <array>
#include <vector>
#include <assert.h>
#include <functional>

typedef int handle_t;

class PoolBase {
public:
    PoolBase(){}
    virtual ~PoolBase() {}
};

template<typename _Ty, size_t _PoolSize, size_t _BitWidth = 16>
class InstancePool : public PoolBase
{
public:
    static_assert(_BitWidth < 20, "Too large index bit width, must be smaller than 20.");
    static_assert(_PoolSize <= 1 << _BitWidth, "_PoolSize out of index. _PoolSize must be smaller than 1<<_BitWidth.");
    typedef _Ty DataType;
    
    enum  {
		ID_BIT_WIDTH    = _BitWidth,
		KEY_BIT_WIDTH   = 32 - _BitWidth
	};
    
	struct Handle
	{
		int  idx : ID_BIT_WIDTH;
		int  key : KEY_BIT_WIDTH;
        
        inline operator int()
        {
            return idx << ID_BIT_WIDTH | key;
        }
        
        Handle(int h) : idx(h>>ID_BIT_WIDTH), key(h)
        {
            
        }
        Handle(int idx, int key) : idx(idx) , key(key)
        {
        }
	};
    
	struct Entry
	{
		int  next_free : ID_BIT_WIDTH;
		int  key       : KEY_BIT_WIDTH;
	};
    
    std::array<Entry,   _PoolSize>  entries;
    std::array<DataType,_PoolSize>  pool;
	int                             first_free;
    
    std::vector<handle_t>           allocated;
    
	InstancePool() {
        reset();
	}
    
    ~InstancePool() {
        
    }
    
    void reset()
    {
        first_free = 0;
        for(size_t i = 0; i < _PoolSize; ++i )
        {
            entries[i].next_free = i+1;
            entries[i].key       = 1;
        }
        allocated.clear();
    }
    
    Handle allocate()
    {
        if (first_free >= _PoolSize || first_free >= 1<<ID_BIT_WIDTH) {
            return Handle(0);
        }
        uint32_t idx = first_free;
        first_free = entries[idx].next_free;
        Handle h(idx, entries[idx].key);
        allocated.push_back(h);
        return h;
    }
    
    void free(Handle handle)
    {
        int idx = handle.idx;
        assert(handle != 0 && "try to free an invalid handle.");
        assert(idx < _PoolSize);
        entries[idx].next_free = first_free;
        entries[idx].key += 1;
        first_free = idx;
        
        auto iter = std::find(allocated.begin(), allocated.end(), handle);
        if( iter != allocated.end() )
        {
            std::swap(*iter, allocated.back());
            allocated.pop_back();
        }
    }
    
    DataType* resolve(Handle handle)
    {
        DataType* p = nullptr;
        if(handle != 0 && handle.idx < _PoolSize && entries[handle.idx].key == handle.key)
            p = &pool[handle.idx];
        return p;
    }
    
    inline DataType* data()
    {
        return pool.data();
    }
};

#endif /* defined(__TrinityCell__instance_pool__) */
