//
//  Game.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "libraries.h"
#include "resources.h"
#include "objects.h"

namespace Graphics {
    class Game: public EventFramework {
    private:
        SDL_Window* displayWindow;
        SDL_GLContext context;
        SDL_DisplayMode displayMode;
    public:
        ShaderProgram* shader;
        std::vector<Entities::Entity*> frame;
        int w,h;
        float lastFrameTicks;
        float thisFrameTicks;
        
        Matrix projectionMatrix;
        Matrix modelMatrix;
        Matrix viewMatrix;
        
        Game();
        
        ~Game();
        
        virtual void setup() = 0;
        
        void start();
        
        virtual void update(float elapsed);
        
        void render();
    };
}

#endif /* Game_hpp */
