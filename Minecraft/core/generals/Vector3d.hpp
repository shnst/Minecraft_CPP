//
//  Vector3d.h
//  Minecraft_cpp
//
//  Created by Shun Sato on 8/10/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef Vector3d_h
#define Vector3d_h

#include <functional>
#include <cmath>

/**
 * 3 dimentional vector class which contains a lot of convenient vector related calculations.
 */
template <class T>
class vec3 {
public:
    T x, y, z;
    
    vec3() :x(0), y(0), z(0) {}
    vec3(T x, T y, T z) : x(x), y(y), z(z) {}
    vec3(const vec3& v) : x(v.x), y(v.y), z(v.z) {}
    
    bool operator!=(const vec3& v) const{
        return (x != v.x || y != v.y || z != v.z);
    }
    
    bool operator==(const vec3& v) const{
        return (x == v.x && y == v.y && z == v.z);
    }
    
    vec3& operator=(const vec3& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
    
    vec3 operator+(const vec3& v) const{
        return vec3(x + v.x, y + v.y, z + v.z);
    }
    vec3 operator-(const vec3& v) const{
        return vec3(x - v.x, y - v.y, z - v.z);
    }
    vec3& operator+=(const vec3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    vec3& operator-=(const vec3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
    
    vec3 operator+(const T& s) const {
        return vec3(x + s, y + s, z + s);
    }
    vec3 operator-(const T& s) const {
        return vec3(x - s, y - s, z - s);
    }
    vec3 operator*(const T& s) const {
        return vec3(x * s, y * s, z * s);
    }
    vec3 operator/(const T& s) const {
        return vec3(x / s, y / s, z / s);
    }
    
    
    vec3& operator+=(const T& s) {
        x += s;
        y += s;
        z += s;
        return *this;
    }
    vec3& operator-=(const T& s) {
        x -= s;
        y -= s;
        z -= s;
        return *this;
    }
    vec3& operator*=(const T& s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }
    vec3& operator/=(const T& s) {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }
    
    void set(T x, T y, T z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
    float distance(const vec3& v) const {
        vec3 d(v.x - x, v.y - y, v.z - z);
        return d.length();
    }
    
    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

};

using vec3n = vec3<int>;
using vec3f = vec3<float>;
using vec3d = vec3<double>;


//bool operator ==(const vec3n& left, const vec3n& right) noexcept {
//    return (left.x == right.x && left.y == right.y && left.z = right.z);
//}

namespace std
{
    template<>
    struct hash<vec3n>
    {
        size_t operator()(const vec3n& v) const noexcept
        {
            std::hash<decltype(v.x)> hasher;
            
            auto hash1 = hasher(v.x);
            auto hash2 = hasher(v.y);
            auto hash3 = hasher(v.z);
            
            return std::hash<decltype(v.x)>{}((hash1 ^ (hash2 << hash3) ^ hash3));
        }
    };
}


#endif /* Vector3d_h */
