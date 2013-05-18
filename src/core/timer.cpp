//
//  timer.cpp
//  TrinityCell
//
//  Created by he qianjun on 13-5-13.
//
//

#include "timer.h"
#include <chrono>

namespace cell {
    namespace Timer {
        using namespace std::chrono;

        struct TimerImpl 
        {
            float scale;    // time scale
            float delta;    //frame delta time
            float time;     //scaled time
            float real_time;//real time
            float start;    // start time
        };

        TimerImpl timer = {1.0f, 0, 0, 0};

        auto t0  = high_resolution_clock::now();

        const float to_seconds = 1.0f/10000000;
        void update()
        {
            auto t1 = high_resolution_clock::now();
            high_resolution_clock::rep delta = (t1-t0).count();
            float delta_in_secs = delta * to_seconds;
            timer.real_time += delta_in_secs;
            timer.delta = delta_in_secs * timer.scale;
            timer.time += timer.delta;
            t0 = t1;
        }

        float getTimeScale() {
            return timer.scale;
        }

        void setTimeScale(float scale)
        {
            timer.scale = scale;
        }

        float getDeltaTime()
        {
            return timer.delta;
        }

        float getTime() 
        {
            return timer.time;
        }

        float getRealTime()
        {
            return timer.real_time;
        }

        void resetTimer()
        {
            timer.scale = 1.0f;
            timer.delta = 0;
            timer.start = 0;
            timer.time = 0;
            timer.real_time = 0;

            t0 = high_resolution_clock::now();
        }
    }
}