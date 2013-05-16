//
//  component_types.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-16.
//
//

#ifndef TrinityCell_component_types_h
#define TrinityCell_component_types_h

//one component type per concrete component
//first 8 bits for class type, second 8 bits for parent type
//0 - 127 system reserved
enum class COMPONENT_TYPE : unsigned short
{
    CT_INVLID_TYPE          = 0<<8 | 0x0,
    CT_TRANSFORM            = 0<<8 | 0x1,
    CT_RENDERER             = 0<<8 | 0x2,
    CT_AUDIO_SOURCE         = 0<<8 | 0x3,
    CT_CAMERA               = 0<<8 | 0x4,
    CT_LIGHT                = 0<<8 | 0x5,
};

#endif
