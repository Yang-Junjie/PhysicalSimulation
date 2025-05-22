#include "scenes/sleep.hpp"
namespace ps
{

    void SceneSleep::setBody()
    {
        m_settings.system.world().setEnableGravity(true);
        m_settings.system.world().setGravity({0.0f, 10.0f});
        m_settings.system.world().setLinearVelocityDamping(0.0f);
        m_settings.system.world().setAirFrictionCoefficient(0.0f);
        m_settings.system.world().setAngularVelocityDamping(0.0f);
        m_settings.system.world().setEnableDamping(true);
        m_settings.system.world().enableSleep() = true;
        m_settings.system.positionIteration() = 4;
        m_settings.system.velocityIteration() = 6;
        polygon.append({{0, 0}, {20, 0}, {20, 20}, {0, 20}});
        edge.set(Vector2{10.0f, 580.0f}, Vector2{1070.0f, 580.0f});
        uint32_t mask = 0x01;
        for (real i = 0; i < 10.0f; i += 1.0f)
        {
            for (real j = 0; j < i; j += 1.0f)
            {
                Body *polygonBody = m_settings.system.world().createBody();
                polygonBody->setShape(&polygon);
                polygonBody->setFriction(1.0f);
                polygonBody->position().set({400.0f + i * 30.0f, 10 + j * 30.0f});
                polygonBody->setBitmask(mask);
                polygonBody->setRestitution(0);
                polygonBody->setMass(1);
                polygonBody->setType(Body::BodyType::Dynamic);
                m_settings.system.tree().insert(polygonBody);
            }
        }
        Body *ground = m_settings.system.world().createBody();
        ground->setShape(&edge);
        ground->position().set({0, 0});
        ground->setFriction(1.0f);
        ground->setBitmask(mask);
        ground->setRestitution(0);
        ground->setMass(Constant::Max);
        ground->setType(Body::BodyType::Static);
        mask = mask << 1;
        m_settings.system.tree().insert(ground);
    }
}