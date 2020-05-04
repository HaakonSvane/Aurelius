//
//  Vector2D.hpp
//  Aurelius
//
//  Created by Haakon Svane on 19/06/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include <cmath>
#include "SDL2/SDL.h"

template <class T>
struct Vector2D{
    
    T x;
    T y;
    
    constexpr Vector2D():Vector2D(0, 0){}
    constexpr Vector2D(T x, T y):x{x}, y{y}{}
    constexpr Vector2D(const Vector2D& other):x{other.x}, y{other.y}{}
    
    constexpr Vector2D& operator=(const Vector2D& other){
        x = other.x;
        y = other.y;
        return *this;
    }
    
    constexpr Vector2D operator+ (const Vector2D& other) const{
        return Vector2D(x+other.x, y+other.y);
    }
    
    constexpr Vector2D operator-(const Vector2D& other) const{
        return Vector2D(x-other.x, y-other.y);
    }
    
    constexpr Vector2D operator*(const Vector2D& other) const{
        return Vector2D(x*other.x, y*other.y);
    }
    
    constexpr Vector2D operator*(const T n) const{
        return Vector2D(x*n, y*n);
    }
    
    constexpr Vector2D operator/(const Vector2D& other) const{
        return Vector2D(x/other.x, y/other.y);
    }
    
    Vector2D<int> to_int() const{
        return (Vector2D<int>{static_cast<int>(x), static_cast<int>(y)});
    };
    
    Vector2D<float> to_float() const{
        return (Vector2D<float>{static_cast<float>(x), static_cast<float>(y)});
    };
    
    constexpr float dist(Vector2D other) const {
        Vector2D v(other.x - x, other.y - y);
        return v.length();
    }
    
    float length() const {
        return std::sqrt(x * x + y * y);
    }
    
    constexpr Vector2D& normalize() {
        if (length() == 0) return *this;
        *this *= (1.0 / length());
        return *this;
    }
};

template <typename T>
constexpr bool operator <= (const Vector2D<T>& v, SDL_Rect r){
    return ((v.x >= r.x && v.x <= (r.x+r.w)) && (v.y >= r.y && v.y <= (r.y+r.h)));
}
template <typename T>
constexpr bool operator > (const Vector2D<T>& v, SDL_Rect r){
    return !(v <= r);
}

template <typename T>
constexpr Vector2D<T> operator - (const Vector2D<T>& v, const SDL_Rect& r){
    T dx = (v.x > r.x + r.w)?(v.x-(r.x+r.w)):((v.x < r.x)?(v.x-r.x):0);
    T dy = (v.y > r.y + r.h)?(v.y-(r.y+r.h)):((v.y < r.y)?(v.y-r.y):0);
    return Vector2D<T>{dx, dy};
        
}



