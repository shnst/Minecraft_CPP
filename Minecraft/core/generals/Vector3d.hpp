//
//  Vector3d.h
//  Minecraft_cpp
//
//  Created by Shun Sato on 8/10/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef Vector3d_h
#define Vector3d_h


/**
 * 3 dimentional vector class which contains a lot of convenient vector related calculations.
 */
template <class T>
class vec3 {
public:
    T x, y, z;
    
    vec3() :x(0), y(0) {}
    vec3(T x, T y, T z) : x(x), y(y), z(z) {}
    vec3(const vec3& v) : x(v.x), y(v.y), z(v.z) {}
    
    bool operator!=(const vec3& v) const{
        return (x != v.x || y != v.y || z != v.z);
    }
    
    bool operator==(const vec3& v) const{
        return (x == v.x && y == v.y && z = v.z);
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
    
    
};

typedef vec3<int> vec3n;
typedef vec3<float> vec3f;
typedef vec3<double> vec3d;


#endif /* Vector3d_h */
