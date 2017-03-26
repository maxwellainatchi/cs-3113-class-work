//
//  Ball.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/20/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Ball.hpp"

namespace Entities {
    Ball::Ball(std::string imageName, Position::Rectangle pen): Animal(imageName, pen) {}
    
    void Ball::reset(Position::Rectangle& window) {
        setOrigin(window.center());
    }
    
    void Ball::checkBounds(float elapsed) {
        auto without = bounds.withoutness(pen);
        if (without.y != 0) {
            velocity = {velocity.x, -velocity.y};
        }
    }
}
