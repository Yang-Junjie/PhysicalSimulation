#include "scenes/catapult.hpp"
namespace ps
{
    void SceneCatapult::setScene()
    {
        m_settings.system.world().setGravity({0.0f, 10.0f});
        m_settings.system.world().setEnableGravity(true);
        m_settings.system.world().setLinearVelocityDamping(0.0f);
        m_settings.system.world().setAirFrictionCoefficient(0.0f);
        m_settings.system.world().setAngularVelocityDamping(0.0f);

        edge.set(Vector2{0.0f, 0.0f}, Vector2{1060.0f, 0.0f});
        polygon.append({{0, 0}, {400, 0}, {400, 20}, {0, 20}});
        polygon1.append({{0, 0}, {30, 0}, {30, 30}, {0, 30}});
        circle.setRadius(15.0f);

        Body *ground = m_settings.system.world().createBody();
        ground->setShape(&edge);
        ground->setType(Body::BodyType::Static);
        ground->setMass(Constant::Max);
        ground->position().set({10, 600});
        m_settings.system.tree().insert(ground);

        Body *board = m_settings.system.world().createBody();
        board->setShape(&polygon);
        board->setType(Body::BodyType::Dynamic);
        board->position().set({500.0f, 530.0f});
        board->setMass(1);
        board->setFriction(0.8);
        m_settings.system.tree().insert(board);

        pjp.targetPoint.set(500.0f, 550.0f);
        pjp.bodyA = board;
        pjp.localPointA.set(0, 0);
        m_settings.system.world().createJoint(pjp);

        for (real i = 0; i < 4.0f; i += 1.0f)
        {
            Body *box = m_settings.system.world().createBody();
            box->setShape(&polygon1);
            box->setType(Body::BodyType::Dynamic);
            box->position().set({350.0f + i * 30.0f, 500.0f});
            box->setMass(1);
            box->setFriction(0.8);
            m_settings.system.tree().insert(box);
        }

        Body *circleBody = m_settings.system.world().createBody();
        circleBody->setShape(&circle);
        circleBody->setType(Body::BodyType::Dynamic);
        circleBody->position().set({600.0f, 300.0f});
        circleBody->setMass(10.0f);
        circleBody->setFriction(0.8);
        m_settings.system.tree().insert(circleBody);
    }
}