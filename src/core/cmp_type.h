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

struct cmp_type_base
{
    virtual cmp_base* allocate() = 0;
	
    virtual void free(cmp_base *p) = 0;
    
    virtual void update() = 0;
    
    virtual cmp_base* resolve(handle_t h) = 0;
};

//fixed size component instance pool
template <typename _Ty>
struct cmp_type_t : public cmp_type_base
{
    typedef _Ty     comp_type;
    typedef _Ty*    pointer_type;
	const size_t stride;
    const size_t max_size;
	const size_t max_bytes;
    
	uint8_t*    data;
	size_t*     indices;
	size_t*     keys;
    
	size_t  next_idx;
    
	cmp_type_t()
	:
	stride(sizeof(_Ty)),
	max_size(_Ty::MAX_COUNT),
	max_bytes(stride*max_size),
	data(0),
	indices(0),
    keys(0),
	next_idx(0)
	{
		reset();
	}
    
	~cmp_type_t()
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
    
	inline cmp_base* at(size_t idx)
	{
		return (cmp_base*)(data + idx);
	}
    
	virtual cmp_base* allocate()
	{
		if (next_idx == max_size || next_idx == 1 << 16)
			return nullptr;
        
		cmp_base* p = nullptr;
        size_t cur_idx = next_idx++;
		p = at(indices[cur_idx]);
        p = new (p) comp_type();
        p->handle = MAKE_HANDLE(cur_idx, keys[cur_idx]);
        p->type = this;
		return p;
	}
    
	virtual void free(cmp_base* cmp)
	{
        handle_t h = cmp->handle;
		assert(h != INVALID_HANDLE && "try to free an invalid handle.");
		size_t idx = HANDLE_INDEX(h);
		size_t key = HANDLE_KEY(h);
		assert(idx < max_size && "bad handle index.");
        assert(key == keys[idx] && "bad handle key.");
        keys[idx]++;
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
    
    cmp_base* resolve(handle_t h)
    {
        if(h == INVALID_HANDLE)
            return nullptr;
        
        assert(h != INVALID_HANDLE && "try to free an invalid handle.");
		size_t idx = HANDLE_INDEX(h);
		size_t key = HANDLE_KEY(h);
		assert(idx < max_size && "bad handle index.");
        assert(key == keys[idx] && "bad handle key.");
        return at(indices[idx]);
    }
    
    virtual void update()
    {
        
    }
};

//specilize update and free for Transform hierarchy
struct Transform;
template<>
void cmp_type_t<Transform>::update();
template<>
void cmp_type_t<Transform>::free(cmp_base* cmp);
#endif
