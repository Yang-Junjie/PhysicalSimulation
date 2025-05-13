#ifndef PS_MATH_HPP
#define PS_MATH_HPP
#include "ps_common.hpp"
#include <algorithm>
inline void realSwap(real &lhs, real &rhs)
{
    const real temp = lhs;
    lhs = rhs;
    rhs = temp;
}

inline bool fuzzyRealEqual(const real &lhs, const real &rhs,
                           const real &epsilon = Constant::GeometryEpsilon)
{
    return std::fabs(lhs - rhs) < epsilon;
}

inline bool realEqual(const real &lhs, const real &rhs)
{
    return fuzzyRealEqual(lhs, rhs, Constant::GeometryEpsilon);
}
class Math
{
public:
    static real bernstein(const real &t, const real &i, const real &n)
    {
        return combination(n, i) * std::pow(t, i) * std::pow(1.0f - t, n - i);
    }

    static real dBernstein(const real &t, const real &i, const real &n)
    {
        if (i == 0)
            return -1.0f * n * std::pow(1.0f - t, n - 1);

        if (i == n)
            return n * std::pow(t, n - 1);

        return combination(n, i) * (i * std::pow(t, i - 1) * std::pow(1.0f - t, n - i) -
                                    (n - i) * std::pow(t, i) * std::pow(1.0f - t, n - i - 1));
    }

    static real d2Bernstein(const real &t, const real &i, const real &n)
    {
        if (i == 0)
            return n * (n - 1) * std::pow(1.0f - t, n - 2.0f);

        if (i == 1)
            return combination(n, 1) * (-2.0f * (n - 1.0f) * std::pow(1.0f - t, n - 2.0f) +
                                        (n - 1.0f) * (n - 2.0f) * t * std::pow(1.0f - t, n - 3.0f));

        if (i == 2)
            return combination(n, 2) * (2.0f * std::pow(1.0f - t, n - 2.0f) - 4.0f * (n - 2.0f) * t * std::pow(1.0f - t, n - 3.0f) +
                                        (n - 2.0f) * (n - 3.0f) * t * t * std::pow(1.0f - t, n - 3.0f));

        if (i == n)
            return n * (n - 1) * std::pow(t, n - 2.0f);

        return combination(n, i) * (i * (i - 1.0f) * std::pow(t, i - 2.0f) * std::pow(1.0f - t, n - i) - 2.0f * i * (n - i) * std::pow(t, i - 1.0f) * std::pow(1.0f - t, n - i - 1.0f) +
                                    (n - i) * (n - i - 1.0f) * std::pow(t, i) * std::pow(1.0f - t, n - i - 2.0f));
    }

    static real combination(const real &n, const real &m)
    {
        real a = 1.0f, b = 1.0f, c = 1.0f;
        for (real i = n; i > 0; i -= 1.0f)
            a *= i;
        for (real i = m; i > 0; i -= 1.0f)
            b *= i;
        for (real i = n - m; i > 0; i -= 1.0f)
            c *= i;
        return a / (b * c);
    }

    // trigonometric function
    static real abs(const real &x)
    {
        return std::fabs(x);
    }

    static real sinx(const real &x)
    {
        return std::sin(x);
    }

    static real cosx(const real &x)
    {
        return std::cos(x);
    }

    static real tanx(const real &x)
    {
        return std::tan(x);
    }

    static real arcsinx(const real &x)
    {
        return std::asin(x);
    }

    static real arccosx(const real &x)
    {
        return std::acos(x);
    }

    static real arctanx(const real &y, const real &x)
    {
        return std::atan2(y, x);
    }

    static real max(const real &a, const real &b)
    {
        return std::max(a, b);
    }

    static real min(const real &a, const real &b)
    {
        return std::min(a, b);
    }

    static real tripleMin(const real &a, const real &b, const real &c)
    {
        return std::min(std::min(a, b), c);
    }

    static real tripleMax(const real &a, const real &b, const real &c)
    {
        return std::max(std::max(a, b), c);
    }

    static real absMax(const real &a, const real &b)
    {
        return std::max(std::fabs(a), std::fabs(b));
    }

    static real absMin(const real &a, const real &b)
    {
        return std::min(std::fabs(a), std::fabs(b));
    }

    static real sqrt(const real &x)
    {
        return std::sqrt(x);
    }

    static real pow(const real &x, const real &e)
    {
        return std::pow(x, e);
    }

    // other
    static bool sameSign(const real &a, const real &b)
    {
        return a >= 0 && b >= 0 || a <= 0 && b <= 0;
    }

    static bool sameSign(const real &a, const real &b, const real &c)
    {
        return a >= 0 && b >= 0 && c >= 0 || a <= 0 && b <= 0 && c <= 0;
    }

    static bool sameSignStrict(const real &a, const real &b)
    {
        return a > 0 && b > 0 || a < 0 && b < 0;
    }

    static bool sameSignStrict(const real &a, const real &b, const real &c)
    {
        return a > 0 && b > 0 && c > 0 || a < 0 && b < 0 && c < 0;
    }

    static int sign(const real &num)
    {
        return num > 0 ? 1 : -1;
    }

    static bool isInRange(const real &value, const real &low, const real &high,
                          const real &epsilon = Constant::GeometryEpsilon)
    {
        return value >= low - epsilon && value <= high + epsilon;
    }

    static bool fuzzyIsInRange(const real &value, const real &low, const real &high,
                               const real &epsilon = Constant::GeometryEpsilon)
    {
        return value >= low - epsilon && value <= high + epsilon || value <= low + epsilon && low >= high - epsilon;
    }

    static real clamp(const real &num, const real &low, const real &high)
    {
        return (num < low) ? low : (high < num) ? high
                                                : num;
    }

    static size_t clamp(const size_t &num, const size_t &low, const size_t &high)
    {
        if (num < low)
            return low;
        if (num > high)
            return high;
        return num;
    }

    static real degreeToRadian(const real &angle)
    {
        return angle * (Constant::Pi / 180.0f);
    }

    static real radianToDegree(const real &radian)
    {
        return radian * (180.0f / Constant::Pi);
    }
};
#endif