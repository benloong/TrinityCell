//
//  prealloc_object.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-14.
//
//

#ifndef TrinityCell_prealloc_object_h
#define TrinityCell_prealloc_object_h

#include <memory>

template <typename Type, int Size = 1024>
struct prealloc_object {
    typedef std::unique_ptr<Type[]> TypeArray;
    static TypeArray __allocated;
    static int __anchor;
};

template<typename Type, int Size>
typename prealloc_object<Type, Size>::TypeArray prealloc_object<Type, Size>::__allocated( new Type[Size]() );
template<typename Type, int Size>
int prealloc_object<Type, Size>::__anchor = 0;
#endif
