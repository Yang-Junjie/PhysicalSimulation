#ifndef PHYSICAL_SIMULATION_RECTANGLE_HPP
#define PHYSICAL_SIMULATION_RECTANGLE_HPP
#include "ps_polygon.hpp"
namespace ps
{
    class   Rectangle : public Polygon
    {

    public:
        Rectangle(const real& width = 0, const real& height = 0);
        void set(const real& width, const real& height);

        real width()const;
        void setWidth(const real& width);

        real height()const;
        void setHeight(const real& height);

        void scale(const real& factor) override;
        bool contains(const Vector2& point, const real& epsilon = Constant::GeometryEpsilon) override;
    private:
        void calcVertices();
        real m_width;
        real m_height;
    };
}
#endif