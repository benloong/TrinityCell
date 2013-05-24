//
//  timer.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-13.
//
//

#ifndef __TrinityCell__timer__
#define __TrinityCell__timer__

namespace cell {

    //game time in seconds
    //scalable timer 
    namespace Timer {
        float  getTimeScale();
        void   setTimeScale( float timeScale);
        float  getDeltaTime();
        float  getTime();
        float  getRealTime();
        void   resetTimer();

        //update timer per game loop 
        void update();
    }
}

#endif /* defined(__TrinityCell__timer__) */
