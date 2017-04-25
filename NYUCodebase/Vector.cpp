//
//  Vector.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Vector.hpp"

Vec2 Vec2::directionVector(Vec2::Direction d) {
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

Vec2::Vec2(): x(0), y(0) {}
Vec2::Vec2(float x, float y): x(x), y(y) {}
Vec2::Vec2(float both): x(both), y(both) {}

float Vec2::magnitude() {
    return sqrtf(powf(x, 2) + powf(y, 2));
}

float Vec2::angle() {
    return atanf(x/y);
}

Vec2 Vec2::operator*(const Vec2& rhs) {
    return {
        x * rhs.x,
        y * rhs.y
    };
}

void Vec2::operator*=(const Vec2& rhs) {
    x *= rhs.x;
    y *= rhs.y;
}

Vec2 Vec2::operator*(float scalar) {
    return self * Vec2(scalar);
}

void Vec2::operator*=(float scalar) {
    self *= Vec2(scalar);
}

Vec2 Vec2::operator+(const Vec2& rhs) {
    return {
        x + rhs.x,
        y + rhs.y
    };
}

void Vec2::operator+=(const Vec2& rhs) {
    x += rhs.x;
    y += rhs.y;
}

Vec2 Vec2::operator-(const Vec2& rhs) {
    return {
        x - rhs.x,
        y - rhs.y
    };
}

void Vec2::operator-=(const Vec2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
}
