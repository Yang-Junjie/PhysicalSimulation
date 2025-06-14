#ifndef PHYSICAL_SIMULATION_REVOLUTE_JOINT_HPP
#define PHYSICAL_SIMULATION_REVOLUTE_JOINT_HPP
#include "ps_joint.hpp"
namespace ps
{
    struct RevoluteJointPrimitive
    {
        Body *bodyA = nullptr;
        Body *bodyB = nullptr;
        Vector2 localPointA;
        Vector2 localPointB;
        real referenceAngle = 0.0f;
        real lowerAngle = Math::degreeToRadian(-30.0f);
        real upperAngle = Math::degreeToRadian(30.0f);

        Vector2 linearError;
        real angularError = 0.0f;

        real damping = 0.0f;
        real stiffness = 0.0f;
        real frequency = 8.0f;
        real maxForce = 5000.0f;
        real dampingRatio = 0.2f;
        real gamma = 0.0f;
        Vector2 bias;
        Matrix2x2 linearMass;
        Vector2 accumulatedImpulse;
        real angularMass = 0.0f;
        real accumulatedLowerAngularImpulse = 0.0f;
        real accumulatedUpperAngularImpulse = 0.0f;

        bool angularLimit = true;
    };
    class RevoluteJoint : public Joint
    {
    public:
        RevoluteJoint();
        RevoluteJoint(const RevoluteJointPrimitive &primitive);
        void set(const RevoluteJointPrimitive &primitive);
        void prepare(const real &dt) override;
        void solveVelocity(const real &dt) override;
        void solvePosition(const real &dt) override;
        RevoluteJointPrimitive &primitive();

    private:
        RevoluteJointPrimitive m_primitive;
    };
}
#endif // PHYSICAL_SIMULATION_REVOLUTE_JOINT_HPP