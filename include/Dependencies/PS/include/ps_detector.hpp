#ifndef PS_DETECTOR_HPP
#define PS_DETECTOR_HPP

#include "ps_math.hpp"
#include "ps_shape.hpp"
#include "ps_body.hpp"
#include "ps_narrowphase.hpp"

namespace ps
{
    struct Collision
    {
        bool isColliding = false;
        Body *bodyA = nullptr;
        Body *bodyB = nullptr;
        ContactPair contactList;
        Vector2 normal;
        real penetration = 0;
    };

    class Detector
    {
    public:
        static bool collide(const ShapePrimitive &shapeA, const ShapePrimitive &shapeB);
        static bool collide(Body *bodyA, Body *bodyB);
        static bool collide(const ShapePrimitive &shapeA, Body *bodyB);
        static bool collide(Body *bodyA, const ShapePrimitive &shapeB);

        static Collision detect(Body *bodyA, Body *bodyB);
        static Collision detect(const ShapePrimitive &shapeA, const ShapePrimitive &shapeB);
        static Collision detect(Body *bodyA, const ShapePrimitive &shapeB);
        static Collision detect(const ShapePrimitive &shapeA, Body *bodyB);

        static CollisionInfo distance(Body *bodyA, Body *bodyB);
        static CollisionInfo distance(const ShapePrimitive &shapeA, const ShapePrimitive &shapeB);
        static CollisionInfo distance(Body *bodyA, const ShapePrimitive &shapeB);
        static CollisionInfo distance(const ShapePrimitive &shapeA, Body *bodyB);

    private:
    };
}
#endif
