#include "ps_distance_joint.hpp"
namespace ps
{

    DistanceJoint::DistanceJoint()
    {
        m_type = JointType::Distance;
    }
    DistanceJoint::DistanceJoint(const DistanceJointPrimitive &primitive) : m_primitive(primitive)
    {
        m_type = JointType::Distance;
    }
    void DistanceJoint::set(const DistanceJointPrimitive &primitive)
    {
        m_primitive = primitive;
    }
    void DistanceJoint::prepare(const real &dt)
    {
        assert(m_primitive.minDistance <= m_primitive.maxDistance);

        if (m_primitive.bodyA == nullptr || m_primitive.bodyB == nullptr)
            return;

        Body *bodyA = m_primitive.bodyA;
        Body *bodyB = m_primitive.bodyB;

        real m_a = bodyA->mass();
        real m_b = bodyB->mass();
        real im_a = bodyA->inverseMass();
        real im_b = bodyB->inverseMass();
        real ii_a = bodyA->inverseInertia();
        real ii_b = bodyB->inverseInertia();

        Vector2 pa = bodyA->toWorldPoint(m_primitive.localPointA);
        Vector2 ra = pa - bodyA->position();

        Vector2 pb = bodyB->toWorldPoint(m_primitive.localPointB);
        Vector2 rb = pb - bodyB->position();

        Vector2 n = (pa - pb).normal();

        real k = im_a + im_b + (ii_a * ra.cross(n) * ra.cross(n)) + (ii_b * rb.cross(n) * rb.cross(n));
        m_primitive.normal = n;
        m_primitive.effectiveMass = k > 0.0f ? 1.0f / k : 0.0f;

        m_primitive.bias = pa - pb;
        m_primitive.currentLength = (pa - pb).length();

        Vector2 P = m_primitive.accumulatedImpulse * n;
        bodyA->applyImpulse(P, ra);
        bodyB->applyImpulse(-P, rb);
    }
    void DistanceJoint::solveVelocity(const real &dt)
    {
        if (m_primitive.bodyA == nullptr || m_primitive.bodyB == nullptr)
            return;

        Body *bodyA = m_primitive.bodyA;
        Body *bodyB = m_primitive.bodyB;

        if (m_primitive.minDistance < m_primitive.maxDistance)
        {
        }

        if (m_primitive.minDistance == m_primitive.maxDistance)
        {
            // equal
            Vector2 ra = bodyA->toWorldPoint(m_primitive.localPointA) - bodyA->position();
            Vector2 va = bodyA->velocity() + Vector2::crossProduct(bodyA->angularVelocity(), ra);

            Vector2 rb = bodyB->toWorldPoint(m_primitive.localPointB) - bodyB->position();
            Vector2 vb = bodyB->velocity() + Vector2::crossProduct(bodyB->angularVelocity(), rb);

            real jv = m_primitive.normal.dot(va - vb);
            real lambda = -m_primitive.effectiveMass * (jv);
            m_primitive.accumulatedImpulse += lambda;

            Vector2 P = lambda * m_primitive.normal;
            bodyA->applyImpulse(P, ra);
            bodyB->applyImpulse(-P, rb);
        }
    }
    void DistanceJoint::solvePosition(const real &dt)
    {
        if (m_primitive.bodyA == nullptr || m_primitive.bodyB == nullptr)
            return;

        Body *bodyA = m_primitive.bodyA;
        Body *bodyB = m_primitive.bodyB;

        Vector2 pa = bodyA->toWorldPoint(m_primitive.localPointA);
        Vector2 ra = pa - bodyA->position();

        Vector2 pb = bodyB->toWorldPoint(m_primitive.localPointB);
        Vector2 rb = pb - bodyB->position();

        Vector2 error = pa - pb;
        real errorLength = error.length();
        real c = 0.0f;

        if (m_primitive.minDistance == m_primitive.maxDistance)
            c = error.length() - m_primitive.minDistance;

        real lambda = -m_primitive.effectiveMass * c;
        Vector2 P = lambda * error.normal();

        bodyA->position() += bodyA->inverseMass() * P;
        bodyA->rotation() += bodyA->inverseInertia() * ra.cross(P);

        bodyB->position() -= bodyB->inverseMass() * P;
        bodyB->rotation() -= bodyB->inverseInertia() * rb.cross(P);
    }

    DistanceJointPrimitive& DistanceJoint::primitive()
    {
        return m_primitive;
    }
}