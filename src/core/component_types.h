//
//  component_types.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-16.
//
//

#ifndef TrinityCell_component_types_h
#define TrinityCell_component_types_h

#include "camera.h"
#include "transform.h"
#include "light.h"
#include "renderable.h"
#include "audio_source.h"
#include "scriptable.h"

//one component type per concrete component
//first 8 bits for class type, second 8 bits for parent type
//0 - 127 system reserved

enum class E_ComponentType : unsigned short
{
    CT_InvalidType          = 0 | 0x0,
    CT_Transform            = 0 | 0x1,
    CT_Renderable           = 0 | 0x2,
    CT_AudioSource          = 0 | 0x3,
    CT_Camera               = 0 | 0x4,
    CT_Light                = 0 | 0x5,
    CT_Scriptable           = 0 | 0x6,
};

#include "component_traits.h"
    
#endif
