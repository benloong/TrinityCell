//
//  type_identifier.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-14.
//
//

#ifndef TrinityCell_type_identifier_h
#define TrinityCell_type_identifier_h

typedef int16_t type_id;
template <typename Type, int16_t ID>
struct identifier {
    static type_id id;
};

template<>
type_id identifier<void, 0>::id = 0;

template <typename Type, int16_t ID>
type_id identifier<Type, ID>::id = ID ;

#endif
