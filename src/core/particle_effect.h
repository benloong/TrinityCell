//
//  particle_effect.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-20.
//
//

#ifndef __TrinityCell__particle_effect__
#define __TrinityCell__particle_effect__


#include "cmp_base.h"
#include <vector>

class ParticleEffect : public cmp_base
{
public:
    struct Particle {
        float position[3];
        float velocity;
        float lifetime;//This is the time in seconds for how long this particle will remain alive. When the lifetime drops below zero the Particle will be killed.
        float size;
        float rotation[4];
        float angluarVelocity;
        float color[3];
    };
    
    void play();
    void stop();
    void pause();
    void clear();
    void emit();
    
    
    int particleCount;
    float time;
    std::vector<Particle> particles;
};

#endif /* defined(__TrinityCell__particle_effect__) */
