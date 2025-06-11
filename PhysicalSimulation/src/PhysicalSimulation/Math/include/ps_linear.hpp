#ifndef MATH_LINEAR_HPP
#define MATH_LINEAR_HPP
#include "ps_vector2.hpp"
#include "ps_vector3.hpp"
#include "ps_vector4.hpp"
#include "ps_matrix2x2.hpp"
#include "ps_matrix3x3.hpp"
#include "ps_matrix4x4.hpp"

namespace ps
{
	inline Vector2 operator*(const real &f, const Vector2 &v)
	{
		return v * f;
	}
	inline Vector3 operator*(const real &f, const Vector3 &v)
	{
		return v * f;
	}
}
#endif