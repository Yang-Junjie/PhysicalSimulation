#ifndef VEC2_HPP
#define VEC2_HPP

#include "common.hpp"
#include <ostream>
#include <glm/glm.hpp>

class Vec2 {
public:
    real m_x, m_y;
    Vec2();
    Vec2(real x, real y);

    // ostream overloading
    friend std::ostream& operator<<(std::ostream& os, const Vec2& v);

    // operator overloading for vector2 addition and subtraction
    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;

    // operator overloading for Scalar Multiplication and Division
    Vec2 operator/(const real& scalar) const;
    Vec2 operator*(const real& scalar) const;
    friend Vec2 operator*(const real& scalar, const Vec2& v);

    Vec2& operator+=(const Vec2& other);
    Vec2& operator-=(const Vec2& other);
    Vec2& operator/=(const real& scalar);
    Vec2& operator*=(const real& scalar);

    // operator overloading for logical
    bool operator==(const Vec2& other) const;
    bool operator!=(const Vec2& other) const;

    void setValue(real x,real y);
    void clear();

    real cross(const Vec2& other) const;
    static inline real cross(const Vec2& v1,const Vec2& v2);
    real dot(const Vec2& other)const;
    static inline real dot(const Vec2& v1,const Vec2& v2);

    real getLength()const;
    static inline real getLength(const Vec2& v);
    real getDistance(const Vec2& other)const;
    static inline real getDistance(const Vec2& v1,const Vec2& v2);

    void normalization();
    static inline void normalization(Vec2& v); 
    
};
#endif