//
//  Rectangle.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Rectangle.hpp"

std::vector<std::vector<Rectangle*>> Rectangle::generateGrid(int rows, int cols, const Vec2& gridSize, const Vec2& padding) {
    std::vector<std::vector<Rectangle*>> retVal;
    repeat (row, rows) {
        retVal.push_back(std::vector<Rectangle*>());
        repeat (col, cols) {
            retVal[row].push_back(new Rectangle({
                (gridSize.x/float(cols) + padding.x) * col,
                (1.f - row/float(rows)) * gridSize.y + padding.y * row
            }, gridSize.x/cols, gridSize.y/rows));
        }
    }
    return retVal;
}

Rectangle::Rectangle(): Rectangle(-0.5f, 0.5f, -0.5f, 0.5f) {}

Rectangle::Rectangle(const Rectangle* r): Rectangle(r->left, r->right, r->bottom, r->top) {}

Rectangle::Rectangle(float left, float right, float bottom, float top) {
    this->left = std::min(left, right);
    this->right = std::max(left, right);
    this->bottom = std::min(bottom, top);
    this->top = std::max(bottom, top);
}

Rectangle::Rectangle(Point bottomLeft, Point topRight):
Rectangle(bottomLeft.x, topRight.x, bottomLeft.y, topRight.y) {}

Rectangle::Rectangle(Point bottomLeft, float w, float h):
Rectangle(bottomLeft.x, bottomLeft.x + w, bottomLeft.y, bottomLeft.y + h) {}

Point Rectangle::bottomLeft() const {
    return {left, bottom};
}
Point Rectangle::bottomRight() const {
    return {right, bottom};
}
Point Rectangle::topLeft() const {
    return {left, top};
}
Point Rectangle::topRight() const {
    return {right, top};
}

Point Rectangle::center() const {
    return {
        left + width() / 2.0f,
        bottom + height() / 2.0f
    };
}

float Rectangle::width() const {
    return right - left;
}

float Rectangle::height() const {
    return top - bottom;
}

float* Rectangle::resolveCoords(bool asTexture) const {
    return new float[12] {
        // Lower triangle
        // Bottom Left
        left,
        asTexture ? top : bottom,
        
        // Bottom Right
        right,
        asTexture ? top : bottom,
        
        // Top Right
        right,
        asTexture ? bottom : top,
        
        // Upper triangle
        // Bottom Left
        left,
        asTexture ? top : bottom,
        
        // Top Right
        right,
        asTexture ? bottom : top,
        
        // Top Left
        left,
        asTexture ? bottom : top
    };
}

Vec2 Rectangle::withoutness(Rectangle pen, bool fully) const {
    Vec2 without = {0, 0};
    var max = fully ? left : right;
    var min = fully ? right : left;
    if (max > pen.right) {
        without.x = max - pen.right;
    } else if (min < pen.left) {
        without.x = min - pen.left;
    }
    
    max = fully ? bottom : top;
    min = fully ? top : bottom;
    if (max > pen.top) {
        without.y = max - pen.top;
    } else if (min < pen.bottom) {
        without.y = min - pen.bottom;
    }
    return without;
}

Vec2 Rectangle::penetration(Rectangle other) const {
    Vec2 dist = {
        (float) fabs(center().x - other.center().x),
        (float) fabs(center().y - other.center().y)
    };
    return {
        (float) fabs(dist.x - width()/2 - other.width()/2),
        (float) fabs(dist.y - height()/2 - other.height()/2)
    };
}

bool Rectangle::isWithin(Rectangle pen, bool fully) const {
    var max = fully ? right : left;
    var min = fully ? left : right;
    guard (max < pen.right && min > pen.left) else { return false; }
    
    max = fully ? top : bottom;
    min = fully ? bottom : top;
    guard (max < pen.top && min > pen.bottom) else { return false; }
    return true;
}

Rectangle Rectangle::operator+(const Vec2& offset) const {
    Rectangle retVal(this);
    retVal += offset;
    return retVal;
}

void Rectangle::operator+=(const Vec2 &offset) {
    left += offset.x;
    right += offset.x;
    bottom += offset.y;
    top += offset.y;
}

Rectangle Rectangle::operator*(const Vec2 &offset) const {
    return {
        bottomLeft(),
        width() * offset.x,
        height() * offset.y
    };
}

cstr Rectangle::debugDescription() {
    cstr retVal = new char;
    sprintf(retVal, "(x: (%f, %f), y: (%f, %f), size: (%f, %f))", left, right, bottom, top, width(), height());
    return retVal;
}
