//
//  cmp_type.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-23.
//
//

#ifndef TrinityCell_cmp_type_h
#define TrinityCell_cmp_type_h

#include "types.h"
#include "cmp_base.h"

//fixed size component instance pool
struct cmp_type_base
{
	const size_t stride;
    const size_t max_size;
	const size_t max_bytes;
    
	uint8_t *data;
	size_t  *indices;
	size_t  *keys;
    
	size_t  next_idx;
    
	cmp_type_base(size_t stride, size_t _max_size)
	:
	stride(stride),
	max_size(_max_size),
	max_bytes(stride*_max_size),
	data(0),
	indices(0),
    keys(0),
	next_idx(0)
	{
		reset();
	}
    
	~cmp_type_base()
	{
		delete []data;
		delete []indices;
		delete []keys;
	}
    
	void reset()
	{
		if(data) delete []data;
		if(indices) delete []indices;
        if(keys) delete []keys;
        
		data = new uint8_t[max_bytes];
		indices = new size_t[max_size];
		keys = new size_t[max_size];
        
		for (int i = 0; i < max_size; ++i)
		{
			indices[i] = i*stride;
			keys[i] = 1;
		}
		next_idx = 0;
	}
    
	inline void* at(size_t idx)
	{
		return data + idx;
	}
    
	handle_t allocate()
	{
		if (next_idx == max_size || next_idx == 1 << 16)
			return INVALID_HANDLE;
        
		void *p = 0;
        size_t cur_idx = next_idx++;
		p = at(indices[cur_idx]);
		on_allocated(p);
		return MAKE_HANDLE(cur_idx, keys[cur_idx]);
	}
    
	void free(handle_t h)
	{
		assert(h != INVALID_HANDLE && "try to free an invalid handle.");
		size_t idx = HANDLE_INDEX(h);
		size_t key = HANDLE_KEY(h);
		assert(idx < max_size && "bad handle index.");
        assert(key == keys[idx] && "bad handle key.");
		void* p = at(indices[idx]);
		on_free(p);
        
		//swap back and idx
		size_t last_idx = --next_idx;
        if(last_idx == idx) return;
        
        cmp_base* cmp = static_cast<cmp_base*>(at(indices[last_idx]));
        
		std::swap(indices[idx], indices[last_idx]);
		std::swap(keys[idx], keys[last_idx]);
        keys[last_idx] += 1;
        
        handle_t old_handle =  *cmp->ref_hdl;
        *cmp->ref_hdl = MAKE_HANDLE(idx, HANDLE_KEY(old_handle));
	}
    
    void* resolve(handle_t h)
    {
        assert(h != INVALID_HANDLE && "try to free an invalid handle.");
		size_t idx = HANDLE_INDEX(h);
		size_t key = HANDLE_KEY(h);
		assert(idx < max_size && "bad handle index.");
        assert(key == keys[idx] && "bad handle key.");
        return at(indices[idx]);
    }
    
	virtual void on_allocated(void *p)
	{
		
	}
    
	virtual void on_free(void *p)
	{
        
	}
    
    virtual void on_update()
    {
        
    }
};

template <typename _Ty>
struct cmp_type_t : public cmp_type_base
{
    typedef _Ty     comp_type;
    typedef _Ty*    pointer_type;
	cmp_type_t()
	:
	cmp_type_base(sizeof(_Ty), _Ty::MAX_COUNT)
	{
	}
    
	void on_allocated(void *p)
	{
        new (p)comp_type();
	}
    
	void on_free(void *p)
	{
        pointer_type cmp = static_cast<pointer_type>(p);
        *cmp->ref_hdl = INVALID_HANDLE;
        cmp->~comp_type();
	}
    
    void on_update()
    {
        
    }
};

#endif
