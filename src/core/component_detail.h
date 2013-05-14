//
//  component_base.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-14.
//
//

#ifndef __TrinityCell__component_base__
#define __TrinityCell__component_base__

namespace cell {
    
    typedef int entity_id_t;
    
    namespace component_detail {
        
        struct type_id
        {
        public:
            type_id(){ }
            ~type_id(){ }
        private:
            type_id( const type_id &);
            const type_id& operator=( const type_id& );
        };
        
        class instance_pool;
        class component_base
        {
        public:
            //trivial constructor and trivial destructor
            //no virtual destructor
            const type_id*   _cid;  // per concrete component type id
            entity_id_t _ent;       // entity id
            const instance_pool * _pool;
        };
        
        class instance_pool
        {
        public:
            instance_pool() { }
            virtual ~instance_pool() { }
            
            virtual void free(const int handle) = 0;
        };
        
        struct handle_t
        {
            union {
                struct {
                    int _idx : 16;
                    int _generation: 16;
                };
                int _uid;
            };
            
            handle_t(int uid): _uid(uid)
            {
                
            }
            
            handle_t(int idx, int generation): _idx(idx), _generation(generation)
            {
                
            }
        };
    }
    
    
}//end cell namespace

#endif /* defined(__TrinityCell__component_base__) */
