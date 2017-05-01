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
    static std::vector<std::vector<Rectangle*>> generateGrid(int rows, int cols, const Vec2& gridSize = {1,1}, const Vec2& padding = {0,0});
    
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
    void operator+=(const Vec2& offset);
    Rectangle operator*(const Vec2& offset) const;
    
    cstr debugDescription();
};

#endif /* Coordinates_hpp */
