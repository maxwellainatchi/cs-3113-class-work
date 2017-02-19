//
//  Player.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Player.hpp"

namespace Entities {
    Player::Player(std::string imageName, Graphics::Coordinates pen): Entity(imageName), pen(pen) {}
    
    void Player::registerMovementHandlers(Graphics::EventFramework* g, std::set<Graphics::Vector2D::Direction> directions) {
        for (Graphics::Vector2D::Direction d : directions) {
            if (controlScheme.count(d)) {
                g->registerKeyHandler(controlScheme[d], [this, d] () {
                    this->moveDirection = d;
                });
                g->registerKeyHandler(controlScheme[d], [this, d] () {
                    this->moveDirection = Graphics::Vector2D::Direction::none;
                }, true);
            }
        }
    }
    
    void Player::update(float elapsed) {
        Graphics::Vector2D directionVector = Graphics::Vector2D::directionVector(moveDirection);
        move(directionVector * 2, elapsed);
        if (position.bounds().top > pen.bounds().top || position.bounds().bottom < pen.bounds().bottom || position.bounds().left < pen.bounds().left || position.bounds().right > pen.bounds().right) {
            move(directionVector * -2, elapsed);
        }
        Entity::update(elapsed);
    }
}
