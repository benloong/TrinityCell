//
//  component.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-12.
//
//

#ifndef __TrinityCell__component__
#define __TrinityCell__component__
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <cassert>
#include <iostream>
#include <exception>
#include "component_detail.h"

namespace cell {
    
    
    /*
    template<typename Type>
    class InstancePool
    {
        struct InstanceEntry
        {
            int next_free : 16;
            int generation : 16;
            Type   instance;
        };
        
        
        
        std::vector<InstanceEntry> _instances;
        int  _first_free;
        
    public:
        
        InstancePool(size_t pool_size = 1<<16)
        {
            reset(pool_size);
        }
        
        ~InstancePool()
        {
            
        }
        
        void reset(size_t pool_size = 1<<16)
        {
            
            _instances.resize(pool_size);
            _first_free = 0;
            for (int i = 0; i < pool_size; ++i) {
                _instances[i].next_free = i+1;
                _instances[i].generation = 1;
                _instances[i].instance.reset(this);
                _instances[i].instance._cid = &Type::id;
            }
        }
        
        int alloc(void* p)
        {
            p = nullptr;
            int idx = _first_free;
            if(idx >= _instances.size()){
                throw std::out_of_range("out of pool size!");
            }
            _first_free = _instances[idx].next_free;
            p =  &(_instances[idx].instance);
            return idx;
        }
        
        virtual void free(int handle)
        {
            component_detail::handle_t h(handle);
            int idx = h._idx;
            assert(idx < _instances.size() && "out of pool size!");
            _instances[idx].next_free = _first_free;
            _first_free = idx;
        }
        
        Type* resolveHandle(int handle)
        {
            component_detail::handle_t h(handle);
            int idx = h._idx;
            if (idx > _instances.size()-1) {
                return nullptr;
            }
            return &(_instances[idx].instance);
        }
    };
    
    
    class ComponentManager
    {
    public:
    	ComponentManager()
        {
            
        }
        
    	~ComponentManager()
        {
            
        }
        
    	template <typename Type>
    	int addComponent(int ent)
    	{
            void * cid = &Type::id;
            if(!_pool_per_comp[cid]) {
                _pool_per_comp[cid].reset(new InstancePool<Type>());
            }
            Type * comp = nullptr;
            return ((InstancePool<Type>*)_pool_per_comp[cid].get())->alloc(comp);
    	}

    	template <typename Type>
    	void destroyComonent(int handle)
        {
            
        }
        
        template< typename Type>
        void registerComponent(size_t max_size = 1<<16)
        {
            void* uid = &Type::id;
            _pool_per_comp[uid].reset(new InstancePool<Type>(max_size));
            _component_type_set.insert(uid);
        }
        
    private:
        std::map<void*, std::unique_ptr<component_detail::instance_pool> > _pool_per_comp;
        std::set<void*> _component_type_set;
    };
    
    template <typename Type>
    struct id_base : public component_detail::type_id
    {
    };
    
    // concrete component should drive this template like this
    // class MyComponent : public ComponentBase<MyComponent>
    template<typename Type>
    class ComponentBase : public component_detail::component_base
    {
    public:
        static id_base<Type> id;
        void reset(InstancePool<Type> *pool)
        {
            _pool = pool;
            _ent = -1;
        }
        friend class InstancePool<Type>;
    };
    
    template<typename Type>
    id_base<Type> ComponentBase<Type>::id;
    */
    namespace EntityUtils
    {
        template<typename Type>
        Type* allocate(uint32_t ent, uint32_t * chain, void *misc = nullptr);
        template<typename Type>
        Type* resolveHandle(uint32_t comp_handle);
        
        //get one component of type that belongs to entity
        template<typename Type>
        Type* getComponent(uint32_t ent, uint32_t* chain);
        //get the first component in host's chain that implements the Type interface
        template<typename Type>
        Type* getComponentThatImplemens(uint32_t ent, uint32_t* chain);
        
        //get all components of type in entity , up to a max of count instances
        //count should be passed with the size of the component array.
        // on return , count will contain the number of matching components, up to the specified limit.
        template<typename Type>
        Type** getComponents(uint32_t ent, uint32_t chain, uint32_t& count);
        
        template<typename Type>
        Type** getComponentsThatImplements(uint32_t ent, uint32_t chain, uint32_t& count);
        
        template<typename Type>
        void free(uint32_t comp_handle, uint32_t ent, uint32_t &chain);
        
        void freeAll(uint32_t ent);
        
        template<typename Type>
        Type* valid_cast(void* comp);
    }
    
    namespace SystemUtils
    {
        //get a list of component types that implement the interface of the given componet type
        //count should be passed with the size of the component array.
        //on return , count will contain the number of matching components, up to the specified limit.
        template<typename Type>
        Type* getTypesThatImplements(uint32_t* count);
        
        //returns whether component type implements interface
        bool isTypeImplements(uint32_t type_id, uint32_t interface_id);
        
        //returns the number of comonents of type that are currently allocated
        uint32_t getNumAllocated(uint32_t type_id);
        
        //returns an array of pointers to all allocated components of type, their count, and their size
        void** getComponents(uint32_t type_id, uint32_t* count);
        
        //returns an array of all components of type(including unallocated instances!),
        //an array of the indices of allocated components within that array,
        //and the count of indices
        void* getComponentsIndexed(uint32_t type_id, uint16_t ** indices, uint32_t * count);
        
        void updateAllComponents(uint8_t stage);
    }
     
}

#endif /* defined(__TrinityCell__component__) */
