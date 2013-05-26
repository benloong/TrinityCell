//
//  types.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-22.
//
//

#ifndef TrinityCell_types_h
#define TrinityCell_types_h

#include <cstdint>
#include <cstddef>
#include <limits>
#include <assert.h>

typedef uint16_t type_id_t;
typedef uint16_t cmp_id_t;
typedef uint32_t entity_id_t;
typedef uint32_t handle_t;
typedef uint16_t index_t;

static const entity_id_t INVALID_ENTITY_ID = 0;
static const handle_t INVALID_HANDLE = 0;

#define HANDLE_INDEX(h) (((h)>>16) & 0xffff)
#define HANDLE_KEY(h) ((h) & 0xffff)
#define MAKE_HANDLE(idx,key) (((idx)<<16) | (key))

#endif
