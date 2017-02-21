//
//  Sheep.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Sheep.hpp"

namespace Entities {
    Sheep::Sheep(std::string imageName, Graphics::Coordinates pen, Graphics::Vector2D velocity): Animal(imageName, pen, velocity), speed(velocity.magnitude()) {}
    
    void Sheep::update(float elapsed) {
        millAbout(elapsed);
        Animal::update(elapsed);
    }
    
    void Sheep::millAbout(float elapsed) {
        float timeLimit = 2.0;
        timeSinceLastMove += elapsed;
        if (timeSinceLastMove > timeLimit) {
            if (arc4random_uniform(UINT32_MAX) < 0.1*UINT32_MAX) {
                auto direction = static_cast<Graphics::Vector2D::Direction>(arc4random_uniform(4));
                velocity = Graphics::Vector2D::directionVector(direction) * speed;
                timeSinceLastMove = 0.0;
            }
        }
    }
}
