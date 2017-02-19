//
//  Coordinates.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Coordinates.hpp"

namespace Graphics {
    
    Coordinates::Coordinates():
    bottomLeft({-0.5,-0.5}),
    bottomRight({0.5,-0.5}),
    topLeft({-0.5,0.5}),
    topRight({0.5,0.5}) {}
    
    
    Coordinates::Coordinates(Coordinates::XY bottomLeft, Coordinates::XY topRight):
    bottomLeft(bottomLeft),
    bottomRight({topRight.x, bottomLeft.y}),
    topLeft({bottomLeft.x, topRight.y}),
    topRight(topRight) {}
    
    Coordinates::Bounds Coordinates::bounds() {
        return {
            topLeft.x,
            topRight.x,
            bottomLeft.y,
            topLeft.y
        };
    }
    
    float Coordinates::width() {
        return bounds().right - bounds().left;
    }
    
    float Coordinates::height() {
        return bounds().top - bounds().bottom;
    }
    
    
    float* Coordinates::resolveCoords() {
        return new float[12] {
            // Lower triangle
            bottomLeft.x,
            bottomLeft.y,
            bottomRight.x,
            bottomRight.y,
            topRight.x,
            topRight.y,
            
            // Upper triangle
            bottomLeft.x,
            bottomLeft.y,
            topRight.x,
            topRight.y,
            topLeft.x,
            topLeft.y
        };
    }
    
    Coordinates Coordinates::operator+(const Vector2D& offset) {
        Coordinates retVal;
        retVal.topRight = { topRight.x + offset.x, topRight.y + offset.y};
        retVal.topLeft = { topLeft.x + offset.x, topLeft.y + offset.y};
        retVal.bottomRight = { bottomRight.x + offset.x, bottomRight.y + offset.y};
        retVal.bottomLeft = { bottomLeft.x + offset.x, bottomLeft.y + offset.y};
        return retVal;
    }
}
