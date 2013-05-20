//
//  entity.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-14.
//
//

#ifndef TrinityCell_entity_h
#define TrinityCell_entity_h

typedef int entity_id_t;
typedef int handle_t;

struct Entity
{
    entity_id_t  id;
    
    handle_t     trans;
    
    char*        name;
};

#endif
