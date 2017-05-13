//
//  Game.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Game.hpp"

// MARK: - Frame

void Frame::insertBackground(Entity *entity) {
    backgrounds.insert(entity);
    renderable.insert(entity);
    all.insert(entity);
}

void Frame::insertStatic(Entity *entity) {
    statics.insert(entity);
    renderable.insert(entity);
    collideable.insert(entity);
    all.insert(entity);
}

void Frame::insertDynamic(Entity *entity) {
    dynamics.insert(entity);
    renderable.insert(entity);
    collideable.insert(entity);
    updateable.insert(entity);
    all.insert(entity);
}

void Frame::clear() {
    backgrounds.clear();
    statics.clear();
    dynamics.clear();
    renderable.clear();
    updateable.clear();
    collideable.clear();
    all.clear();
}

// MARK: - Game
// MARK: - Private

// MARK: Stages of the game

void Game::configure() {
    for (var frame in frames) {
        for (var entity in frame.second.all) {
            entity->setup();
        }
    }
}

void Game::loop() {
    LOG("Game loop is beginning", INFO);
    SDL_Event event;
    done = false;//, firstLoop = true;
    lastFrameTicks = (float)SDL_GetTicks()/1000.0f;
    while (!done) {
        LOG("Loop cycle", DBG);
//        if (firstLoop) {didStart(); firstLoop = false;}
        
        LOG("Checking event handlers", DBG);
        DEBUG_TIME(true, "Event Handler Checking");
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                done = true;
                willEnd();
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
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        
        for (var keyCode in continuousKeyPressHandlers[state]) {
            if (keys[keyCode.first]) { keyCode.second(); }
        }
        
        for (var keyCode in continuousKeyUnpressHandlers[state]) {
            if (!keys[keyCode.first]) { keyCode.second(); }
        }
        
        DEBUG_TIME(false, "Event Handler Checking", DBG);
        
        guard(!done) else { break; }
        
        thisFrameTicks = (float)SDL_GetTicks()/1000.0f;
        var elapsed = thisFrameTicks - lastFrameTicks;
        elapsed *= 2;
        LOG("Elapsed", elapsed, DBG);
        LOG("Updating", DBG);
        willUpdate(elapsed);
        update(elapsed);
//        didUpdate(elapsed);
        
        lastFrameTicks = thisFrameTicks;
        
        LOG("Rendering", DBG);
        willRender();
        render();
//        didRender();
        
        // Tells the window to rerender
        SDL_GL_SwapWindow(displayWindow);
    }
}


// TODO: Collision checking should activate both collision responses.
void Game::update(float elapsed) {
    DEBUG_TIME(true, "Update");
    var fixedElapsed = std::min(elapsed,MAX_TIMESTEPS*FIXED_TIMESTEP);
    while (fixedElapsed > 0) {
        let timestep = std::min(fixedElapsed, FIXED_TIMESTEP);
        for (var timer in timers[state]) {
            timer->increment(timestep);
        }
        
        LOG("Checking collisions", DBG);
        DEBUG_TIME(true, "Collision Detection");
        for (var entity in frames[state].collideable) {
            for (var otherEntity in frames[state].collideable) {
                guard (entity->willCollideWith(otherEntity, elapsed, false)) else { continue; }
                if (entity->onCollide) {
                    entity->onCollide(otherEntity, elapsed);
                }
                if (otherEntity->onCollide) {
                    otherEntity->onCollide(entity, elapsed);
                }
            }
        }
        DEBUG_TIME(false, "Collision Detection", DBG);
        LOG("Enacting update", DBG);
        for (var entity in frames[state].updateable) {
            entity->update(timestep);
        }
        fixedElapsed -= timestep;
    }
    DEBUG_TIME(false, "Update", DBG);
}

void Game::render() {
    DEBUG_TIME(true, "Render");
    willRender();
    shader->setProjectionMatrix(projection);
    shader->setViewMatrix(view);
    
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Render all the things!
    LOG("Rendering background entities", NOID);
    for (var entity in frames[state].backgrounds) {
        entity->render(shader);
    }
    LOG("Rendering dynamic entities", NOID);
    for (var entity in frames[state].dynamics) {
        entity->render(shader);
    }
    LOG("Rendering static entities", NOID);
    for (var entity in frames[state].statics) {
        entity->render(shader);
    }
    DEBUG_TIME(false, "Render", DBG);
}

// MARK: - Public

Game::Game(std::string name) {
    DEBUG_TIME(true, "Init");
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
    innerBounds = window.uv;
    
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
    
    DEBUG_TIME(false, "Init", INFO);
}

Game::~Game() {
    for (var frame in frames) {
        for (var entity in frame.second.all) {
            delete entity;
        }
        frame.second.clear();
    }
    delete shader;
    SDL_Quit();
}

// MARK: Utility Methods

void Game::showLoading(bool firstRun) {
    this->state = LOADING;
    for (var entity in frames[LOADING].all) {
        entity->setup();
    }
}

void Game::start() {
    LOG("Game is starting", INFO);
    DEBUG_TIME(true, "Entity Configuration");
    willConfigure();
    configure();
//    didConfigure();
    DEBUG_TIME(false, "Entity Configuration", INFO);
    
    willStart();
    loop();
//    didEnd();
}

void Game::changeState(State state) {
    LOG("Changing state from " + self.state + " to " + state);
    DEBUG_TIME(true, "State Change");
    willChangeState(state);
    for (var timer in timers[this->state]) {
        timer->stop();
    }
    this->state = state;
    for (var timer in timers[state]) {
        timer->start();
    }
//    didChangeState();
    DEBUG_TIME(false, "State Change", DBG);
}

void Game::createState(State name) {
    frames[name] = Frame();
}
