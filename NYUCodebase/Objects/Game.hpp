//
//  Game.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#define RUNNING "running"
#define PAUSED "paused"
#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6

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
        std::map<std::string, std::set<Entities::Entity*>> frames;
        std::map<std::string, std::set<Graphics::Timer*>> timers;
        
        Window window;
        float lastFrameTicks;
        float thisFrameTicks;
        Matrix projectionMatrix;
        Matrix modelMatrix;
        Matrix viewMatrix;
        std::string state;
        SDL_Scancode pausekey;
        
        Game(std::string name);
        
        ~Game();
        
        // MARK: - Stages of the game
        
        /// For setting up game state
        virtual void setup();
        
        /// Initializes things dependent on game state
        void initialize();
        
        /// Anything that needs to happen right before the game starts
        virtual void willStart();
        
        /// Starts the game loop
        void start();
        
        /// Updates the game
        virtual void update(float elapsed);
        
        /// Renders the game
        virtual void render();
        
        /// Anything that needs to happen right after the game ends
        virtual void willEnd();
        
        // MARK: - Utility methods
        
        /// Rerenders the window
        void swapWindow();
    };
}

#endif /* Game_hpp */
