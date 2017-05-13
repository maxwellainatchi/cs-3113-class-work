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
#include <map>
#include <sstream>
#include <ctime>

enum LOG_LEVEL: int { NOID = 0, DBG, INFO, WRN, ERR, FATAL };
#if DEBUG == 1
inline const char* LOG_LEVEL_TO_STRING(LOG_LEVEL l) {
    return  l < 1 ? "PARANOID"  :
            l < 2 ? "DEBUG"     :
            l < 3 ? "INFO"      :
            l < 4 ? "WARNING"   :
            l < 5 ? "ERROR"     :
                    "FATAL"     ;
}
#endif
inline LOG_LEVEL DBG_LEVEL = LOG_LEVEL::INFO;
inline LOG_LEVEL DEF_LEVEL = LOG_LEVEL::INFO;

inline void LOG(std::string message, LOG_LEVEL level = DEF_LEVEL) {
#if DEBUG == 1
    if (level >= DBG_LEVEL) {
        printf("LOG (%s): %s\n", LOG_LEVEL_TO_STRING(level),  message.c_str());
    }
#endif
}

inline void LOG(std::string name, float statistic, LOG_LEVEL level = DEF_LEVEL) {
#if DEBUG == 1
    if (level >= DBG_LEVEL) {
        printf("LOG (%s): %s: %f\n", LOG_LEVEL_TO_STRING(level), name.c_str(), statistic);
    }
#endif
}

inline float NOW() {
    return (float) clock() / CLOCKS_PER_SEC;
}

#if DEBUG == 1
struct DEBUG_TIMER {
    float start;
    std::string statistic;
    float clock() {
        float now = NOW();
        float elapsed = now - start;
        start = now;
        return elapsed;
    }
    DEBUG_TIMER(std::string statistic): statistic(statistic), start(NOW()) { }
};

inline std::map<std::string, DEBUG_TIMER*> DEBUG_TIMERS;
#endif

inline void DEBUG_TIME(bool start, std::string statistic, LOG_LEVEL level = DEF_LEVEL) {
#if DEBUG == 1
    if (start) {
        if (DEBUG_TIMERS[statistic] != nullptr) {
            DEBUG_TIMERS[statistic]->start = NOW();
        } else {
            DEBUG_TIMERS[statistic] = new DEBUG_TIMER(statistic);
        }
    } else {
        LOG(statistic + " time", DEBUG_TIMERS[statistic]->clock(), level);
    };
#endif
}

inline bool getBit(int number, size_t n) {
    return (bool) ((number >> n) & 1);
}

inline int setBit(int number, size_t n, bool set) {
    return number ^ ((-((int) set) ^ number) & (1 << n));
};

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
