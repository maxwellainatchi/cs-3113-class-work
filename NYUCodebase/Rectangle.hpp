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
    
    Point bottomLeft();
    Point bottomRight();
    Point topLeft();
    Point topRight();
    Point center();
    
    Vec2 withoutness(Rectangle pen, bool fully);
    Vec2 penetration(Rectangle other);
    bool isWithin(Rectangle pen, bool fully = true);
    
    float width();
    float height();
    
    float* resolveCoords(bool asTexture = false);
    
    Rectangle operator+(const Vec2& offset);
    Rectangle operator*(const Vec2& offset);
    
    void operator+=(const Vec2& offset);
};

#endif /* Coordinates_hpp */
