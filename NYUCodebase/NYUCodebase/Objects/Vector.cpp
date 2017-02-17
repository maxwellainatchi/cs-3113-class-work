//
//  Vector.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Vector.hpp"

namespace Graphics {
    Vector2D Vector2D::directionVector(Vector2D::Direction d) {
        switch (d) {
            case up:
                return {0.0, 1.0};
            case down:
                return {0.0, -1.0};
            case left:
                return {-1.0, 0.0};
            case right:
                return {1.0, 0.0};
            default:
                return {0.0, 0.0};
        }
    }
    
    float Vector2D::magnitude() {
        return sqrtf(powf(x, 2) + powf(y, 2));
    }
    
    float Vector2D::angle() {
        return atanf(x/y);
    }
    
    Vector2D Vector2D::operator*(const Vector2D& rhs) {
        return {
            x * rhs.x,
            y * rhs.y
        };
    }
    
    Vector2D Vector2D::operator*(float scalar) {
        return {
            x * scalar,
            y * scalar
        };
    }
}
