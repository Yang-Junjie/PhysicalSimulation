#include "ps_matrix3x3.hpp"

namespace ps
{
	Matrix3x3::Matrix3x3(const Matrix3x3 &mat) : column1(mat.column1), column2(mat.column2), column3(mat.column3)
	{
	}

	Matrix3x3::Matrix3x3(const Vector3 &col1, const Vector3 &col2, const Vector3 &col3)
		: column1(col1), column2(col2), column3(col3)
	{
	}

	Matrix3x3::Matrix3x3(const real &col1_x, const real &col1_y, const real &col1_z, const real &col2_x,
						 const real &col2_y, const real &col2_z, const real &col3_x, const real &col3_y,
						 const real &col3_z)
		: column1(col1_x, col1_y, col1_z), column2(col2_x, col2_y, col2_z), column3(col3_x, col3_y, col3_z)
	{
	}

	Matrix3x3 &Matrix3x3::operator=(const Matrix3x3 &rhs)
	{
		if (&rhs == this)
			return *this;
		column1 = rhs.column1;
		column2 = rhs.column2;
		column3 = rhs.column3;
		return *this;
	}

	Matrix3x3 &Matrix3x3::operator=(const Matrix2x2 &rhs)
	{
		column1.x_ = rhs.column1.x_;
		column1.y_ = rhs.column1.y_;
		column1.z_ = 0;
		column2.x_ = rhs.column2.x_;
		column2.y_ = rhs.column2.y_;
		column2.z_ = 0;
		column3.clear();
		return *this;
	}

	Matrix3x3 &Matrix3x3::operator+=(const Matrix3x3 &rhs)
	{
		column1 += rhs.column1;
		column2 += rhs.column2;
		column3 += rhs.column3;
		return *this;
	}

	Matrix3x3 &Matrix3x3::operator-=(const Matrix3x3 &rhs)
	{
		column1 -= rhs.column1;
		column2 -= rhs.column2;
		column3 -= rhs.column3;
		return *this;
	}

	Matrix3x3 &Matrix3x3::operator*=(const real &factor)
	{
		column1 *= factor;
		column2 *= factor;
		column3 *= factor;
		return *this;
	}

	Matrix3x3 &Matrix3x3::operator/=(const real &factor)
	{
		assert(!realEqual(factor, 0));
		column1 /= factor;
		column2 /= factor;
		column3 /= factor;
		return *this;
	}

	Vector3 Matrix3x3::row1() const
	{
		return Vector3(column1.x_, column2.x_, column3.x_);
	}

	Vector3 Matrix3x3::row2() const
	{
		return Vector3(column1.y_, column2.y_, column3.y_);
	}

	Vector3 Matrix3x3::row3() const
	{
		return Vector3(column1.z_, column2.z_, column3.z_);
	}

	real &Matrix3x3::e11()
	{
		return column1.x_;
	}

	real &Matrix3x3::e12()
	{
		return column2.x_;
	}

	real &Matrix3x3::e13()
	{
		return column3.x_;
	}

	real &Matrix3x3::e21()
	{
		return column1.y_;
	}

	real &Matrix3x3::e22()
	{
		return column2.y_;
	}

	real &Matrix3x3::e23()
	{
		return column3.y_;
	}

	real &Matrix3x3::e31()
	{
		return column1.z_;
	}

	real &Matrix3x3::e32()
	{
		return column2.z_;
	}

	real &Matrix3x3::e33()
	{
		return column3.z_;
	}

	real Matrix3x3::determinant() const
	{
		return determinant(*this);
	}

	Matrix3x3 &Matrix3x3::transpose()
	{
		realSwap(column1.y_, column2.x_);
		realSwap(column1.z_, column3.x_);
		realSwap(column2.z_, column3.y_);
		return *this;
	}

	Matrix3x3 &Matrix3x3::invert()
	{
		invert(*this);
		return *this;
	}

	Matrix3x3 &Matrix3x3::clear()
	{
		column1.clear();
		column2.clear();
		column3.clear();
		return *this;
	}

	Matrix3x3 &Matrix3x3::set(const real &col1_x, const real &col1_y, const real &col1_z, const real &col2_x,
							  const real &col2_y, const real &col2_z, const real &col3_x, const real &col3_y,
							  const real &col3_z)
	{
		column1.set(col1_x, col1_y, col1_z);
		column2.set(col2_x, col2_y, col2_z);
		column3.set(col3_x, col3_y, col3_z);
		return *this;
	}

	Matrix3x3 &Matrix3x3::set(const Vector3 &col1, const Vector3 &col2, const Vector3 &col3)
	{
		column1 = col1;
		column2 = col2;
		column3 = col3;
		return *this;
	}

	Matrix3x3 &Matrix3x3::set(const Matrix3x3 &other)
	{
		column1 = other.column1;
		column2 = other.column2;
		column3 = other.column3;
		return *this;
	}

	Vector3 Matrix3x3::multiply(const Vector3 &rhs) const
	{
		return multiply(*this, rhs);
	}

	Vector2 Matrix3x3::multiply(const Vector2 &rhs) const
	{
		return multiply(*this, rhs);
	}

	Matrix3x3 &Matrix3x3::multiply(const Matrix3x3 &rhs)
	{
		*this = multiply(*this, rhs);
		return *this;
	}

	Matrix3x3 Matrix3x3::skewSymmetricMatrix(const Vector3 &v)
	{
		return Matrix3x3(
			0, v.z_, -v.y_,
			-v.z_, 0, v.x_,
			v.y_, -v.x_, 0);
	}

	Matrix3x3 Matrix3x3::identityMatrix()
	{
		return Matrix3x3(1, 0, 0, 0, 1, 0, 0, 0, 1);
	}

	Matrix3x3 Matrix3x3::multiply(const Matrix3x3 &lhs, const Matrix3x3 &rhs)
	{
		return Matrix3x3(multiply(lhs, rhs.column1),
						 multiply(lhs, rhs.column2),
						 multiply(lhs, rhs.column3));
	}

	Vector3 Matrix3x3::multiply(const Matrix3x3 &lhs, const Vector3 &rhs)
	{
		return Vector3(lhs.column1.x_ * rhs.x_ + lhs.column2.x_ * rhs.y_ + lhs.column3.x_ * rhs.z_,
					   lhs.column1.y_ * rhs.x_ + lhs.column2.y_ * rhs.y_ + lhs.column3.y_ * rhs.z_,
					   lhs.column1.z_ * rhs.x_ + lhs.column2.z_ * rhs.y_ + lhs.column3.z_ * rhs.z_);
	}

	Vector2 Matrix3x3::multiply(const Matrix3x3 &lhs, const Vector2 &rhs)
	{
		return Vector2(lhs.column1.x_ * rhs.x_ + lhs.column2.x_ * rhs.y_,
					   lhs.column1.y_ * rhs.x_ + lhs.column2.y_ * rhs.y_);
	}

	real Matrix3x3::determinant(const Matrix3x3 &mat)
	{
		return mat.column1.x_ * Vector2::crossProduct(mat.column2.y_, mat.column2.z_, mat.column3.y_, mat.column3.z_) +
			   mat.column2.x_ * Vector2::crossProduct(mat.column3.y_, mat.column3.z_, mat.column1.y_, mat.column1.z_) +
			   mat.column3.x_ * Vector2::crossProduct(mat.column1.y_, mat.column1.z_, mat.column2.y_, mat.column2.z_);
	}

	bool Matrix3x3::invert(Matrix3x3 &mat)
	{
		const real det = mat.determinant();
		if (realEqual(det, 0.0f))
			return false;

		const real det11 = Vector2::crossProduct(mat.column2.y_, mat.column2.z_, mat.column3.y_, mat.column3.z_);
		const real det12 = Vector2::crossProduct(mat.column2.x_, mat.column2.z_, mat.column3.x_, mat.column3.z_) * -1;
		const real det13 = Vector2::crossProduct(mat.column2.x_, mat.column2.y_, mat.column3.x_, mat.column3.y_);

		const real det21 = Vector2::crossProduct(mat.column1.y_, mat.column1.z_, mat.column3.y_, mat.column3.z_) * -1;
		const real det22 = Vector2::crossProduct(mat.column1.x_, mat.column1.z_, mat.column3.x_, mat.column3.z_);
		const real det23 = Vector2::crossProduct(mat.column1.x_, mat.column1.y_, mat.column3.x_, mat.column3.y_) * -1;

		const real det31 = Vector2::crossProduct(mat.column1.y_, mat.column1.z_, mat.column2.y_, mat.column2.z_);
		const real det32 = Vector2::crossProduct(mat.column1.x_, mat.column1.z_, mat.column2.x_, mat.column2.z_) * -1;
		const real det33 = Vector2::crossProduct(mat.column1.x_, mat.column1.y_, mat.column2.x_, mat.column2.y_);

		mat.set(det11, det12, det13, det21, det22, det23, det31, det32, det33);
		mat.transpose();
		mat /= det;
		return true;
	}
}
