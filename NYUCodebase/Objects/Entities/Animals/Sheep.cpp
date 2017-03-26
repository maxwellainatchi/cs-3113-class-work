//
//  Sheep.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Sheep.hpp"

namespace Entities {
    Sheep::Sheep(std::string imageName, Position::Rectangle pen, Position::Vector2D velocity): Animal(imageName, pen, velocity), speed(velocity.magnitude()) {
        t.action = λ() {
            guard (arc4random_uniform(UINT32_MAX) > 0.1*UINT32_MAX) else { return; }
            auto direction = static_cast<Position::Vector2D::Direction>(arc4random_uniform(4));
            velocity = Position::Vector2D::directionVector(direction) * speed;
        };
        t.start();
    }
    
    Sheep::~Sheep() {
        t.stop();
    }
    
    void Sheep::update(float elapsed) {
        t.increment(elapsed);
        Animal::update(elapsed);
    }
}
