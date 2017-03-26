//
//  Animal.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Animal.hpp"

namespace Entities {
    Animal::Animal(std::string imageName, Position::Rectangle pen, Position::Vector2D velocity): Entities::Entity(imageName), pen(pen), velocity(velocity) {}
    
    void Animal::update(float elapsed) {
        Entity::update(elapsed);
        checkBounds(elapsed);
        move(elapsed);
    }
    
    void Animal::checkBounds(float elapsed) {
        var without = bounds.withoutness(pen);
        if (without.x != 0) {
            velocity.x = -velocity.x;
        }
        if (without.y != 0) {
            velocity.y = -velocity.y;
        }
    }
    
    void Animal::move(float elapsed) {
        Entity::move(velocity, elapsed);
    }
}
