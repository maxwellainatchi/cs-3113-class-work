//
//  Ball.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/20/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Ball.hpp"

namespace Entities {
    Ball::Ball(std::string imageName, Graphics::Coordinates pen): Animal(imageName, pen) {}
    
    void Ball::reset(Graphics::Coordinates& window) {
        paused = true;
        setCoordinates({{
            window.center().x - position.width()/2.0f,
            window.center().y + position.height()/2.0f
        }, {
            window.center().x + position.width()/2.0f,
            window.center().y - position.height()/2.0f
        }});
    }
    
    void Ball::update(float elapsed) {
        if (!paused) {
            Animal::update(elapsed);
        }
    }
    
    void Ball::checkBounds(float elapsed) {
        if (position.bounds().top > pen.bounds().top || position.bounds().bottom < pen.bounds().bottom) {
            velocity = {velocity.x, -velocity.y};
        }
    }
}
