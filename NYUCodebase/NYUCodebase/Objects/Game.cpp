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
        SDL_Init(SDL_INIT_VIDEO);
        SDL_GetCurrentDisplayMode(0, &displayMode);
        w = displayMode.w;
        h = displayMode.h;
        displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);
        context = SDL_GL_CreateContext(displayWindow);
        SDL_GL_MakeCurrent(displayWindow, context);
        #ifdef _WINDOWS
            glewInit();
        #endif
        
        glViewport(0, 0, w, h);
        shader = new ShaderProgram(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");
        
        glUseProgram(shader->programID);
        glEnable(GL_BLEND);
        
        projectionMatrix.setOrthoProjection(-3.55, 3.55, -2.0f, 2.0f, -1.0f, 1.0f);
    }
    
    void Game::start() {
        setup();
        SDL_Event event;
        bool done = false;
        while (!done) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                    done = true;
                }
            }
            
            thisFrameTicks = (float)SDL_GetTicks()/1000.0f;
            update(thisFrameTicks - lastFrameTicks);
            lastFrameTicks = thisFrameTicks;
            render();
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            SDL_GL_SwapWindow(displayWindow);
        }
        SDL_Quit();
    }
    
    void Game::render() {
        shader->setProjectionMatrix(projectionMatrix);
        shader->setViewMatrix(viewMatrix);
        
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Render all the things!
        for (Graphics::Entity* entity : frame) {
            entity->draw(shader);
        }
    }
    
    void Game::update(float elapsed) {
        for (Graphics::Entity* entity : frame) {
            entity->update(elapsed);
        }
    }
}
