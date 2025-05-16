#ifndef PS_CIRCLE_HPP
#define PS_CIRCLE_HPP
#include "ps_shape.hpp"
/**
 * @brief Represents a circle shape in the ps namespace.
 * 
 * The Circle class inherits from Shape and provides functionality
 * for circles, including radius manipulation, scaling, containment checks,
 * and center retrieval.
 */
namespace ps
{
    class Circle : public Shape
    {

    public:
        Circle(real radius = 0);

        real radius() const;
        void setRadius(const real& radius);
        void scale(const real& factor) override;
        bool contains(const Vector2& point, const real& epsilon = Constant::GeometryEpsilon) override;
        Vector2 center()const override;
    private:
        real m_radius;
    };
}
#endif