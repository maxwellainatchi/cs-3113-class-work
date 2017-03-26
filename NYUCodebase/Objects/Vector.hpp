//
//  Vector.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include "math.h"

namespace Position {
    class Vector2D {
    public:
        enum Direction: int { none, up, down, left, right };
        static Vector2D directionVector(Direction d);
        
        float x;
        float y;
        
        float magnitude();
        
        float angle();
        
        Vector2D operator*(const Vector2D& rhs);
        Vector2D operator*(float scalar);
        Vector2D operator+(const Vector2D& rhs);
        Vector2D operator-(const Vector2D& rhs);
    };
    typedef Vector2D Point;
}

#endif /* Vector_hpp */
