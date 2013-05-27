//
//  audio_source.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-20.
//
//

#ifndef __TrinityCell__audio_source__
#define __TrinityCell__audio_source__

#include "cmp_base.h"

class AudioSource : public cmp_base {
    float volume;
    float time;
    bool  loop;
    int   clipID; //audio clip id
    
public:
    void play();
};
#endif /* defined(__TrinityCell__audio_source__) */
