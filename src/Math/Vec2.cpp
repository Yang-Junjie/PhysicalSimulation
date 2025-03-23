#include "Vec2.hpp"
#include <cmath>
#include <ostream>
Vec2::Vec2()
    : m_x(0.0)
    , m_y(0.0)
{
}

Vec2::Vec2(real x, real y)
    : m_x(x)
    , m_y(y)
{
}

std::ostream& operator<<(std::ostream& os, const Vec2& v)
{
    os << "[ " << v.m_x << " " << v.m_y << " ]";
    return os;
}

Vec2 Vec2::operator+(const Vec2& other) const

{
    return Vec2(this->m_x + other.m_x, this->m_y + other.m_y);
}

Vec2 Vec2::operator-(const Vec2& other) const

{
    return Vec2(this->m_x - other.m_x, this->m_y - other.m_y);
}

Vec2 Vec2::operator/(const real& scalar) const

{
    return Vec2(this->m_x / scalar, this->m_y / scalar);
}
Vec2 Vec2::operator*(const real& scalar) const

{
    return Vec2(this->m_x * scalar, this->m_y * scalar);
}

Vec2 operator*(const real& scalar, const Vec2& v)
{
    return Vec2(v.m_x * scalar, v.m_y * scalar);
}

Vec2& Vec2::operator+=(const Vec2& other)
{
    this->m_x += other.m_x;
    this->m_y += other.m_y;
    return *this;
}
Vec2& Vec2::operator-=(const Vec2& other)
{
    this->m_x -= other.m_x;
    this->m_y -= other.m_y;
    return *this;
}
Vec2& Vec2::operator/=(const real& scalar)
{
    this->m_x /= scalar;
    this->m_y /= scalar;
    return *this;
}
Vec2& Vec2::operator*=(const real& scalar)
{
    this->m_x += scalar;
    this->m_y += scalar;
    return *this;
}
bool Vec2::operator==(const Vec2& other) const

{
    return (this->m_x == other.m_x) && (this->m_y == other.m_y);
}
bool Vec2::operator!=(const Vec2& other) const

{
    return !(*this == other);
}
void Vec2::setValue(real x, real y)
{
    this->m_x = x;
    this->m_y = y;
}
void Vec2::clear()
{
    this->m_x = 0.0;
    this->m_y = 0.0;
}
real Vec2::cross(const Vec2& v) const
{
    return this->m_x * v.m_y - this->m_y * v.m_x;
}

real Vec2::cross(const Vec2& v1, const Vec2& v2)
{
    return v1.m_x * v2.m_y - v1.m_y * v2.m_x;
}
real Vec2::dot(const Vec2& other) const
{
    return this->m_x * other.m_x + this->m_y * other.m_y;
}
real Vec2::dot(const Vec2& v1, const Vec2& v2)
{
    return v1.m_x * v2.m_x + v1.m_y * v2.m_y;
}
real Vec2::getLength() const
{
    return std::sqrt(this->m_x * this->m_x + this->m_y * this->m_y);
}

real Vec2::getLength(const Vec2& v)
{
    return std::sqrt(v.m_x * v.m_x + v.m_y * v.m_y);
}

real Vec2::getDistance(const Vec2& other) const
{
    Vec2 v = *this - other;
    return v.getLength();
}

real Vec2::getDistance(const Vec2& v1, const Vec2& v2)
{
    Vec2 v = v1 - v2;
    return v.getLength();
}

void Vec2::normalization()
{
    real len = this->getLength();
    this->m_x /= len;
    this->m_y /= len;
}

void Vec2::normalization(Vec2& v)
{
    real len = v.getLength();
    v.m_x /= len;
    v.m_y /= len;
}