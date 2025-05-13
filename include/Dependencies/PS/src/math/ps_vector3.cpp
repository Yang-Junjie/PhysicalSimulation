#include "ps_vector3.hpp"
#include "ps_math.hpp"

namespace ps
{
	Vector3::Vector3(const real& x ,const real& y, const real& z) : x_(x), y_(y), z_(z)
	{
	}

	Vector3::Vector3(const Vector3& copy) : x_(copy.x_), y_(copy.y_), z_(copy.z_)
	{
	}

	Vector3 Vector3::operator+(const Vector3& rhs) const
	{
		return Vector3(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_);
	}

	Vector3 Vector3::operator-(const Vector3& other) const
	{
		return Vector3(x_ - other.x_, y_ - other.y_, z_ - other.z_);
	}

	Vector3 Vector3::operator-() const
	{
		return Vector3(-x_, -y_, -z_);
	}

	Vector3 Vector3::operator*(const real& factor) const
	{
		return Vector3(x_ * factor, y_ * factor, z_ * factor);
	}

	Vector3 Vector3::operator/(const real& factor) const
	{
		assert(!realEqual(factor, 0));
		return Vector3(x_ / factor, y_ / factor, z_ / factor);
	}

	Vector3& Vector3::operator+=(const Vector3& rhs)
	{
		x_ += rhs.x_;
		y_ += rhs.y_;
		z_ += rhs.z_;
		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& rhs)
	{
		x_ -= rhs.x_;
		y_ -= rhs.y_;
		z_ -= rhs.z_;
		return *this;
	}

	Vector3& Vector3::operator*=(const real& factor)
	{
		x_ *= factor;
		y_ *= factor;
		z_ *= factor;
		return *this;
	}

	Vector3& Vector3::operator/=(const real& factor)
	{
		assert(!realEqual(factor, 0));
		x_ /= factor;
		y_ /= factor;
		z_ /= factor;
		return *this;
	}

	Vector3& Vector3::set(const real& _x_, const real& _y_, const real& _z_)
	{
		x_ = _x_;
		y_ = _y_;
		z_ = _z_;
		return *this;
	}

	Vector3& Vector3::set(const Vector3& other)
	{
		x_ = other.x_;
		y_ = other.y_;
		z_ = other.z_;
		return *this;
	}

	Vector3& Vector3::clear()
	{
		x_ = 0.0f;
		y_ = 0.0f;
		z_ = 0.0f;
		return *this;
	}

	Vector3 Vector3::negative() const
	{
		return Vector3(-x_, -y_, -z_);
	}
	Vector3& Vector3::negate()
	{
		x_ = -x_;
		y_ = -y_;
		z_ = -z_;
		return *this;
	}

	real Vector3::lengthSquare() const
	{
		return x_ * x_ + y_ * y_ + z_ * z_;
	}

	real Vector3::length() const
	{
		return sqrt(lengthSquare());
	}

	Vector3& Vector3::normalize()
	{
		const real length_inv = 1/sqrt(lengthSquare());
		x_ *= length_inv;
		y_ *= length_inv;
		z_ *= length_inv;
		return *this;
	}

	Vector3 Vector3::normal() const
	{
		return Vector3(*this).normalize();
	}

	bool Vector3::equal(const Vector3& rhs) const
	{
		return realEqual(x_, rhs.x_) && realEqual(y_, rhs.y_) && realEqual(z_, rhs.z_);
	}

	bool Vector3::fuzzyEqual(const Vector3& rhs, const real& epsilon) const
	{
		return (*this - rhs).lengthSquare() < epsilon;
	}
	bool Vector3::isOrigin(const real& epsilon) const
	{
		return fuzzyEqual({0, 0, 0}, epsilon);
    }
	Vector3& Vector3::swap(Vector3& other)
	{
		realSwap(x_, other.x_);
		realSwap(y_, other.y_);
		realSwap(z_, other.z_);
		return *this;
	}

	real Vector3::dot(const Vector3& rhs) const
	{
		return x_ * rhs.x_ + y_ * rhs.y_ + z_ * rhs.z_;
	}

	Vector3& Vector3::cross(const Vector3& rhs)
	{
		x_ = y_ * rhs.z_ - rhs.y_ * z_;
		y_ = rhs.x_ * z_ - x_ * rhs.z_;
		z_ = x_ * rhs.y_ - y_ * rhs.x_;
		return *this;
	}

	real Vector3::dotProduct(const Vector3& lhs, const Vector3& rhs)
	{
		return lhs.x_ * rhs.x_ + lhs.y_ * rhs.y_ + lhs.z_ * rhs.z_;
	}

	Vector3 Vector3::crossProduct(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3(lhs.y_ * rhs.z_ - rhs.y_ * lhs.z_, rhs.x_ * lhs.z_ - lhs.x_ * rhs.z_, lhs.x_ * rhs.y_ - lhs.y_ * rhs.x_);
	}

	Vector3& Vector3::operator/=(const int& factor)
	{
		assert(!realEqual(factor, 0));
		x_ /= factor;
		y_ /= factor;
		z_ /= factor;
		return *this;
	}

	Vector3& Vector3::operator*=(const int& factor)
	{
		x_ *= factor;
		y_ *= factor;
		z_ *= factor;
		return *this;
	}

	Vector3 Vector3::operator/(const int& factor) const
	{
		assert(!realEqual(factor, 0));
		return Vector3(x_ / factor, y_ / factor, z_ / factor);
	}

	Vector3 Vector3::operator*(const int& factor) const
	{
		return Vector3(x_ * factor, y_ * factor, z_ * factor);
	}

	Vector3& Vector3::operator=(const Vector3& copy_)
	{
		if (&copy_ == this)
			return *this;
		x_ = copy_.x_;
		y_ = copy_.y_;
		z_ = copy_.z_;
		return *this;
	}
}
