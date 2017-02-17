//
//  Sheep.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Sheep.hpp"

namespace Graphics {
    Sheep::Sheep(std::string imageName, Coordinates pen, Vector2D velocity): Animal(imageName, pen, velocity) {}
    
    void Sheep::update(float elapsed) {
        millAbout(elapsed);
        Animal::update(elapsed);
    }
    
    void Sheep::millAbout(float elapsed) {
        float timeLimit = 1.0;
        timeSinceLastMove += elapsed;
        if (timeSinceLastMove > timeLimit) {
            if (arc4random_uniform(UINT32_MAX) > (timeSinceLastMove/(timeSinceLastMove - timeLimit)/10)*UINT32_MAX) {
                velocity = {velocity.y, velocity.x};
                timeSinceLastMove = 0.0;
            }
        }
    }
}
