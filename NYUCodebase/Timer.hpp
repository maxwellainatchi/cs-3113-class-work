//
//  Timer.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 3/20/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#include "libraries.h"


class Timer {
public:
    void increment(float elapsed);
    
    enum State { STOPPED, STARTED };
    State state;
    float interval;
    float elapsed;
    InstantAction action;
    
    Timer(float interval);
    
    void start();
    void pause();
    void stop();
    void kill();
};

#endif /* Timer_hpp */
