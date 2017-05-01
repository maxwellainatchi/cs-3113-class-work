//
//  Game.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Game.hpp"

// MARK: - Private

// MARK: Stages of the game

void Game::configure() {
    for (var frame in frames) {
        for (var entity in frame.second) {
            entity->setup();
        }
    }
}

void Game::loop() {
    SDL_Event event;
    bool done = false;//, firstLoop = true;
    lastFrameTicks = (float)SDL_GetTicks()/1000.0f;
    while (!done) {
//        if (firstLoop) {didStart(); firstLoop = false;}
        
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: case SDL_WINDOWEVENT_CLOSE:
                    done = true;
                    willEnd();
                    break;
                case SDL_KEYDOWN: {
                    var keycode = event.key.keysym.scancode;
                    if (keyDownHandlers[state].count(keycode)) {
                        keyDownHandlers[state][keycode]();
                    }
                    break;
                }
                case SDL_KEYUP: {
                    var keycode = event.key.keysym.scancode;
                    if (keyUpHandlers[state].count(keycode)) {
                        keyUpHandlers[state][keycode]();
                    }
                    break;
                }
            }
        }
        
        guard(!done) else { break; }
        
        thisFrameTicks = (float)SDL_GetTicks()/1000.0f;
        let elapsed = thisFrameTicks - lastFrameTicks;
        
        willUpdate(elapsed);
        update(elapsed);
//        didUpdate(elapsed);
        
        lastFrameTicks = thisFrameTicks;
        
        willRender();
        render();
//        didRender();
        
        // Tells the window to rerender
        SDL_GL_SwapWindow(displayWindow);
    }
}


// TODO: Collision checking should activate both collision responses.
void Game::update(float elapsed) {
    var fixedElapsed = std::min(elapsed,MAX_TIMESTEPS*FIXED_TIMESTEP);
    while (fixedElapsed > 0) {
        let timestep = std::min(fixedElapsed, FIXED_TIMESTEP);
        for (var timer in timers[state]) {
            timer->increment(timestep);
        }
        
        for (var entity in frames[state]) {
            for (var otherEntity in frames[state]) {
                guard (entity->willCollideWith(otherEntity, elapsed, false)) else { continue; }
                if (entity->onCollide) {
                    entity->onCollide(otherEntity, elapsed);
                }
                if (otherEntity->onCollide) {
                    otherEntity->onCollide(entity, elapsed);
                }
            }
            entity->update(timestep);
        }
        fixedElapsed -= timestep;
    }
}

void Game::render() {
    willRender();
    shader->setProjectionMatrix(projection);
    shader->setViewMatrix(view);
    
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Render all the things!
    for (var entity in frames[state]) {
        shader->setModelMatrix(entity->model);
        entity->render(shader);
    }
}

// MARK: - Public

Game::Game(std::string name) {
    // Initializes video display
    SDL_Init(SDL_INIT_VIDEO);
    
    // Fetches info about the current display
    SDL_GetCurrentDisplayMode(0, &displayMode);
    
    // Set screen size
//    window.pixels = Rectangle({0, 0}, {static_cast<float>(displayMode.w), static_cast<float>(displayMode.h)});
    window.pixels = Rectangle({0, 0}, aspectRatio * 80);
    var ortho = aspectRatio * 0.5f;
    projection.setOrthoProjection(-ortho.x, ortho.x, -ortho.y, ortho.y, -1.0f, 1.0f);
    window.uv = Rectangle({-ortho.x, -ortho.y}, aspectRatio.x, aspectRatio.y);
    
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
    
    // Setup default event listeners (doing nothing)
    willConfigure = EmptyInstantAction;
    willStart = EmptyInstantAction;
    willUpdate = EmptyTimedAction;
    willChangeState = EmptyStateAction;
    willRender = EmptyInstantAction;
    willEnd = EmptyInstantAction;
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

// MARK: Utility Methods

void Game::start() {
    willConfigure();
    configure();
//    didConfigure();
    
    willStart();
    loop();
//    didEnd();
}

void Game::changeState(State state) {
    willChangeState(state);
    for (var timer in timers[this->state]) {
        timer->stop();
    }
    this->state = state;
    for (var timer in timers[state]) {
        timer->start();
    }
//    didChangeState();
}

void Game::createState(State name) {
    frames[name] = std::set<Entity*>();
}
