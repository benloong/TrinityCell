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

void Transform::init()
{
    

}

void Transform::uninit()
{
    
}

namespace Hierarchy {
    typedef InstancePool<Transform, Transform::MAX_COUNT> pool_type;
    
    enum {
        Dirty_Child = 0x1,
        Dirty_All   = 0x2
    };
    
    void setParent(handle_t trans, handle_t parent)
    {
        auto compMgr = cell::ctx->getCompManager();
        Transform * child = compMgr->resolveHandle<Transform>(trans);
        Transform * newParent = compMgr->resolveHandle<Transform>(parent);
        assert(child != nullptr && "null child transform.");
        Transform * oldParent = compMgr->resolveHandle<Transform>(child->parent);
        
        handle_t newNext = 0;
        if (newParent != nullptr) {
            newNext = newParent->first_child;
            auto next = compMgr->resolveHandle<Transform>(newParent->first_child);
            if(next != nullptr) {
                next->prev_sibling = trans;
            }
            newParent->first_child = trans;
        }
        
        if (oldParent!= nullptr && oldParent->first_child == trans) {
            oldParent->first_child = child->next_sibling;
        }
        if (child->prev_sibling) {
            compMgr->resolveHandle<Transform>(child->prev_sibling)->next_sibling = child->next_sibling;
        }
        
        child->parent = parent;
        child->next_sibling = newNext;
        child->prev_sibling = 0;
        child->bitmask |= Dirty_All;
    }
    
    handle_t getParent(handle_t trans)
    {
        auto p = cell::ctx->getCompManager()->resolveHandle<Transform>(trans);
        if(p != nullptr) return p->parent;
        return 0;
    }
    
    handle_t getRoot(handle_t trans)
    {
        handle_t root = trans;
        
        while (root != 0) {
            trans = getParent(trans);
            if (!trans)
                break;
            root = trans;
        }
        return root;
    }
    
    void updateHierarchy()
    {
        
    }
    
}