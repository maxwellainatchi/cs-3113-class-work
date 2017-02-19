//
//  Texturey.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Texturey.hpp"

namespace Games {
    void Texturey::setup() {
        // Initialize players
        player1 = new Entities::Player("otherpicture.png", window.uv);
        player2 = new Entities::Player("picture.png", window.uv);
        
        // Add Entities to frame
        frame.push_back(new Entities::Sheep("thirdpicture.png", window.uv));
        frame.push_back(player1);
        frame.push_back(player2);
        
        // Assign initial positions
        float padding = 0.2f;
        player1->translate({window.uv.topLeft.x + player1->position.width()/2 + padding, window.uv.topLeft.y - window.uv.height()/2});
        player2->translate({window.uv.topRight.x - player2->position.width()/2 - padding, window.uv.topRight.y - window.uv.height()/2});
        
        // Add pause
        registerKeyHandler(SDL_SCANCODE_SPACE, [&] () {
            paused = !paused;
        });
        
        // Register player control schemes
        player1->controlScheme = Graphics::EventFramework::ControlSchemes::ArrowKeys;
        player2->controlScheme = Graphics::EventFramework::ControlSchemes::WASD;
        player1->registerMovementHandlers(this);
        player2->registerMovementHandlers(this);
    }
    
    void Texturey::update(float elapsed) {
        if (!paused) {
            Graphics::Game::update(elapsed);
        }
    }
}
