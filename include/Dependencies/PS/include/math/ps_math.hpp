#ifndef PHYSICAL_SIMULATION_MATH_HPP
#define PHYSICAL_SIMULATION_MATH_HPP
#include "ps_common.hpp"
#include "immintrin.h"
#include "xmmintrin.h"

namespace ps
{
	//basic real utilities
	 inline void realSwap(real& lhs, real& rhs)
	{
		const real temp = lhs;
		lhs = rhs;
		rhs = temp;
	}

	 inline bool fuzzyRealEqual(const real& lhs, const real& rhs,
	                                         const real& epsilon = Constant::GeometryEpsilon)
	{
		return std::fabs(lhs - rhs) < epsilon;
	}

	 inline bool realEqual(const real& lhs, const real& rhs)
	{
		return fuzzyRealEqual(lhs, rhs, Constant::GeometryEpsilon);
	}

	class Math
	{
	public:
		//trigonometric function
		 static real abs(const real& x)
		{
			return std::fabs(x);
		}

		 static real sinx(const real& x)
		{
			return std::sin(x);
		}

		 static real cosx(const real& x)
		{
			return std::cos(x);
		}

		 static real tanx(const real& x)
		{
			return std::tan(x);
		}

		 static real arcsinx(const real& x)
		{
			return std::asin(x);
		}

		 static real arccosx(const real& x)
		{
			return std::acos(x);
		}

		 static real arctanx(const real& y, const real& x)
		{
			return std::atan2(y, x);
		}

		 static real max(const real& a, const real& b)
		{
			return std::max(a, b);
		}

		 static real min(const real& a, const real& b)
		{
			return std::min(a, b);
		}

		 static real tripleMin(const real& a, const real& b, const real& c)
		{
			return std::min(std::min(a, b), c);
		}

		 static real tripleMax(const real& a, const real& b, const real& c)
		{
			return std::max(std::max(a, b), c);
		}

		 static real absMax(const real& a, const real& b)
		{
			return std::max(std::fabs(a), std::fabs(b));
		}

		 static real absMin(const real& a, const real& b)
		{
			return std::min(std::fabs(a), std::fabs(b));
		}

		 static real sqrt(const real& x)
		{
			return std::sqrt(x);
		}

		 static real pow(const real& x, const real& e)
		{
			return std::pow(x, e);
		}

		//other
		 static bool sameSign(const real& a, const real& b)
		{
			return a >= 0 && b >= 0 || a <= 0 && b <= 0;
		}

		 static bool sameSign(const real& a, const real& b, const real& c)
		{
			return a >= 0 && b >= 0 && c >= 0 || a <= 0 && b <= 0 && c <= 0;
		}

		 static bool sameSignStrict(const real& a, const real& b)
		{
			return a > 0 && b > 0 || a < 0 && b < 0;
		}

		 static bool sameSignStrict(const real& a, const real& b, const real& c)
		{
			return a > 0 && b > 0 && c > 0 || a < 0 && b < 0 && c < 0;
		}

		 static int8_t sign(const real& num)
		{
			return num > 0 ? 1 : -1;
		}

		 static bool isInRange(const real& value, const real& low, const real& high,
		                                    const real& epsilon = Constant::GeometryEpsilon)
		{
			return value >= low - epsilon && value <= high + epsilon;
		}

		 static bool fuzzyIsInRange(const real& value, const real& low, const real& high,
		                                         const real& epsilon = Constant::GeometryEpsilon)
		{
			return value >= low - epsilon && value <= high + epsilon || value <= low + epsilon && low >= high - epsilon;
		}

		 static real clamp(const real& num, const real& low, const real& high)
		{
			return std::clamp(num, low, high);
		}

		 static size_t clamp(const size_t& num, const size_t& low, const size_t& high)
		{
			if (num < low)
				return low;
			if (num > high)
				return high;
			return num;
		}

		 static real degreeToRadian(const real& angle)
		{
			return angle * (Constant::Pi / 180.0f);
		}

		 static real radianToDegree(const real& radian)
		{
			return radian * (180.0f / Constant::Pi);
		}

		template <typename T, size_t iterations = 4>
		 static T fastInverseSqrt(T x)
		{
			using Tint = std::conditional_t<sizeof(T) == 8, std::int64_t, std::int32_t>;
			T y = x;
			T x2 = y * 0.5f;
			Tint i = *(Tint*)&y;
			i = (sizeof(T) == 8 ? 0x5fe6eb50c7b537a9 : 0x5f3759df) - (i >> 1);
			y = *(T*)&i;
			for (size_t k = 0; k <= iterations; k++)
				y = y * (1.5f - (x2 * y * y));
			return y;
		}
	};
}
#endif
