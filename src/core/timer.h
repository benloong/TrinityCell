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
    class Timer{
    public:
        float _timeScale;
        float _time;
        float _realTime;
        float _deltaTime;
        Timer();
        ~Timer();
        void update();
    };
}

#endif /* defined(__TrinityCell__timer__) */
