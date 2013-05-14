//
//  type_identifier.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-14.
//
//

#ifndef TrinityCell_type_identifier_h
#define TrinityCell_type_identifier_h

struct type_id
{
    type_id(const type_id&) = delete;
    const type_id& operator=(const type_id &) = delete;
    int id;
};

template <typename Type>
struct identifier {
    static type_id id;
};

template <>
struct identifier<void>{
    static type_id id;
};

type_id identifier<void>::id = {0};

template <typename Type>
type_id identifier<Type>::id = {identifier<void>::id.id++};

#endif
