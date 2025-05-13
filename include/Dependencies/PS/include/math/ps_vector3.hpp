#ifndef PS_VECTOR3_HPP
#define PS_VECTOR3_HPP
#include "ps_common.hpp"
namespace ps
{
    class Vector3
    {
    public:
        Vector3(const real &x = 0.0f, const real &y = 0.0f, const real &z = 0.0f);
        Vector3(const Vector3 &copy);
        Vector3 &operator=(const Vector3 &copy);
        Vector3(Vector3 &&other) = default;

        Vector3 operator+(const Vector3 &rhs) const;
        Vector3 operator-(const Vector3 &other) const;
        Vector3 operator-() const;
        Vector3 operator*(const real &factor) const;
        Vector3 operator*(const int &factor) const;
        Vector3 operator/(const real &factor) const;
        Vector3 operator/(const int &factor) const;

        Vector3 &operator+=(const Vector3 &rhs);
        Vector3 &operator-=(const Vector3 &rhs);
        Vector3 &operator*=(const real &factor);
        Vector3 &operator*=(const int &factor);
        Vector3 &operator/=(const real &factor);
        Vector3 &operator/=(const int &factor);

        Vector3 &set(const real &x, const real &y, const real &z);
        Vector3 &set(const Vector3 &other);
        Vector3 &clear();
        Vector3 &negate();
        Vector3 &normalize();

        real lengthSquare() const;
        real length() const;

        Vector3 normal() const;
        Vector3 negative() const;

        bool equal(const Vector3 &rhs) const;
        bool fuzzyEqual(const Vector3 &rhs, const real &epsilon = Constant::GeometryEpsilon) const;
        bool isOrigin(const real &epsilon = Constant::GeometryEpsilon) const;
        Vector3 &swap(Vector3 &other);

        real dot(const Vector3 &rhs) const;
        Vector3 &cross(const Vector3 &rhs);

        static real dotProduct(const Vector3 &lhs, const Vector3 &rhs);
        static Vector3 crossProduct(const Vector3 &lhs, const Vector3 &rhs);

        real x_;
        real y_;
        real z_;
    };
}
#endif
