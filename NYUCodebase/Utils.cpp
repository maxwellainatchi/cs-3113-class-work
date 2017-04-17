//
//  Utils.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 4/14/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>

inline void LOG(std::string message) {
    printf("LOG: %s\n", message.c_str());
}


inline float lerp(float v0, float v1, float t) {
    return (1.0-t)*v0 + t*v1;
}

inline std::vector<std::string> tokenize(std::string str, char delim) {
    std::vector<std::string> retVal;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        retVal.push_back(token);
    }
    return retVal;
}
