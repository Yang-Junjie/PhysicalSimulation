#ifndef PS_BODY_HPP
#define PS_BODY_HPP
#include "ps_aabb.hpp"
#include "ps_math.hpp"
#include "ps_common.hpp"
#include "ps_shape.hpp"
#include "ps_integrator.hpp"
#include "ps_circle.hpp"

#include "ps_edge.hpp"
#include "ps_polygon.hpp"
namespace ps
{
    class Body
    {
    public:
        struct BodyPair
        {
            using BodyPairID = uint64_t;
            static BodyPairID generateBodyPairID(Body *bodyA, Body *bodyB);
            static BodyPair generateBodyPair(Body *bodyA, Body *bodyB);
            BodyPairID pairID;
            Body *bodyA;
            Body *bodyB;
        };

        enum class BodyType
        {
            Kinematic,
            Static,
            Dynamic,
            Bullet
        };

        struct PhysicsAttribute
        {
            Vector2 position;
            Vector2 velocity;
            real rotation = 0;
            real angularVelocity = 0;
            void step(const real &dt);
        };

        Body() = default;
        Vector2 &position();

        Vector2 &velocity();

        real &rotation();

        real &angularVelocity();

        Vector2 &forces();
        void clearTorque();

        real &torques();

        Vector2 &lastPosition();
        real &lastRotation();
        uint32_t &sleepCountdown(); // 物体休眠前的倒计时

        Shape *shape() const;
        void setShape(Shape *shape);

        BodyType type() const;
        void setType(const BodyType &type);

        real mass() const;
        void setMass(const real &mass);

        real inertia() const;

        AABB aabb(const real &factor = Constant::AABBExpansionFactor) const;

        real friction() const;
        void setFriction(const real &friction);

        bool sleep() const;
        void setSleep(bool sleep);

        real inverseMass() const;
        real inverseInertia() const;

        PhysicsAttribute physicsAttribute() const;
        void setPhysicsAttribute(const PhysicsAttribute &info);

        void stepPosition(const real &dt);

        void applyImpulse(const Vector2 &impulse, const Vector2 &r);
        Vector2 toLocalPoint(const Vector2 &point) const;
        Vector2 toWorldPoint(const Vector2 &point) const;
        Vector2 toActualPoint(const Vector2 &point) const;

        uint32_t id() const;
        void setId(const uint32_t &id);

        uint32_t bitmask() const;
        void setBitmask(const uint32_t &bitmask);

        real restitution() const;
        void setRestitution(const real &restitution);

        real kineticEnergy() const;

    private:
        void calcInertia();

        uint32_t m_id;
        uint32_t m_bitmask = 1;

        real m_mass = 0;
        real m_inertia = 0;
        real m_invMass = 0;
        real m_invInertia = 0;

        Vector2 m_position;
        Vector2 m_velocity;
        real m_rotation = 0;
        real m_angularVelocity = 0;

        Vector2 m_lastPosition;
        real m_lastRotation = 0;

        Vector2 m_forces;
        real m_torques = 0;

        Shape *m_shape;
        BodyType m_type = BodyType::Static;

        bool m_sleep = false;
        real m_friction = 0.1f;
        real m_restitution = 0.0f;

        uint32_t m_sleepCountdown = 0;
    };
}
#endif
