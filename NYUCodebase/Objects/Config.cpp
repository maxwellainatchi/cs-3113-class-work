//
//  Config.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/9/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Config.hpp"

namespace Graphics {
    Config::Config()  {
        SDL_Init(SDL_INIT_VIDEO);
        #ifdef _WINDOWS
            glewInit();
        #endif
        setDisplayMode();
        setVersionInfo();
        createWindow();
        setViewPort();
        loop = std::function<void()>();
        shader = new ShaderProgram(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");
    }
    
    Config::~Config() {
        SDL_Quit();
    }
    
    float Config::elapsed() {
        return thisFrameTicks - lastFrameTicks;
    }
    
    void Config::start() {
        m.projection.setOrthoProjection(-3.55, 3.55, -2.0f, 2.0f, -1.0f, 1.0f);
        shader->setModelMatrix(m.model);
        shader->setProjectionMatrix(m.projection);
        shader->setViewMatrix(m.view);
        SDL_Event event;
        bool done = false;
        while (!done) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                    done = true;
                }
                
                //TODO: Add event listeners here later
            }
            thisFrameTicks = (float)SDL_GetTicks()/1000.0f;
            //std::cout << "Tick: " << thisFrameTicks << std::endl;
            //TODO: f.update;
            //TODO: f.render;
            loop();
            lastFrameTicks = thisFrameTicks;
            SDL_GL_SwapWindow(displayWindow);
        }
    }
    
    void Config::setDisplayMode() {
        SDL_GetCurrentDisplayMode(0, &displayMode);
        w = displayMode.w;
        h = displayMode.h;
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    void Config::setVersionInfo() {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    }
    
    void Config::createWindow() {
        displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);
        
        // Assign OpenGL context
        context = SDL_GL_CreateContext(displayWindow);
        SDL_GL_MakeCurrent(displayWindow, context);
    }
    
    void Config::setViewPort() {
        glViewport(0, 0, w, h);
        aspect = (float)w/(float)h;
    }
}
