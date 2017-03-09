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

//TODO: Make coordinates contain both UV and XY
//TODO: Prevent inverted coordinates (e.g. top below bottom)
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
        
        Coordinates(XY bottomLeft, float w, float h);
        
        Bounds bounds();
        
        float width();
        
        float height();
        
        XY center();
        
        float* resolveCoords();
        
        Coordinates operator+(const Vector2D& offset);
    };
}

#endif /* Coordinates_hpp */
