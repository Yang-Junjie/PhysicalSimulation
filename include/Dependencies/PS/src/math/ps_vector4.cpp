#include "ps_vector4.hpp"
#include "ps_math.hpp"

namespace ps
{

	Vector4::Vector4(const real& x_, const real& y_, const real& z_, const real& w_)
		: x_(x_), y_(y_), z_(z_), w_(w_)
	{
	}

	Vector4& Vector4::operator=(const Vector4& copy_)
	{
		if (&copy_ == this)
			return *this;
		x_ = copy_.x_;
		y_ = copy_.y_;
		z_ = copy_.z_;
		w_ = copy_.w_;
		return *this;
	}

	Vector4& Vector4::operator=(const Vector3& copy_)
	{
		x_ = copy_.x_;
		y_ = copy_.y_;
		z_ = copy_.z_;
		w_ = 0.0;
		return *this;
	}

	Vector4::Vector4(const Vector3& copy_)
		:x_(copy_.x_), y_(copy_.y_), z_(copy_.z_), w_(0.0)
	{

	}

	Vector4 Vector4::operator+(const Vector4& rhs) const
	{
		return Vector4(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_, w_ + rhs.w_);
	}

	Vector4 Vector4::operator-(const Vector4& other) const
	{
		return Vector4(x_ - other.x_, y_ - other.y_, z_ - other.z_, w_ - other.w_);
	}
	Vector4 Vector4::operator-() const
	{
		return Vector4(-x_, -y_, -z_, -w_);
	}
	Vector4 Vector4::operator*(const real& factor) const
	{
		return Vector4(x_ * factor, y_ * factor, z_ * factor, w_ * factor);
	}

	Vector4 Vector4::operator/(const real& factor) const
	{

		assert(!realEqual(factor, 0));
		return Vector3(x_ / factor, y_ / factor, z_ / factor);
	}

	Vector4& Vector4::operator+=(const Vector4& rhs)
	{
		x_ += rhs.x_;
		y_ += rhs.y_;
		z_ += rhs.z_;
		w_ += rhs.w_;
		return *this;
	}

	Vector4& Vector4::operator-=(const Vector4& rhs)
	{
		x_ -= rhs.x_;
		y_ -= rhs.y_;
		z_ -= rhs.z_;
		w_ -= rhs.w_;
		return *this;
	}

	Vector4& Vector4::operator*=(const real& factor)
	{
		x_ *= factor;
		y_ *= factor;
		z_ *= factor;
		w_ *= factor;
		return *this;
	}

	Vector4& Vector4::operator/=(const real& factor)
	{
		assert(!realEqual(factor, 0));
		x_ /= factor;
		y_ /= factor;
		z_ /= factor;
		w_ /= factor;
		return *this;
	}

	Vector4& Vector4::set(const real& x, const real& y, const real& z, const real& w)
	{
		x_ = x;
		y_ = y;
		z_ = z;
		w_ = w;
		return *this;
	}
	

	Vector4& Vector4::set(const Vector4& other)
	{
		x_ = other.x_;
		y_ = other.y_;
		z_ = other.z_;
		w_ = other.w_;
		return *this;
	}

	Vector4& Vector4::set(const Vector3& other)
	{
		x_ = other.x_;
		y_ = other.y_;
		z_ = other.z_;
		w_ = 0.0;
		return *this;
	}

	Vector4& Vector4::clear()
	{
		x_ = 0.0;
		y_ = 0.0;
		z_ = 0.0;
		w_ = 0.0;
		return *this;
	}

	Vector4& Vector4::negate()
	{
		x_ = -x_;
		y_ = -y_;
		z_ = -z_;
		w_ = -w_;
		return *this;
	}

	Vector4& Vector4::normalize()
	{
		const real length_inv = 1/sqrt(lengthSquare());
		x_ *= length_inv;
		y_ *= length_inv;
		z_ *= length_inv;
		w_ *= length_inv;
		return *this;
	}

	real Vector4::lengthSquare() const
	{
		return x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_;
	}

	real Vector4::length() const
	{
		return sqrt(lengthSquare());
	}

	Vector4 Vector4::normal() const
	{
		return Vector4(*this).normalize();
	}

	Vector4 Vector4::negative() const
	{
		return Vector4(-x_, -y_, -z_, -w_);
	}

	bool Vector4::equal(const Vector4& rhs) const
	{
		return realEqual(x_, rhs.x_) && realEqual(y_, rhs.y_)
		&& realEqual(z_, rhs.z_) && realEqual(w_, rhs.w_);
	}

	bool Vector4::fuzzyEqual(const Vector4& rhs, const real& epsilon) const
	{
		return (*this - rhs).lengthSquare() < epsilon;
	}

	bool Vector4::isOrigin(const real& epsilon) const
	{
		return fuzzyEqual({ 0, 0, 0 , 0}, epsilon);
	}

	Vector4& Vector4::swap(Vector4& other)
	{
		realSwap(x_, other.x_);
		realSwap(y_, other.y_);
		realSwap(z_, other.z_);
		realSwap(w_, other.w_);
		return *this;
	}

	real Vector4::dot(const Vector4& rhs) const
	{
		return x_ * rhs.x_ + y_ * rhs.y_ + z_ * rhs.z_ + w_ * rhs.w_;
	}

	real Vector4::dotProduct(const Vector4& lhs, const Vector4& rhs)
	{
		return lhs.x_ * rhs.x_ + lhs.y_ * rhs.y_ + lhs.z_ * rhs.z_ + lhs.w_ * rhs.w_;
	}
	
}
