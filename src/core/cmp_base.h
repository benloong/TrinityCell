//
//  cmp_base.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-23.
//
//

#ifndef __TrinityCell__cmp_base__
#define __TrinityCell__cmp_base__

#include "types.h"
enum E_CType
{
    CT_InvalidType          = 0 | 0x0,
    CT_Transform            = 0 | 0x1,
    CT_Renderable           = 0 | 0x2,
    CT_AudioSource          = 0 | 0x3,
    CT_Camera               = 0 | 0x4,
    CT_Light                = 0 | 0x5,
    CT_Scriptable           = 0 | 0x6,
};
struct cmp_type_base;

struct cmp_base {
    entity_id_t  ent_id;//host entity id
    handle_t     handle;//self handle
    cmp_type_base* type;//cmp_type registry
};

#endif /* defined(__TrinityCell__cmp_base__) */
