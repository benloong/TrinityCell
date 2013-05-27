//
//  transform.cpp
//  TrinityCell
//
//  Created by he qianjun on 13-5-20.
//
//

#include "transform.h"
#include "context.h"
#include "cmp_type.h"
#include "math.h"

template<>
void cmp_type_t<Transform>::update()
{
    Transform* trans = nullptr;
    Transform* parent = nullptr;
    for (int i = 0; i < next_idx; ++i) {
        trans = (Transform*)data[indices[i]];
        trans->world_mat = trans->local_mat;
        if (trans->parent != INVALID_HANDLE) {
            parent = (Transform*)data[indices[HANDLE_INDEX(trans->parent)]];
            trans->world_mat = Math::mul(trans->local_mat, parent->world_mat);
        }
    }
}

template <>
void cmp_type_t<Transform>::free(cmp_base* cmp)
{
    handle_t h = cmp->handle;
    assert(h != INVALID_HANDLE && "try to free an invalid handle.");
    size_t idx = HANDLE_INDEX(h);
    size_t key = HANDLE_KEY(h);
    assert(idx < max_size && "bad handle index.");
    assert(key == keys[idx] && "bad handle key.");
    keys[idx] += 1;
    
    //swap back and idx
    size_t last_idx = --next_idx;
    if(last_idx == idx) return;
    
    cmp_base* last_cmp = at(indices[last_idx]);
    
    std::swap(indices[idx], indices[last_idx]);
    std::swap(keys[idx], keys[last_idx]);
    
    handle_t old_handle =  last_cmp->handle;
    last_cmp->handle = MAKE_HANDLE(idx, HANDLE_KEY(old_handle));
    ((pointer_type)cmp)->~comp_type();
}

namespace SceneGraph {
    
    void setParent(Transform* self, Transform* parent)
    {
        Transform* old_parent = getParent(self);
        Transform* old_prev_sibling = (Transform*) self->type->resolve(self->prev_sibling);
        Transform* old_next_sibling = (Transform*) self->type->resolve(self->next_sibling);
        
        if (old_parent != nullptr && old_parent->first_child == self->handle)
        {
            old_parent->first_child = self->next_sibling;
        }
        
        if (old_prev_sibling != nullptr)
        {
            old_prev_sibling->next_sibling = self->next_sibling;
        }
        
        if (old_next_sibling != nullptr)
        {
            old_next_sibling->prev_sibling = self->prev_sibling;
        }
        
        if(parent == nullptr)
        {
            self->parent = INVALID_HANDLE;
            self->next_sibling = INVALID_HANDLE;
            self->prev_sibling = INVALID_HANDLE;
            self->level = 0;
            return;
        }
        
        Transform* next_sibling = (Transform*) parent->type->resolve(parent->first_child);
        self->parent = parent->handle;
        self->next_sibling = parent->first_child;
        self->level = parent->level+1;
        parent->first_child = self->handle;
        
        if (next_sibling != nullptr)
        {
            next_sibling->prev_sibling = self->handle;
        }
    }
    
    Transform* getParent(Transform* self)
    {
        Transform* parent = (Transform*)self->type->resolve(self->parent);
        return parent;
    }
    
    Transform* getRoot(Transform* self)
    {
        Transform* root = self;
        Transform* parent = getParent(root);
        while (parent != nullptr) {
            root = parent;
            parent = getParent(parent);
        }
        return root;
    }
    
    int childCount(Transform* self)
    {
        int count = 0;
        Transform* child = (Transform* )self->type->resolve(self->first_child);
        while (child != nullptr) {
            child = (Transform*) child->type->resolve(child->next_sibling);
            count++;
        }
        return count;
    }
    
    Transform* getChild(Transform* self, int index)
    {
        int curr = 0;
        Transform* child = (Transform*) self->type->resolve(self->first_child);
        while (child != nullptr && curr != index) {
            child = (Transform*) child->type->resolve(child->next_sibling);
            curr++;
        }
        return child;
    }
    
    void update()
    {
        
    }
}