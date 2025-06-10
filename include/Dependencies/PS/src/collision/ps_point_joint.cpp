#include "ps_point_joint.hpp"
namespace ps
{
    PointJoint::PointJoint()
    {
        m_type = JointType::Point;
    }

    PointJoint::PointJoint(const PointJointPrimitive &prim) : m_primitive(prim)
    {
        m_type = JointType::Point;
    }

    void PointJoint::set(const PointJointPrimitive &prim)
    {
        m_primitive = prim;
    }

    void PointJoint::prepare(const real &dt)
    {
        if (m_primitive.bodyA == nullptr)
            return;
        Body *bodyA = m_primitive.bodyA;

        real m_a = bodyA->mass();
        real im_a = bodyA->inverseMass();
        real ii_a = bodyA->inverseInertia();
        if (m_primitive.frequency > 0.0)
        {
            real nf = naturalFrequency(m_primitive.frequency);
            m_primitive.stiffness = springStiffness(m_a, nf);
            m_primitive.damping = springDampingCoefficient(m_a, nf, m_primitive.dampingRatio);
        }
        else
        {
            m_primitive.stiffness = 0.0;
            m_primitive.damping = 0.0;
        }
        m_primitive.gamma = constraintImpulseMixing(dt, m_primitive.stiffness, m_primitive.damping);
        real erp = errorReductionParameter(dt, m_primitive.stiffness, m_primitive.damping);

        Vector2 pa = bodyA->toWorldPoint(m_primitive.localPointA);
        Vector2 ra = pa - bodyA->position();
        Vector2 pb = m_primitive.targetPoint;

        m_primitive.bias = (pa - pb) * erp;
        Matrix2x2 k;
        k.e11() = im_a + ra.y * ra.y * ii_a;
        k.e12() = -ra.x * ra.y * ii_a;
        k.e21() = k.e12();
        k.e22() = im_a + ra.x * ra.x * ii_a;

        k.e11() += m_primitive.gamma;
        k.e22() += m_primitive.gamma;

        m_primitive.effectiveMass = k.invert();
        // warmstart
        // m_primitive.impulse *= dt / dt;

        bodyA->applyImpulse(m_primitive.accumulatedImpulse, ra);
    }

    void PointJoint::solveVelocity(const real &dt)
    {
        if (m_primitive.bodyA == nullptr)
            return;
        Vector2 ra = m_primitive.bodyA->toWorldPoint(m_primitive.localPointA) - m_primitive.bodyA->position();
        Vector2 va = m_primitive.bodyA->velocity() +
                     Vector2::crossProduct(m_primitive.bodyA->angularVelocity(), ra);
        Vector2 jvb = va;
        jvb += m_primitive.bias;
        jvb += m_primitive.accumulatedImpulse * m_primitive.gamma;
        jvb.negate();

        Vector2 J = m_primitive.effectiveMass.multiply(jvb);
        Vector2 oldImpulse = m_primitive.accumulatedImpulse;
        m_primitive.accumulatedImpulse += J;
        real maxImpulse = dt * m_primitive.maxForce;
        if (m_primitive.accumulatedImpulse.lengthSquare() > maxImpulse * maxImpulse)
        {
            m_primitive.accumulatedImpulse.normalize();
            m_primitive.accumulatedImpulse *= maxImpulse;
        }
        J = m_primitive.accumulatedImpulse - oldImpulse;

        m_primitive.bodyA->applyImpulse(J, ra);
    }

    void PointJoint::solvePosition(const real &dt)
    {
    }

    PointJointPrimitive &PointJoint::primitive()
    {
        return m_primitive;
    }
}