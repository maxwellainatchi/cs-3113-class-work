//
//  Utils.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 4/14/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include <stdio.h>
#include <string>

inline void LOG(std::string message) {
    printf("LOG: %s\n", message.c_str());
}


inline float lerp(float v0, float v1, float t) {
    return (1.0-t)*v0 + t*v1;
}
