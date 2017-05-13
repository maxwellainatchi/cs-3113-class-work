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

class Rectangle;

// Todo: make generic
class Grid {
private:
    // Underlying grid structure
    typedef std::vector<Rectangle*> _Grid;
    
    // Defines the variable with private member access and a public getter
    // Easy access control! (Again, Swift inspired).
    getOnly(IntPair, rowCol);
    getOnly(IntPair, pages);
    getOnly(Size, cellSize);
    getOnly(Size, offset);
    getOnly(Size, padding);
    getOnly(_Grid, value);
public:
    IntPair startIndex;
    
    Grid() {}
    Grid(IntPair rowCol,
         IntPair pages = {1},
         Size cellSize = {1},
         Size offset = {0},
         Size padding = {0});
    
    int rows() const { return rowCol.x * pages.x; }
    int cols() const { return rowCol.y * pages.y; }
    Rectangle* operator[](const IntPair& position) const;
    void operator[](int row) { SDL_assert(false); };
    void addCol();
};

//TODO: Make coordinates contain both UV and XY
//TODO: Use matrices bc efficiency
class Rectangle {
public:
    
    float left;
    float right;
    float bottom;
    float top;
    
    Rectangle();
    
//    Rectangle(const Rectangle* r);
    
    Rectangle(float left, float right, float bottom, float top);
    
    Rectangle(Point bottomLeft, Point topRight);
    
    Rectangle(Point bottomLeft, float w, float h);
    
    Point bottomLeft() const;
    Point bottomRight() const;
    Point topLeft() const;
    Point topRight() const;
    Point center() const;
    
    Vector withoutness(Rectangle pen, bool fully) const;
    Vector penetration(Rectangle other) const;
    bool isWithin(Rectangle pen, bool fully = true) const;
    
    float width() const;
    float height() const;
    float ratio() const;
    
    float* resolveCoords(bool asTexture = false) const;
    
    Rectangle operator+(const Vector& offset) const;
    void operator+=(const Vector& offset);
    Rectangle operator*(const Vector& offset) const;
    
    std::string debugDescription();
};

#endif /* Coordinates_hpp */
