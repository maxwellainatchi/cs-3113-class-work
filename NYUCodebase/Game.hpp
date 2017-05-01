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

class Game: public EventFramework {
private:
    // MARK: - Config
    
    Vec2 aspectRatio = {16.0f, 9.0f};
    
    // MARK: - Private
    struct Window {
        Rectangle uv;
        Rectangle pixels;
    };
    
    SDL_Window* displayWindow;
    SDL_GLContext context;
    SDL_DisplayMode displayMode;
    ShaderProgram* shader;
    
    float lastFrameTicks;
    float thisFrameTicks;
    
    // MARK: Stages of the game
    
    /// Runs the setup for each entity
    void configure();
    
    /// Starts the game loop
    void loop();
    
    /// Updates the game
    void update(float elapsed);
    
    /// Renders the game
    void render();
public:
    // MARK: - Public
    std::map<std::string, std::set<Entity*>> frames;
    std::map<std::string, std::set<Timer*>> timers;
    
    Matrix model;
    Matrix projection;
    Matrix view;
    
    Window window;
    std::string state;
    
    Game(std::string name);
    ~Game();
    
    // MARK: Event listeners
    
    InstantAction willConfigure;
//    InstantAction didConfigure;
    
    InstantAction willStart;
//    InstantAction didStart;
    
    TimedAction willUpdate;
//    TimedAction didUpdate;
    
    StateAction willChangeState;
//    InstantAction didChangeState;
    
    InstantAction willRender;
//    InstantAction didRender;
    
    InstantAction willEnd;
//    InstantAction didEnd;
    
    
    // MARK: Utility methods
    
    void start();
    void changeState(State state);
    void createState(State name);
};

#endif /* Game_hpp */
