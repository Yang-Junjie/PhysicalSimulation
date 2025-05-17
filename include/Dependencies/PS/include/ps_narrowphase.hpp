#ifndef PHYSICS2D_NARROWPHASE_H
#define PHYSICS2D_NARROWPHASE_H
#include "ps_common.hpp"
#include "ps_shape.hpp"
#include "ps_simplex.hpp"
#include "ps_circle.hpp"
#include "ps_edge.hpp"
#include "ps_polygon.hpp"

namespace ps
{
    struct SimplexVertexWithOriginDistance
    {
        SimplexVertex vertex;
        real distance = 0.0f;
    };

    struct Feature
    {
        // circle and ellipse, use index 0
        // edge use index 0 and 1
        Vector2 vertex[2];
        Index index[2] = {UINT32_MAX, UINT32_MAX};
    };

    struct ClipVertex
    {
        Vector2 vertex;
        bool isClip = false;
        Vector2 clipperVertex;
        bool isFinalValid = false;
    };

    struct ContactPair
    {
        // contact pair1:
        //	points[0]: pointA
        //	points[1]: pointB

        // if there is second contact pair:
        //	points[2]: pointA
        //	points[3]: pointB
        std::array<Vector2, 4> points;
        std::array<uint64_t, 2> ids;
        uint32_t count = 0;

        void addContact(const Vector2 &pointA, const Vector2 &pointB)
        {
            assert(count <= 4);
            points[count++] = pointA;
            points[count++] = pointB;
        }
    };

    struct VertexPair
    {
        VertexPair() = default;
        Vector2 pointA;
        Vector2 pointB;

        bool isEmpty() const
        {
            return pointA.fuzzyEqual({0, 0}) && pointB.fuzzyEqual({0, 0});
        }

        bool operator==(const VertexPair &other) const
        {
            return (other.pointA.fuzzyEqual(this->pointA) && other.pointB.fuzzyEqual(this->pointB)) || (other.pointB.fuzzyEqual(this->pointA) && other.pointA.fuzzyEqual(this->pointB));
        }
    };

    struct CollisionInfo
    {
        Vector2 normal;
        real penetration = 0;
        Simplex simplex;
        VertexPair pair;
        //[Debug]
        Simplex originalSimplex;
        std::list<SimplexVertexWithOriginDistance> polytope;
    };

    class Narrowphase
    {
    public:
        static Simplex gjk(const ShapePrimitive &shapeA, const ShapePrimitive &shapeB, const size_t &iteration = 30);
        static CollisionInfo epa(const Simplex &simplex, const ShapePrimitive &shapeA, const ShapePrimitive &shapeB,
                                 const size_t &iteration = 30, const real &epsilon = Constant::GeometryEpsilon);
        static SimplexVertex support(const ShapePrimitive &shapeA, const ShapePrimitive &shapeB,
                                     const Vector2 &direction);
        static std::pair<Vector2, Index> findFurthestPoint(const ShapePrimitive &shape, const Vector2 &direction);
        static Vector2 findDirectionByEdge(const SimplexVertex &v1, const SimplexVertex &v2, bool pointToOrigin);
        static std::pair<Vector2, Index> findFurthestPoint(const Container::Vector<Vector2> &vertices,
                                                           const Vector2 &direction);
        static ContactPair generateContacts(const ShapePrimitive &shapeA, const ShapePrimitive &shapeB,
                                            CollisionInfo &info);

        static CollisionInfo gjkDistance(const ShapePrimitive &shapeA, const ShapePrimitive &shapeB,
                                         const size_t &iteration = 10);

    private:
        static void reconstructSimplexByVoronoi(Simplex &simplex);

        static bool perturbSimplex(Simplex &simplex, const ShapePrimitive &shapeA, const ShapePrimitive &shapeB,
                                   const Vector2 &dir);

        static Feature findFeatures(const Simplex &simplex, const Vector2 &normal, const ShapePrimitive &shape,
                                    const Index &AorB);

        static ContactPair clipTwoEdge(const Vector2 &va1, const Vector2 &va2, const Vector2 &vb1, const Vector2 &vb2,
                                       CollisionInfo &info);

        static ContactPair clipIncidentEdge(std::array<ClipVertex, 2> &incEdge, std::array<Vector2, 2> refEdge,
                                            const Vector2 &normal, bool swap);

        static ContactPair clipPolygonPolygon(const ShapePrimitive &shapeA, const ShapePrimitive &shapeB,
                                              const Feature &featureA, const Feature &featureB, CollisionInfo &info);
        static ContactPair clipPolygonEdge(const ShapePrimitive &shapeA, const ShapePrimitive &shapeB,
                                           const Feature &featureA, const Feature &featureB, CollisionInfo &info);
        static ContactPair clipPolygonRound(const ShapePrimitive &shapeA, const ShapePrimitive &shapeB,
                                            const Feature &featureA, const Feature &featureB, CollisionInfo &info);
        static ContactPair clipEdgeRound(const ShapePrimitive &shapeA, const ShapePrimitive &shapeB,
                                         const Feature &featureA, const Feature &featureB, CollisionInfo &info);
        static ContactPair clipRoundRound(const ShapePrimitive &shapeA, const ShapePrimitive &shapeB,
                                          const Feature &featureA, const Feature &featureB, CollisionInfo &info);

        static ContactPair clipEdgeVertex(const Vector2 &va1, const Vector2 &va2, const Vector2 &vb,
                                          CollisionInfo &info);

        static void polytopeIterNext(std::list<SimplexVertexWithOriginDistance>::iterator &targetIter,
                                     std::list<SimplexVertexWithOriginDistance> &list);
        static void polytopeIterPrev(std::list<SimplexVertexWithOriginDistance>::iterator &targetIter,
                                     std::list<SimplexVertexWithOriginDistance> &list);

        static void buildPolytopeFromSimplex(std::list<SimplexVertexWithOriginDistance> &polytope,
                                             const Simplex &simplex);
    };
}
#endif
