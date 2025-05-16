#ifndef PS_COMMON_HPP
#define PS_COMMON_HPP
#include <limits>
#include <cmath>
#include <assert.h>
#include <iostream>
#include <vector>
#include <optional>
#include <initializer_list>
#include <vector>
#include <tuple>
#include <optional>
#include <list>

#ifndef SINGLE_PRECISION
using real = float;

namespace Constant
{
	constexpr unsigned int SimplexMax = 8;
	constexpr unsigned int CCDMaxIterations = 20;
	constexpr real Epsilon = 0.00000000000000001f;
	constexpr real Max = 3.402823466e+38F;
	constexpr real PositiveMin = 1.175494351e-38F;
	constexpr real NegativeMin = -3.402823466e+38F;
	constexpr real Pi = 3.1415926535f;
	constexpr real HalfPi = Pi / 2.0f;
	constexpr real DoublePi = Pi * 2.0f;
	constexpr real ReciprocalOfPi = 0.3183098861f;
	constexpr real GeometryEpsilon = 1e-6f;
	constexpr real TrignometryEpsilon = 1e-3f;
	constexpr real CCDMinVelocity = 100.0f;
	constexpr real MaxVelocity = 1000.0f;
	constexpr real MaxAngularVelocity = 1000.0f;
	constexpr real AABBExpansionFactor = 0.0f;
	constexpr real MinLinearVelocity = 1e-4f;
	constexpr real MinAngularVelocity = 1e-4f;
	constexpr real MinEnergy = 9e-10f;
	constexpr size_t SleepCountdown = 32;
	constexpr int GJKRetryTimes = 8;
}
#else
using real = double;
namespace Constant
{
	constexpr unsigned int SimplexMax = 8;
	constexpr real Epsilon = DBL_EPSILON;
	constexpr real Max = DBL_MAX;
	constexpr real PositiveMin = DBL_MIN;
	constexpr real NegativeMin = -Max;
	constexpr real Pi = 3.141592653589793238463;
	constexpr real HalfPi = Constant::Pi / 2.0;
	constexpr real DoublePi = Constant::Pi * 2.0;
	constexpr real ReciprocalOfPi = 0.3183098861837907;
	constexpr real GeometryEpsilon = 0.0000001;
	constexpr real CCDMinVelocity = 100.0;
	constexpr real MaxVelocity = 1000.0;
	constexpr real MaxAngularVelocity = 1000.0;
	constexpr real AABBExpansionFactor = 0.0;
	constexpr real MinLinearVelocity = 1e-4;
	constexpr real MinAngularVelocity = 1e-4;
	constexpr size_t SleepCountdown = 32;

}
#endif
#endif