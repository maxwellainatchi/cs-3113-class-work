//
//  Player.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Player.hpp"

namespace Entities {
    Player::Player(Graphics::SpriteSheet* spriteSheet, std::string name, Graphics::Coordinates pen): Sprite(spriteSheet, name), pen(pen) {}
    
    void Player::registerMovementHandlers(Graphics::EventFramework* g, std::vector<std::string> states, std::set<Graphics::Vector2D::Direction> directions) {
        for (Graphics::Vector2D::Direction d : directions) {
            if (controlScheme.count(d)) {
                g->registerKeyHandler(controlScheme[d], states, [this, d] () {
                    this->moveDirection = d;
                });
                g->registerKeyHandler(controlScheme[d], states,[this, d] () {
                    this->moveDirection = Graphics::Vector2D::Direction::none;
                }, true);
            }
        }
    }
    
    void Player::update(float elapsed) {
        Graphics::Vector2D directionVector = Graphics::Vector2D::directionVector(moveDirection);
        move(directionVector * speed, elapsed);
        auto without = withoutness(pen);
        if (!(without.x == 0 && without.y == 0)) {
            move(directionVector * -speed, elapsed);
        }
        Entity::update(elapsed);
    }
}
