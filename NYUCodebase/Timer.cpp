//
//  Timer.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 3/20/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Timer.hpp"

Timer::Timer(float interval): interval(interval) {}

void Timer::start() {
    state = Timer::STARTED;
}

void Timer::increment(float elapsed) {
    if (state == Timer::STOPPED) { return; }
    this->elapsed += elapsed;
    while (this->elapsed >= interval) {
        this->elapsed -= interval;
        action();
    }
}

void Timer::pause() {
    state = Timer::STOPPED;
}

void Timer::stop() {
    state = Timer::STOPPED;
    elapsed = 0;
}
