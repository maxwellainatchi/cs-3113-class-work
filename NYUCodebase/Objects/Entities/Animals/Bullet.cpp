//
//  Bullet.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 3/10/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Bullet.hpp"

namespace Entities {
    Bullet::Bullet(std::string imageName, Position::Rectangle pen, Position::Vector2D velocity): Entities::Animal(imageName, pen, velocity) {}
    
    void Bullet::kill() {
        translate({
            pen.height() * 2,
            0
        });
    }
    
    void Bullet::checkBounds(float elapsed) {
        var without = bounds.withoutness(pen, false);
        guard (without.x == 0 && without.y == 0) else {
            velocity = {0,0};
        }
    }
}
