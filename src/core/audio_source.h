//
//  audio_source.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-20.
//
//

#ifndef __TrinityCell__audio_source__
#define __TrinityCell__audio_source__

#include "component.h"

class AudioSource : public DCS::Component_T<AudioSource, 1024> {
    float volume;
    float time;
    bool  loop;
    int   clipID; //audio clip id
    
public:
    void Play();
};
#endif /* defined(__TrinityCell__audio_source__) */
