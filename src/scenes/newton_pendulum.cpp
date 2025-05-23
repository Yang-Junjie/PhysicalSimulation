#include "scenes/newton_pendulum.hpp"
namespace ps
{
    void SceneNewTonPendulum::setScene()
    {
        m_settings.system.world().setEnableGravity(true);
        m_settings.system.world().setGravity({0.0f, 10.0f});
        m_settings.system.world().setLinearVelocityDamping(0.0f);
        m_settings.system.world().setAirFrictionCoefficient(0.0f);
        m_settings.system.world().setAngularVelocityDamping(0.0f);
        m_settings.system.world().clearAllBodies();
        m_settings.system.world().setEnableDamping(true);
        m_settings.system.world().enableSleep() = true;
        m_settings.system.positionIteration() = 4;
        m_settings.system.velocityIteration() = 6;

        edge.set(Vector2{10.0f, 100.0f}, Vector2{1070.0f, 100.0f});
        circle.setRadius(30.0f);

        real startX = 350.0f;
        
        Body *ball = m_settings.system.world().createBody();
        ball->setShape(&circle);
        ball->setMass(1.0f);
        ball->setType(Body::BodyType::Dynamic);
        ball->position().set(startX, 400.0f);
        ball->setRestitution(1.0f);
        m_settings.system.tree().insert(ball);

        Body *ground = m_settings.system.world().createBody();
        ground->setShape(&edge);
        ground->position().set({0.0f, 0.0f});
        ground->setMass(Constant::Max);
        ground->setType(Body::BodyType::Static);
        m_settings.system.tree().insert(ground);

        DistanceJointPrimitive djp;
        djp.minDistance = 300.0f;
        djp.maxDistance = 300.0f;
        djp.bodyB = ground;
        djp.localPointB.set(startX, 100.0f);
        djp.bodyA = ball;
        djp.localPointA.set(0, 0);
        m_settings.system.world().createJoint(djp);

        for (real i = 0; i < 5.0f; i++)
        {
            startX += 60.0f;
            ball = m_settings.system.world().createBody();
            ball->setShape(&circle);
            ball->setMass(1.0f);
            ball->setType(Body::BodyType::Dynamic);
            ball->setFriction(0.1f);
            ball->setRestitution(1.0f);
            ball->position().set(startX, 400.0f);
            djp.localPointB.set(startX, 100.0f);
            djp.bodyA = ball;
            m_settings.system.world().createJoint(djp);
            m_settings.system.tree().insert(ball);
        }

        startX += 60.00f;
        ball = m_settings.system.world().createBody();
        ball->setShape(&circle);
        ball->setMass(1.0f);
        ball->setType(Body::BodyType::Dynamic);
        ball->position().set(startX + 50.0f, 105.0f);
        ball->setRestitution(1.0f);
        m_settings.system.tree().insert(ball);
        djp.localPointB.set(startX, 100.0f);
        djp.bodyA = ball;
        m_settings.system.world().createJoint(djp);
        
    }
}
