#include "Vec3.hpp"
#include <cmath>
#include <ostream>
Vec3::Vec3()
    : m_x(0.0)
    , m_y(0.0)
    , m_z(0.0)
{
}

Vec3::Vec3(real x, real y, real z)
    : m_x(x)
    , m_y(y)
    , m_z(z)
{
}

std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
    os << "[ " << v.m_x << " " << v.m_y << "," << v.m_z << " ]";
    return os;
}

Vec3 Vec3::operator+(const Vec3& other) const

{
    return Vec3(this->m_x + other.m_x, this->m_y + other.m_y, this->m_z + other.m_z);
}

Vec3 Vec3::operator-(const Vec3& other) const

{
    return Vec3(this->m_x - other.m_x, this->m_y - other.m_y, this->m_z - other.m_z);
}

Vec3 Vec3::operator/(const real& scalar) const

{
    return Vec3(this->m_x / scalar, this->m_y / scalar, this->m_z / scalar);
}
Vec3 Vec3::operator*(const real& scalar) const

{
    return Vec3(this->m_x * scalar, this->m_y * scalar, this->m_z * scalar);
}

Vec3 operator*(const real& scalar, const Vec3& v)
{
    return Vec3(v.m_x * scalar, v.m_y * scalar, v.m_z * scalar);
}

Vec3& Vec3::operator+=(const Vec3& other)
{
    this->m_x += other.m_x;
    this->m_y += other.m_y;
    this->m_z += other.m_z;
    return *this;
}
Vec3& Vec3::operator-=(const Vec3& other)
{
    this->m_x -= other.m_x;
    this->m_y -= other.m_y;
    this->m_z -= other.m_z;
    return *this;
}
Vec3& Vec3::operator/=(const real& scalar)
{
    this->m_x /= scalar;
    this->m_y /= scalar;
    this->m_z /= scalar;
    return *this;
}
Vec3& Vec3::operator*=(const real& scalar)
{
    this->m_x += scalar;
    this->m_y += scalar;
    this->m_z += scalar;
    return *this;
}
bool Vec3::operator==(const Vec3& other) const

{
    return (this->m_x == other.m_x) && (this->m_y == other.m_y)&&(this->m_z == other.m_z);;
}
bool Vec3::operator!=(const Vec3& other) const

{
    return !(*this == other);
}
void Vec3::setValue(real x, real y,real z)
{
    this->m_x = x;
    this->m_y = y;
    this->m_z = z;
}
void Vec3::clear()
{
    this->m_x = 0.0;
    this->m_y = 0.0;
    this->m_z = 0.0;
}
Vec3 Vec3::cross(const Vec3& other) const
{
    return Vec3(this->m_y * other.m_z - this->m_z * other.m_y, this->m_z * other.m_x - this->m_x * other.m_z, this->m_x * other.m_y - this->m_y * other.m_x);
}
Vec3 Vec3::cross(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.m_y * v2.m_z - v1.m_z * v2.m_y, v1.m_z * v2.m_x - v1.m_x * v2.m_z, v1.m_x * v2.m_y - v1.m_y * v2.m_x);
}
real Vec3::dot(const Vec3& other) const
{
    return this->m_x * other.m_x + this->m_y * other.m_y + this->m_z * other.m_z;
    ;
}
real Vec3::dot(const Vec3& v1, const Vec3& v2)
{
    return v1.m_x * v2.m_x + v1.m_y * v2.m_y + v1.m_z * v2.m_z;
}

real Vec3::getLength() const
{
    return std::sqrt(this->m_x * this->m_x + this->m_y * this->m_y + this->m_z * this->m_z);
}

real Vec3::getLength(const Vec3& v)
{
    return std::sqrt(v.m_x * v.m_x + v.m_y * v.m_y + v.m_z * v.m_z);
}

real Vec3::getDistance(const Vec3& other) const
{
    Vec3 v = *this - other;
    return v.getLength();
}

real Vec3::getDistance(const Vec3& v1, const Vec3& v2)
{
    Vec3 v = v1 - v2;
    return v.getLength();
}

void Vec3::normalization()
{
    real len = this->getLength();
    this->m_x /= len;
    this->m_y /= len;
    this->m_z /= len;
}

void Vec3::normalization(Vec3& v)
{
    real len = v.getLength();
    v.m_x /= len;
    v.m_y /= len;
    v.m_z /= len;
}