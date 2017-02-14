//
//  Config.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/9/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef GameProgram_hpp
#define GameProgram_hpp

#include <SDL.h>
#include "ShaderProgram.h"
#include "resources.h"
#include <functional>

namespace Graphics {
    struct Matrices {
        Matrix projection;
        Matrix view;
        Matrix model;
    };
    
    class Config {
    public:
        Matrices m;
        //TODO: Frame f;
        std::function<void()> loop;
        SDL_GLContext context;
        SDL_DisplayMode displayMode;
        SDL_Window* displayWindow;
        float lastFrameTicks = 0.0f;
        float thisFrameTicks = 0.0f;
        
        int w,h;
        float aspect;
        ShaderProgram* shader;
        
        Config();
        
        ~Config();
        
        float elapsed();
        
        void start();
        
        void setDisplayMode();
        
        void setVersionInfo();
        
        void createWindow();
        
        void setViewPort();
    };
}

#endif /* GameProgram_hpp */
