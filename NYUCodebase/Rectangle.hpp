//
//  Rectangle.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Rectangle_hpp
#define Rectangle_hpp

#include "libraries.h"
#include "macros.h"
#include "Vector.hpp"

//TODO: Make coordinates contain both UV and XY
//TODO: Use matrices bc efficiency
class Rectangle {
public:
    float left;
    float right;
    float bottom;
    float top;
    
    Rectangle();
    
    Rectangle(const Rectangle* r);
    
    Rectangle(float left, float right, float bottom, float top);
    
    Rectangle(Point bottomLeft, Point topRight);
    
    Rectangle(Point bottomLeft, float w, float h);
    
    Point bottomLeft() const;
    Point bottomRight() const;
    Point topLeft() const;
    Point topRight() const;
    Point center() const;
    
    Vec2 withoutness(Rectangle pen, bool fully) const;
    Vec2 penetration(Rectangle other) const;
    bool isWithin(Rectangle pen, bool fully = true) const;
    
    float width() const;
    float height() const;
    
    float* resolveCoords(bool asTexture = false) const;
    
    Rectangle operator+(const Vec2& offset) const;
    Rectangle operator*(const Vec2& offset) const;
    
    void operator+=(const Vec2& offset);
};

#endif /* Coordinates_hpp */
