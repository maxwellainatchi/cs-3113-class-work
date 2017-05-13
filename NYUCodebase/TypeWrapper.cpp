//
//  TypeWrapper.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 5/11/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include <string>
#include <sstream>

/** 
 @author Muhammad Ahmad Tirmazi
 Modified by Max Ainatchi
 **/
template< typename T> class TypeWrapper {
    T value;
public:
    TypeWrapper(T v): value(v) {}
    
    operator T() { return value; }
    
    // basic arithmetic operators
    void operator = (T v){  value = v; }
    
    template <typename X>
    TypeWrapper operator + (X v) { return TypeWrapper( value + v ); }
    template <typename X>
    TypeWrapper operator - (X v) { return TypeWrapper( value - v); }
    template <typename X>
    TypeWrapper operator * (X v) { return TypeWrapper( value * v); }
    template <typename X>
    TypeWrapper operator / (X v) { return TypeWrapper( value / v); }
    template <typename X>
    TypeWrapper operator % (X v) { return TypeWrapper( value % v); }
    
    template <typename X>
    void operator += (X v) { value += v; }
    template <typename X>
    void operator -= (X v) { value -= v; }
    template <typename X>
    void operator *= (X v) { value *= v; }
    template <typename X>
    void operator /= (X v) { value /= v; }
    template <typename X>
    void operator %= (X v) { value %= v; }
    
    T operator ++ () { return ++value; }
    T operator -- () { return --value;}
    T operator ++ (int v) { return value++; }
    T operator -- (int v) { return value--; }
    
    // conditions
    template <typename X>
    bool operator == (X v) { return value == v; }
    template <typename X>
    bool operator != (X v) { return value != v; }
    template <typename X>
    bool operator > (X v) { return value > v; }
    template <typename X>
    bool operator < (X v) { return value < v; }
    template <typename X>
    bool operator >= (X v) { return value >= v; }
    template <typename X>
    bool operator <= (X v) { return value <= v; }
    
    template<typename X>
    TypeWrapper<X> convert() {
        return TypeWrapper<X>((X) value);
    }
    
    T toPrimitive() { return value; }
    std::string toString() {
        std::stringstream ss;
        std::string rtn;
        
        ss << value;
        ss >> rtn;
        
        return rtn;
    }
};

// just to make things easier for a future move.
#define Numeric TypeWrapper

typedef Numeric< int > Integer;
typedef Numeric< double > Double;
typedef Numeric< float > Float;
