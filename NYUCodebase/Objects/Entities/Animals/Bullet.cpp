//
//  Bullet.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 3/10/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Bullet.hpp"

namespace Entities {
    Bullet::Bullet(std::string imageName, Graphics::Coordinates pen, Graphics::Vector2D velocity): Entities::Animal(imageName, pen, velocity) {}
    
    void Bullet::kill() {
        translate({
            pen.height() * 2,
            0
        });
    }
    
    void Bullet::checkBounds(float elapsed) {
        if (position.bounds().bottom > pen.bounds().top ||
            position.bounds().top < pen.bounds().bottom ||
            position.bounds().left > pen.bounds().right ||
            position.bounds().right < pen.bounds().left) {
            velocity = {0,0};
        }
    }
}
