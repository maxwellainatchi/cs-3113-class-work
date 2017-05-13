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

// Follows standard order left, right, down, up
enum class Direction: Uint8 {
    none        = 0b0000,
    left        = 0b0001,
    downLeft    = 0b0101,
    down        = 0b0100,
    downRight   = 0b0110,
    right       = 0b0010,
    upRight     = 0b1010,
    up          = 0b1000,
    upLeft      = 0b1001
};

template <typename T>
class Vec2 {
public:
    Vec2();
    Vec2(T x, T y);
    Vec2(T both);
    Vec2(Direction d);
//    Vec2(float magnitude, angle);
    
    T x;
    T y;
    alias(T, x, row);
    alias(T, y, col);
    
    float magnitude();
    void magnitude(float mag);
    
    float angle();
    void angle(float ang);
    
    
    // MARK: - Vector Arithmetic
    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator-(const Vec2& rhs) const;
    Vec2 operator*(const Vec2& rhs) const;
    
    // MARK: Assignment
    void operator+=(const Vec2& rhs);
    void operator-=(const Vec2& rhs);
    void operator*=(const Vec2& rhs);
    
    // MARK: - Scalar Arithmetic
    Vec2 operator+(T scalar) const;
//    Vec2 operator-(T scalar) const;
    Vec2 operator*(T scalar) const;
    
    // MARK: Assignment
    void operator+=(T scalar);
    void operator*=(T scalar);
    
    // MARK: - Utilities
    std::string debugDescription() const;
};
    
// MARK: - Implementation
// MARK: - Initalizers
template <typename T>
Vec2<T>::Vec2(): x(0), y(0) {}
template <typename T>
Vec2<T>::Vec2(T x, T y): x(x), y(y) {}
template <typename T>
Vec2<T>::Vec2(T both): x(both), y(both) {}
template <typename T>
Vec2<T>::Vec2(Direction d) {
    self.magnitude(1);
    let rawVal = (Uint8) d;
    if (getBit(rawVal, 0)) {
        self.angle(M_PI);
    } else if (getBit(rawVal, 1)) {
        self.angle(0);
    }
    if (getBit(rawVal, 2)) {
        self.angle(self.angle() - M_PI_2);
    } else if (getBit(rawVal, 3)) {
        self.angle(self.angle() + M_PI_2);
    }
//    switch (d) {
//        case Direction::up:
//            self.x = 0; self.y = 1; break;
//        case Direction::down:
//            self.x = 0; self.y = -1; break;
//        case Direction::left:
//            self.x = -1; self.y = 0; break;
//        case Direction::right:
//            self.x = 1; self.y = 0; break;
//        default:
//            self.x = 0; self.y = 0; break;
//    }
}

// MARK: - Resolutions
template <typename T>
float Vec2<T>::magnitude() {
    return sqrtf(powf(x, 2) + powf(y, 2));
}

template <typename T>
void Vec2<T>::magnitude(float mag) {
    let theta = angle();
    self.x = mag * cosf(theta);
    self.y = mag * sinf(theta);
}

template <typename T>
float Vec2<T>::angle() {
    return atanf(y/x);
}

template <typename T>
void Vec2<T>::angle(float theta) {
    let mag = magnitude();
    self.x = cosf(theta) * mag;
    self.y = sinf(theta) * mag;
}

// MARK: - Vector Arithmetic
template <typename T>
Vec2<T> Vec2<T>::operator+(const Vec2<T>& rhs) const {
    return {
        x + rhs.x,
        y + rhs.y
    };
}

template <typename T>
Vec2<T> Vec2<T>::operator-(const Vec2<T>& rhs) const {
    return {
        x - rhs.x,
        y - rhs.y
    };
}

template <typename T>
Vec2<T> Vec2<T>::operator*(const Vec2<T>& rhs) const {
    return {
        x * rhs.x,
        y * rhs.y
    };
}

// MARK: Assignment
template <typename T>
void Vec2<T>::operator+=(const Vec2<T>& rhs) {
    x += rhs.x;
    y += rhs.y;
}

template <typename T>
void Vec2<T>::operator-=(const Vec2<T>& rhs) {
    x -= rhs.x;
    y -= rhs.y;
}

template <typename T>
void Vec2<T>::operator*=(const Vec2<T>& rhs) {
    x *= rhs.x;
    y *= rhs.y;
}

// MARK: Scalar Arithmetic
template <typename T>
Vec2<T> Vec2<T>::operator+(T scalar) const {
    Vec2<T> retVal(self);
    retVal += scalar;
    return retVal;
}

template <typename T>
Vec2<T> Vec2<T>::operator*(T scalar) const {
    return self * Vec2<T>(scalar);
}

// MARK: Assignment
template <typename T>
void Vec2<T>::operator+=(T scalar) {
    self.x += cosf(self.angle()) * scalar;
    self.y += sinf(self.angle()) * scalar;
}

template <typename T>
void Vec2<T>::operator*=(T scalar) {
    self *= Vec2<T>(scalar);
}

// MARK: - Utilities
template <typename T>
std::string Vec2<T>::debugDescription() const {
    return "(x: " + std::to_string(x) +
    ",y: " + std::to_string(y) + ")";
}
    
    
// MARK: Typedefs
// Vector should always be my current implementation
typedef Vec2<float> Vector;
typedef Vector Size;
typedef Vector Point;
typedef Vec2<int> IntPair;

#endif /* Vector_hpp */
