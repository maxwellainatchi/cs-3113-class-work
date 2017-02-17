//
//  Taz.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Taz.hpp"

namespace Graphics {
    
    Taz::Taz(std::string imageName, Coordinates pen, Vector2D velocity): Graphics::Animal(imageName, pen, velocity) {}
    
    void Taz::move(float elapsed) {
        angle += elapsed;
        rotate(elapsed);
        //TODO: Take velocity into account
    }
}
