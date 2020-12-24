#include "Arduino.h"

#ifndef utils_h
#define utils_h

class utils{
    public:
        utils();
        void init();
        int motor_speed(int speed);
        int distance_to_degree(float mm_dist);
};

#endif