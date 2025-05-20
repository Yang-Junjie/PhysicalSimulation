#ifndef PHYSICAL_SIMULATION_POLYGON_HPP
#define PHYSICAL_SIMULATION_POLYGON_HPP
#include "ps_shape.hpp"
namespace ps
{
    class   Polygon : public Shape
    {

    public:
        Polygon();

        const Container::Vector<Vector2> &vertices() const;
        const Container::Vector<int> &indices() const;
        void append(const std::initializer_list<Vector2> &vertices);
        void append(const Vector2 &vertex);
        Vector2 center() const override;
        void scale(const real &factor) override;
        bool contains(const Vector2 &point, const real &epsilon = Constant::GeometryEpsilon) override;

    protected:
        Container::Vector<Vector2> m_vertices;
        Container::Vector<int> m_indices;
        void updateVertices();
        void updateIndex();
    };
}
#endif