//
//  Game.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Game.hpp"

namespace Graphics {
    Game::Game() {
        // Initializes video display
        SDL_Init(SDL_INIT_VIDEO);
        
        // Fetches info about the current display
        SDL_GetCurrentDisplayMode(0, &displayMode);
        
        // Set screen size
        window.pixels = Graphics::Coordinates({0, 0}, {static_cast<float>(displayMode.w), static_cast<float>(displayMode.h)});
        window.pixels = Graphics::Coordinates({0, 0}, {640 * 2, 360 * 2});
        float ortho_width = 3.55f;
        float ortho_height = 2.0f;
        projectionMatrix.setOrthoProjection(-ortho_width, ortho_width, -ortho_height, ortho_height, -1.0f, 1.0f);
        window.uv = Graphics::Coordinates({-ortho_width, -ortho_height}, {ortho_width, ortho_height});
        
        // Creates the window
        displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window.pixels.width(), window.pixels.height(), SDL_WINDOW_OPENGL);
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
        for (Entities::Entity* entity : frame) {
            delete entity;
        }
        frame.clear();
        delete shader;
        SDL_Quit();
    }
    
    void Game::start() {
        setup();
        SDL_Event event;
        bool done = false;
        while (!done) {
            while (SDL_PollEvent(&event)) {
                //TODO: Figure out why if 2 players try to move at the same time, it sometimes fails one.
                if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                    done = true;
                } else if (event.type == SDL_KEYDOWN) {
                    auto keycode = event.key.keysym.scancode;
                    if (keyDownHandlers.count(keycode)) {
                        keyDownHandlers[keycode]();
                    }
                } else if (event.type == SDL_KEYUP) {
                    auto keycode = event.key.keysym.scancode;
                    if (keyUpHandlers.count(keycode)) {
                        keyUpHandlers[keycode]();
                    }
                }
            }
            
            thisFrameTicks = (float)SDL_GetTicks()/1000.0f;
            update(thisFrameTicks - lastFrameTicks);
            lastFrameTicks = thisFrameTicks;
            render();
        }
    }
    
    void Game::render() {
        shader->setProjectionMatrix(projectionMatrix);
        shader->setViewMatrix(viewMatrix);
        
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Render all the things!
        for (Entities::Entity* entity : frame) {
            entity->draw(shader);
        }
        
        // Tells the window to rerender
        SDL_GL_SwapWindow(displayWindow);
    }
    
    void Game::update(float elapsed) {
        for (Entities::Entity* entity : frame) {
            entity->update(elapsed);
        }
    }
}
