//
//  Magician.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Magician.hpp"

namespace Entities {
    Magician::Magician(std::string imageName, Graphics::Coordinates pen):
    Entities::Entity(imageName), pen(pen), apparitionTime(2.0) {}
    
    void Magician::update(float elapsed) {
        Entity::update(elapsed);
        float resolution = 1000.0f;
        timeSinceLastApparition += elapsed;
        if (timeSinceLastApparition > apparitionTime) {
            float maxY = pen.bounds().top - position.bounds().top;
            float minY = position.bounds().bottom - pen.bounds().bottom;
            float maxX = pen.bounds().right - position.bounds().right;
            float minX = position.bounds().left - pen.bounds().left;
            Graphics::Coordinates::XY offset = {
                static_cast<float>(arc4random_uniform((maxX+minX)*resolution)/resolution - minX),
                static_cast<float>(arc4random_uniform((maxY+minY)*resolution)/resolution - minY)
            };
            translate(offset);
            timeSinceLastApparition = 0;
        }
    }
}
