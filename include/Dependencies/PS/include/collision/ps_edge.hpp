#ifndef PHYSICAL_SIMULATION_EDGE_HPP
#define PHYSICAL_SIMULATION_EDGE_HPP
#include "ps_shape.hpp"
namespace ps
{
    class   Edge : public Shape
    {

    public:
        Edge();

        void set(const Vector2& start, const Vector2& end);

        Vector2 startPoint()const;
        void setStartPoint(const Vector2& start);

        Vector2 endPoint()const;
        void setEndPoint(const Vector2& end);
        void scale(const real& factor) override;
        bool contains(const Vector2& point, const real& epsilon = Constant::GeometryEpsilon) override;
        Vector2 center()const override;
        Vector2 normal()const;
        void setNormal(const Vector2& normal);
    private:
        //0: start
        //1: end
        Vector2 m_point[2];
        Vector2 m_normal;
    };
}
#endif