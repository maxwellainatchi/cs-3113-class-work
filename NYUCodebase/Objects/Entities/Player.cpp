//
//  Player.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Player.hpp"

namespace Entities {
    Player::Player(Graphics::SpriteSheet* spriteSheet, std::string name, Position::Rectangle pen): Sprite(spriteSheet, name), pen(pen) {}
    
    void Player::registerMovementHandlers(Graphics::EventFramework* g, std::vector<std::string> states, std::set<Position::Vector2D::Direction> directions) {
        for (Position::Vector2D::Direction d : directions) {
            if (controlScheme.count(d)) {
                g->registerKeyHandler(controlScheme[d], states, [this, d] () {
                    this->moveDirection = d;
                });
                g->registerKeyHandler(controlScheme[d], states,[this, d] () {
                    this->moveDirection = Position::Vector2D::Direction::none;
                }, true);
            }
        }
    }
    
    void Player::update(float elapsed) {
        Entity::update(elapsed);
        Position::Vector2D directionVector = Position::Vector2D::directionVector(moveDirection);
        move(directionVector * speed, elapsed);
        var without = bounds.withoutness(pen);
        guard (without.x == 0 && without.y == 0) else {
            move(directionVector * -speed, elapsed);
        }
    }
}
