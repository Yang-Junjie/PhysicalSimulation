#include "newton_pendulum.hpp"
namespace ps
{
    void SceneNewTonPendulum::setScene()
    {
        m_settings.system->world().setGravity({0.0f, 10.0f});
        m_settings.system->world().setEnableGravity(true);
        m_settings.system->world().setLinearVelocityDamping(0.0f);
        m_settings.system->world().setAirFrictionCoefficient(0.0f);
        m_settings.system->world().setAngularVelocityDamping(0.0f);

        edge.set(Vector2{0.0f, 0.0f}, Vector2{1060.0f, 0.0f});
        circle.setRadius(30.0f);

        Body *ground = m_settings.system->world().createBody();
        ground->setShape(&edge);
        ground->setType(Body::BodyType::Static);
        ground->position().set({10, 100});
        ground->setMass(Constant::Max);
        m_settings.system->tree().insert(ground);

        real startX = 350.0f;

        djp.minDistance = 300.0f;
        djp.maxDistance = 300.0f;
        djp.bodyB = ground;

        Body *ball = m_settings.system->world().createBody();
        ball->setShape(&circle);
        ball->setMass(1.0f);
        ball->setType(Body::BodyType::Dynamic);
        ball->setRestitution(1.0f);
        ball->position().set(startX, 400.0f);
        m_settings.system->tree().insert(ball);
        djp.localPointB.set(startX-10.0f, 0.0f);
        djp.bodyA = ball;
        djp.localPointA.set(0, 0);
        m_settings.system->world().createJoint(djp);

        for (real i = 0; i < 5.0f; i++)
        {
            startX += 60.0f;
            ball = m_settings.system->world().createBody();
            ball->setShape(&circle);
            ball->setMass(1.0f);
            ball->setType(Body::BodyType::Dynamic);
            ball->setFriction(0.1f);
            ball->setRestitution(1.0f);
            ball->position().set(startX, 400.0f);
            m_settings.system->tree().insert(ball);
            djp.localPointB.set(startX-10.0f, 0.0f);
            djp.bodyA = ball;
            djp.localPointA.set(0, 0);
            m_settings.system->world().createJoint(djp);
        }

        startX += 60.0f;
        ball = m_settings.system->world().createBody();
        ball->setShape(&circle);
        ball->setMass(1.0f);
        ball->setType(Body::BodyType::Dynamic);
        ball->position().set(startX + 30.0f, 105.0f);
        ball->setRestitution(1.0f);
        m_settings.system->tree().insert(ball);
        djp.localPointB.set(startX-10.0f, 0.0f);
        djp.bodyA = ball;
        djp.localPointA.set(0, 0);
        m_settings.system->world().createJoint(djp);
    }
}
