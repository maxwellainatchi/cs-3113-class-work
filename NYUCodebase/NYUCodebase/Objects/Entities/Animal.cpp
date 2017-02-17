//
//  Animal.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Animal.hpp"

namespace Entities {
    Animal::Animal(std::string imageName, Graphics::Coordinates pen, Graphics::Vector2D velocity): Entities::Entity(imageName), pen(pen), velocity(velocity) {}
    
    void Animal::update(float elapsed) {
        Entity::update(elapsed);
        checkBounds(elapsed);
        move(elapsed);
    }
    
    void Animal::checkBounds(float elapsed) {
        if (position.bounds().top > pen.bounds().top || position.bounds().bottom < pen.bounds().bottom) {
            velocity = {velocity.x, -velocity.y};
        }
        if (position.bounds().right > pen.bounds().right || position.bounds().left < pen.bounds().left) {
            velocity = {-velocity.x, velocity.y};
        }
    }
    
    void Animal::move(float elapsed) {
        Entity::move(velocity, elapsed);
    }
}
