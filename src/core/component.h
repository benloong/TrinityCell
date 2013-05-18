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
    
    /** 
        Component system design
        key template class: ComponentBaseT, ComponentManagerBaseT  fixed_size_pool  Handle_T
        Component derived from ComonentBaseT with a specified ManagerType 
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
        
        //void updateAllComponents(uint8_t stage);
    }
     
}

#endif /* defined(__TrinityCell__component__) */
