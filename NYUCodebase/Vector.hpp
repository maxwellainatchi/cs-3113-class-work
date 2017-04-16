//
//  Vector.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include "libraries.h"
#include "math.h"

class Vec2 {
public:
    enum Direction: int { none = 0, up, down, left, right };
    static Vec2 directionVector(Direction d);
    
    Vec2();
    Vec2(float x, float y);
    Vec2(float both);
//    Vec2(float magnitude, angle);
    
    float x;
    float y;
    
    float magnitude();
    
    float angle();
    
    Vec2 operator*(const Vec2& rhs);
    void operator*=(const Vec2& rhs);
    Vec2 operator*(float scalar);
    void operator*=(float scalar);
    Vec2 operator+(const Vec2& rhs);
    void operator+=(const Vec2& rhs);
    Vec2 operator-(const Vec2& rhs);
    void operator-=(const Vec2& rhs);
};
typedef Vec2 Point;

#endif /* Vector_hpp */
