#ifndef VEC3_HPP
#define VEC3_HPP
#include "Common.hpp"
#include <ostream>
class Vec3 {
public:
    real m_x, m_y,m_z;
    Vec3();
    Vec3(real x, real y,real z);

    // ostream overloading
    friend std::ostream& operator<<(std::ostream& os, const Vec3& v);

    // operator overloading for vector2 addition and subtraction
    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;

    // operator overloading for Scalar Multiplication and Division
    Vec3 operator/(const real& scalar) const;
    Vec3 operator*(const real& scalar) const;
    friend Vec3 operator*(const real& scalar, const Vec3& v);

    Vec3& operator+=(const Vec3& other);
    Vec3& operator-=(const Vec3& other);
    Vec3& operator/=(const real& scalar);
    Vec3& operator*=(const real& scalar);

    // operator overloading for logical
    bool operator==(const Vec3& other) const;
    bool operator!=(const Vec3& other) const;

    void setValue(real x,real y,real z);
    void clear();

    Vec3 cross(const Vec3& other) const;
    static inline Vec3 cross(const Vec3& v1,const Vec3& v2);
    real dot(const Vec3& other)const;
    static inline real dot(const Vec3& v1,const Vec3& v2);

    real getLength()const;
    static inline real getLength(const Vec3& v);
    real getDistance(const Vec3& other)const;
    static inline real getDistance(const Vec3& v1,const Vec3& v2);

    void normalization();
    static inline void normalization(Vec3& v); 
    
};


#endif