 //
//  Game.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Game.hpp"

namespace Graphics {
    Game::Game(std::string name): pausekey(SDL_SCANCODE_SPACE) {
        // Initializes video display
        SDL_Init(SDL_INIT_VIDEO);
        
        // Fetches info about the current display
        SDL_GetCurrentDisplayMode(0, &displayMode);
        
        // Set screen size
        window.pixels = Position::Rectangle({0, 0}, {static_cast<float>(displayMode.w), static_cast<float>(displayMode.h)});
        window.pixels = Position::Rectangle({0, 0}, {640 * 2, 360 * 2});
        float ortho_width = 3.55f;
        float ortho_height = 2.0f;
        projectionMatrix.setOrthoProjection(-ortho_width, ortho_width, -ortho_height, ortho_height, -1.0f, 1.0f);
        window.uv = Position::Rectangle({-ortho_width, -ortho_height}, {ortho_width, ortho_height});
        
        // Creates the window
        displayWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window.pixels.width(), window.pixels.height(), SDL_WINDOW_OPENGL);
        glViewport(0, 0, window.pixels.width(), window.pixels.height());
        
        // Points the stupid globals that SDL uses to this window
        context = SDL_GL_CreateContext(displayWindow);
        SDL_GL_MakeCurrent(displayWindow, context);
        
        // Some windows stuff
        #ifdef _WINDOWS
            glewInit();
        #endif
        
        // Initializes the shader, which draws things on screen
        shader = new ShaderProgram(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");
        glUseProgram(shader->programID);
        
        // Enable blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    Game::~Game() {
        for (var frame in frames) {
            for (var entity in frame.second) {
                delete entity;
            }
            frame.second.clear();
        }
        delete shader;
        SDL_Quit();
    }
    
    void Game::setup() {}
    
    void Game::initialize() {
        if (pausekey == SDL_SCANCODE_UNKNOWN) return;
        registerKeyHandler(pausekey, {PAUSED, RUNNING}, [&] () {
            if (state == RUNNING) {
                state = PAUSED;
            } else {
                state = RUNNING;
            }
            this->render();
        });
    }
    
    void Game::willStart() {}
    
    void Game::start() {
        setup();
        initialize();
        willStart();
        SDL_Event event;
        bool done = false;
        lastFrameTicks = (float)SDL_GetTicks()/1000.0f;
        while (!done) {
            while (SDL_PollEvent(&event)) {
                //TODO: Figure out why if 2 players try to move at the same time, it sometimes fails one.
                // -- Has something to do with key repeat cancelling other repeats out
                if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                    done = true;
                } else if (event.type == SDL_KEYDOWN) {
                    var keycode = event.key.keysym.scancode;
                    if (keyDownHandlers[state].count(keycode)) {
                        keyDownHandlers[state][keycode]();
                    }
                } else if (event.type == SDL_KEYUP) {
                    var keycode = event.key.keysym.scancode;
                    if (keyUpHandlers[state].count(keycode)) {
                        keyUpHandlers[state][keycode]();
                    }
                }
            }
            
            thisFrameTicks = (float)SDL_GetTicks()/1000.0f;
            update(thisFrameTicks - lastFrameTicks);
            lastFrameTicks = thisFrameTicks;
            render();
            
            // swapWindow is separated so you can override render()
            swapWindow();
        }
        willEnd();
    }
    
    void Game::update(float elapsed) {
        var fixedElapsed = std::min(elapsed,MAX_TIMESTEPS*FIXED_TIMESTEP);
        while (fixedElapsed > 0) {
            let timestep = std::min(fixedElapsed, FIXED_TIMESTEP);
            for (var timer in timers[state]) {
                timer->increment(timestep);
            }
            for (var entity in frames[state]) {
                entity->update(timestep);
            }
            fixedElapsed -= timestep;
        }
    }
    
    std::string Game::willChangeState(std::string newState) {
        return state;
    }
    
    void Game::render() {
        shader->setProjectionMatrix(projectionMatrix);
        shader->setViewMatrix(viewMatrix);
        
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Render all the things!
        for (Entities::Entity* entity in frames[state]) {
            entity->draw(shader);
            for (Entities::Entity* otherEntity in frames[state]) {
                guard(entity->onCollide && entity->isCollidingWith(otherEntity)) else { continue; }
                entity->onCollide(otherEntity);
            }
        }
    }
    
    void Game::willEnd() {}
    
    void Game::swapWindow() {
        // Tells the window to rerender
        SDL_GL_SwapWindow(displayWindow);
    }
    
    void Game::changeState(std::string state) {
        this->state = willChangeState(state);
    }
}
