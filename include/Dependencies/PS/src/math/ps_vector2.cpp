#include "ps_vector2.hpp"
#include "ps_math.hpp"
namespace ps
{
	Vector2::Vector2(const real& _x_, const real& _y_) : x_(_x_), y_(_y_)
	{
		assert(!std::isnan(x_));
		assert(!std::isnan(y_));
	}

	Vector2::Vector2(const Vector2& copy_) : x_(copy_.x_), y_(copy_.y_)
	{
		assert(!std::isnan(x_));
		assert(!std::isnan(y_));
	}

	Vector2 Vector2::operator+(const Vector2& rhs) const
	{
		return Vector2(x_ + rhs.x_, y_ + rhs.y_);
	}

	Vector2 Vector2::operator-(const Vector2& rhs) const
	{
		return Vector2(x_ - rhs.x_, y_ - rhs.y_);
	}
	Vector2 Vector2::operator-()const
	{
		return Vector2(-x_, -y_);
	}
	Vector2 Vector2::operator*(const int& factor) const
	{
		return Vector2(x_ * factor, y_ * factor);
	}

	Vector2 Vector2::operator/(const real& factor) const
	{
		assert(!realEqual(factor, 0));
		return Vector2(x_ / factor, y_ / factor);
	}

	Vector2& Vector2::operator+=(const Vector2& rhs)
	{
		x_ += rhs.x_;
		y_ += rhs.y_;
		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& rhs)
	{
		x_ -= rhs.x_;
		y_ -= rhs.y_;
		return *this;
	}

	Vector2& Vector2::operator*=(const real& factor)
	{
		x_ *= factor;
		y_ *= factor;
		return *this;
	}

	Vector2& Vector2::operator/=(const real& factor)
	{
		assert(!realEqual(factor, 0));
		x_ /= factor;
		y_ /= factor;
		return *this;
	}

	bool Vector2::operator==(const Vector2& rhs) const
	{
		return realEqual(x_, rhs.x_) && realEqual(y_, rhs.y_);
	}

	bool Vector2::operator!=(const Vector2& rhs) const
	{
		return !realEqual(x_, rhs.x_) || !realEqual(y_, rhs.y_);
	}

	real Vector2::lengthSquare() const
	{
		return x_ * x_ + y_ * y_;
	}

	real Vector2::length() const
	{
		return std::sqrt(lengthSquare());
	}

	real Vector2::theta() const
	{
		return Math::arctanx(y_, x_);
	}

	Vector2& Vector2::set(const real& _x_, const real& _y_)
	{
		x_ = _x_;
		y_ = _y_;
		return *this;
	}

	Vector2& Vector2::set(const Vector2& copy_)
	{
		x_ = copy_.x_;
		y_ = copy_.y_;
		return *this;
	}

	Vector2& Vector2::clear()
	{
		x_ = 0.0f;
		y_ = 0.0f;
		return *this;
	}

	Vector2& Vector2::negate()
	{
		x_ *= -1.0f;
		y_ *= -1.0f;
		return *this;
	}

	Vector2& Vector2::swap(Vector2& other) noexcept
	{
		realSwap(x_, other.x_);
		realSwap(y_, other.y_);
		return *this;
	}

	Vector2& Vector2::normalize()
	{
		const real length_inv = 1.0f / std::sqrt(lengthSquare());
		assert(!std::isinf(length_inv));
		//

		//const real length_inv = Math::fastInverseSqrt<real>(lengthSquare());
		x_ *= length_inv;
		y_ *= length_inv;

		return *this;
	}

	Vector2 Vector2::normal() const
	{
		return Vector2(*this).normalize();
	}

	Vector2 Vector2::negative() const
	{
		return Vector2(-x_, -y_);
	}

	bool Vector2::equal(const Vector2& rhs) const
	{
		return realEqual(x_, rhs.x_) && realEqual(y_, rhs.y_);
	}

	bool Vector2::fuzzyEqual(const Vector2& rhs, const real& epsilon)const
	{
		return fuzzyRealEqual(x_, rhs.x_, epsilon) && fuzzyRealEqual(y_, rhs.y_, epsilon);
	}

	bool Vector2::isOrigin(const real& epsilon) const
	{
		return fuzzyEqual({ 0, 0 }, epsilon);
	}

	bool Vector2::isSameQuadrant(const Vector2& rhs) const
	{
		return Math::sameSign(x_, rhs.x_) && Math::sameSign(y_, rhs.y_);
	}

	real Vector2::dot(const Vector2& rhs) const
	{
		return x_ * rhs.x_ + y_ * rhs.y_;
	}

	real Vector2::cross(const Vector2& rhs) const
	{
		return x_ * rhs.y_ - y_ * rhs.x_;
	}

	Vector2& Vector2::matchSign(const Vector2& rhs)
	{
		x_ = std::abs(x_);
		y_ = std::abs(y_);
		if (rhs.x_ < 0)
			x_ = -x_;
		if (rhs.y_ < 0)
			y_ = -y_;
		return *this;
	}

	Vector2 Vector2::perpendicular() const
	{
		return Vector2(-y_, x_);
	}

	real Vector2::dotProduct(const Vector2& lhs, const Vector2& rhs)
	{
		return lhs.x_ * rhs.x_ + lhs.y_ * rhs.y_;
	}

	real Vector2::crossProduct(const Vector2& lhs, const Vector2& rhs)
	{
		return lhs.x_ * rhs.y_ - lhs.y_ * rhs.x_;
	}

	real Vector2::crossProduct(const real& x_1, const real& y_1, const real& x_2, const real& y_2)
	{
		return x_1 * y_2 - x_2 * y_1;
	}

	Vector2 Vector2::crossProduct(const real& lhs, const Vector2& rhs)
	{
		return Vector2(-rhs.y_, rhs.x_) * lhs;
	}

	Vector2 Vector2::crossProduct(const Vector2& lhs, const real& rhs)
	{
		return Vector2(lhs.y_, -lhs.x_) * rhs;
	}

	Vector2 Vector2::lerp(const Vector2& lhs, const Vector2& rhs, const real& t)
	{
		return lhs + (rhs - lhs) * t;
	}

	Vector2& Vector2::operator/=(const int& factor)
	{
		assert(!realEqual(factor, 0));
		x_ /= factor;
		y_ /= factor;
		return *this;
	}

	Vector2& Vector2::operator*=(const int& factor)
	{
		x_ *= factor;
		y_ *= factor;
		return *this;
	}

	Vector2 Vector2::operator/(const int& factor) const
	{
		assert(!realEqual(factor, 0));
		return Vector2(x_ / factor, y_ / factor);
	}

	Vector2 Vector2::operator*(const real& factor) const
	{
		return Vector2(x_ * factor, y_ * factor);
	}

	Vector2& Vector2::operator=(const Vector2& copy_)
	{
		if (&copy_ == this)
			return *this;
		x_ = copy_.x_;
		y_ = copy_.y_;
		return *this;
	}
}
