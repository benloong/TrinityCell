//
//  transform.cpp
//  TrinityCell
//
//  Created by he qianjun on 13-5-20.
//
//

#include "transform.h"
#include "context.h"
#include "component_manager.h"

Transform::Transform()
{
    
}

void Transform::setParent(Transform *parent)
{
    ComponentTraits<Transform>::pool_type *pool = cell::ctx->getCompManager()->getComponentInstancePool<Transform>();
}