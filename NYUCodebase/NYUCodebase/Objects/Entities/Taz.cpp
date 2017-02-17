//
//  Taz.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Taz.hpp"

namespace Graphics {
    
    Taz::Taz(std::string imageName, Coordinates pen, float speed): Graphics::Animal(imageName, pen, {0.0, 0.0}), speed(speed) {}
    
    void Taz::move(float elapsed) {
        angle += elapsed;
        rotate(elapsed * speed);
    }
}
