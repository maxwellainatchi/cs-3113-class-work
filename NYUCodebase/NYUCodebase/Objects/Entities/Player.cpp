//
//  Player.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Player.hpp"

namespace Entities {
    Player::Player(std::string imageName): Entity(imageName) {}
    
    void Player::registerMovementHandlers(Graphics::EventFramework* g) {
        g->registerKeyHandler(SDL_SCANCODE_UP, [&] () {
            moveDirection = Graphics::Vector2D::Direction::up;
        });
        g->registerKeyHandler(SDL_SCANCODE_DOWN, [&] () {
            moveDirection = Graphics::Vector2D::Direction::down;
        });
        g->registerKeyHandler(SDL_SCANCODE_LEFT, [&] () {
            moveDirection = Graphics::Vector2D::Direction::left;
        });
        g->registerKeyHandler(SDL_SCANCODE_RIGHT,[&] () {
            moveDirection = Graphics::Vector2D::Direction::right;
        });
        for (SDL_Scancode code : {SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT}) {
            g->registerKeyHandler(code, [&] () {
                moveDirection = Graphics::Vector2D::Direction::none;
            }, true);
        }
    }
    
    
    
    void Player::update(float elapsed) {
        Graphics::Vector2D directionVector = Graphics::Vector2D::directionVector(moveDirection);
        move(directionVector * 2, elapsed);
        Entity::update(elapsed);
    }
}
