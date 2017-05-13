//
//  libraries.h
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef libraries_h
    #define libraries_h

    #ifdef _WINDOWS
        #include <GL/glew.h>
    #endif

    #include <SDL.h>
    #include <SDL_opengl.h>
    #include <SDL_image.h>
    #include "stb_image.h"
    #include "ShaderProgram.h"
    #include "Matrix.h"
    #include <vector>
    #include <string>
    #include <random>
    #include <math.h>
    #include <functional>
    #include <map>
    #include <set>
    #include <algorithm>
    #include "Utils.cpp"
    #include "TypeWrapper.cpp"

    #include "macros.h"
    typedef std::string State;

    typedef std::function<void(void)> InstantAction;
    typedef std::function<void(float)> TimedAction;
    typedef std::function<void(ShaderProgram*)> ShaderAction;
    typedef std::function<void(std::string)> StateAction;
    typedef std::function<bool(void)> Validator;
    inline float SMALL_AMOUNT = 0.001f;

#endif /* libraries_h */
