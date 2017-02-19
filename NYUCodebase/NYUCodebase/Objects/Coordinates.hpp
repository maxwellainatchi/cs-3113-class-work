//
//  Coordinates.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Coordinates_hpp
#define Coordinates_hpp

#include "Vector.hpp"

namespace Graphics {
    class Coordinates {
    private:
        struct Bounds {
            float left;
            float right;
            float bottom;
            float top;
        };
    public:
        typedef Vector2D XY;
        
        XY topLeft;
        XY topRight;
        XY bottomLeft;
        XY bottomRight;
        
        Coordinates();
        
        Coordinates(XY bottomLeft, XY topRight);
        
        Bounds bounds();
        
        float width();
        
        float height();
        
        float* resolveCoords();
        
        Coordinates operator+(const Vector2D& offset);
    };
}

#endif /* Coordinates_hpp */
