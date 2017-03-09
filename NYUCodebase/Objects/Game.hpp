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
        
        struct Window {
            Graphics::Coordinates uv;
            Graphics::Coordinates pixels;
        };
    public:
        ShaderProgram* shader;
        std::vector<Entities::Entity*> frame;
        Window window;
        float lastFrameTicks;
        float thisFrameTicks;
        Matrix projectionMatrix;
        Matrix modelMatrix;
        Matrix viewMatrix;
        
        Game(std::string name);
        
        ~Game();
        
        virtual void setup() = 0;
        
        void start();
        
        virtual void update(float elapsed);
        
        virtual void render();
        
        void swapWindow();
    };
}

#endif /* Game_hpp */
