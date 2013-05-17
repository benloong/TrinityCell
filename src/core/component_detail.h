//
//  component_base.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-14.
//
//

#ifndef __TrinityCell__component_base__
#define __TrinityCell__component_base__

namespace cell {
    
    typedef uint32_t entity_id_t;
    
    struct ComponentBase
    {
        entity_id_t     _ent_id;       // entity id
        const uint16_t  _type_id;      // type id
        ComponentBase(uint16_t id) : _type_id(id) { }
    };
    
    //one unique type_id per concrete component
    template<typename _AllocType>
    struct ComponentBaseT : public ComponentBase
    {
        typedef _AllocType ManagerType;
        static const uint16_t type_id;
        ComponentBaseT() : ComponentBase(type_id) { }
    };
//    
//    template<typename Comp>
//    uint16_t ComponentBaseT<Comp>::type_id = 0;
}//end cell namespace

#endif /* defined(__TrinityCell__component_base__) */
