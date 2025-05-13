#include "ps_matrix2x2.hpp"

namespace ps
{
	
	Matrix2x2::Matrix2x2(const real& radian)
	{
		set(radian);
	}


	Matrix2x2::Matrix2x2(const Vector2& col1, const Vector2& col2) : column1(col1), column2(col2)
	{
	}

	Matrix2x2::Matrix2x2(const real& col1_x, const real& col1_y, const real& col2_x, const real& col2_y)
		: column1(col1_x, col1_y), column2(col2_x, col2_y)
	{
	}
	
	Matrix2x2::Matrix2x2(const Matrix2x2& mat) : column1(mat.column1), column2(mat.column2)
	{
	}

	Matrix2x2& Matrix2x2::operator=(const Matrix2x2& rhs)
	{
		if (&rhs == this)
			return *this;
		column1 = rhs.column1;
		column2 = rhs.column2;
		return *this;
	}

	Matrix2x2& Matrix2x2::operator+=(const Matrix2x2& rhs)
	{
		column1 += rhs.column1;
		column2 += rhs.column2;
		return *this;
	}

	Matrix2x2& Matrix2x2::operator-=(const Matrix2x2& rhs)
	{
		column1 -= rhs.column1;
		column2 -= rhs.column2;
		return *this;
	}

	Matrix2x2& Matrix2x2::operator*=(const real& factor)
	{
		column1 *= factor;
		column2 *= factor;
		return *this;
	}

	Matrix2x2& Matrix2x2::operator/=(const real& factor)
	{
		assert(!realEqual(factor, 0));
		column1 /= factor;
		column2 /= factor;
		return *this;
	}

	Matrix2x2 Matrix2x2::operator+(const Matrix2x2& rhs) const
	{
		return Matrix2x2(column1 + rhs.column1, column2 + rhs.column2);
	}

	Matrix2x2 Matrix2x2::operator-(const Matrix2x2& rhs) const
	{
		return Matrix2x2(column1 - rhs.column1, column2 - rhs.column2);
	}

	Vector2 Matrix2x2::row1() const
	{
		return Vector2(column1.x_, column2.x_);
	}

	Vector2 Matrix2x2::row2() const
	{
		return Vector2(column1.y_, column2.y_);
	}

	real& Matrix2x2::e11()
	{
		return column1.x_;
	}

	real& Matrix2x2::e21()
	{
		return column1.y_;
	}
	real& Matrix2x2::e12()
	{
		return column2.x_;
	}

	real& Matrix2x2::e22()
	{
		return column2.y_;
	}

	real Matrix2x2::determinant() const
	{
		return determinant(*this);
	}

	Matrix2x2& Matrix2x2::transpose()
	{
		realSwap(column1.y_, column2.x_);
		return *this;
	}

	Matrix2x2& Matrix2x2::invert()
	{
		invert(*this);
		return *this;
	}

	Matrix2x2& Matrix2x2::multiply(const Matrix2x2& rhs)
	{
		*this = multiply(*this, rhs);
		return *this;
	}

	Vector2 Matrix2x2::multiply(const Vector2& rhs) const
	{
		return multiply(*this, rhs);
	}

	Matrix2x2& Matrix2x2::clear()
	{
		column1.clear();
		column2.clear();
		return *this;
	}

	Matrix2x2& Matrix2x2::set(const real& col1_x, const real& col1_y, const real& col2_x, const real& col2_y)
	{
		column1.set(col1_x, col1_y);
		column2.set(col2_x, col2_y);
		return *this;
	}

	Matrix2x2& Matrix2x2::set(const Vector2& col1, const Vector2& col2)
	{
		column1 = col1;
		column2 = col2;
		return *this;
	}

	Matrix2x2& Matrix2x2::set(const Matrix2x2& other)
	{
		column1 = other.column1;
		column2 = other.column2;
		return *this;
	}

	Matrix2x2& Matrix2x2::set(const real& radian)
	{
		const real c = Math::cosx(radian);
		const real s = Math::sinx(radian);
		column1.set(c, s);
		column2.set(-s, c);
		return *this;
	}

	Matrix2x2 Matrix2x2::fromRadian(const real& radian)
	{
		Matrix2x2 mat;
		mat.set(radian);
		return mat;
	}

	Matrix2x2 Matrix2x2::skewSymmetricMatrix(const Vector2& r)
	{
		return Matrix2x2(0, -r.y_, r.x_, 0);
	}

	Matrix2x2 Matrix2x2::identityMatrix()
	{
		return Matrix2x2(1, 0, 0, 1);
	}

	Vector2 Matrix2x2::multiply(const Matrix2x2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.column1.x_ * rhs.x_ + lhs.column2.x_ * rhs.y_, lhs.column1.y_ * rhs.x_ + lhs.column2.y_ * rhs.y_);
	}

	Matrix2x2 Matrix2x2::multiply(const Matrix2x2& lhs, const Matrix2x2& rhs)
	{
		return Matrix2x2(lhs.column1.x_ * rhs.column1.x_ + lhs.column2.x_ * rhs.column1.y_,
		                 lhs.column1.y_ * rhs.column1.x_ + lhs.column2.y_ * rhs.column1.y_,
		                 lhs.column1.x_ * rhs.column2.x_ + lhs.column2.x_ * rhs.column2.y_,
		                 lhs.column1.y_ * rhs.column2.x_ + lhs.column2.y_ * rhs.column2.y_);
	}

	real Matrix2x2::determinant(const Matrix2x2& mat)
	{
		return mat.column1.x_ * mat.column2.y_ - mat.column2.x_ * mat.column1.y_;
	}

	bool Matrix2x2::invert(Matrix2x2& mat)
	{
		const real det = mat.determinant();

		if (realEqual(det, 0))
			return false;

		realSwap(mat.column1.x_, mat.column2.y_);
		mat.column1.y_ *= -1;
		mat.column2.x_ *= -1;
		mat /= det;
		return true;
	}
}
