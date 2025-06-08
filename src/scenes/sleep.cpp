#include "scenes/sleep.hpp"
namespace ps
{

    void SceneSleep::setScene()
    {
        m_settings.system->world().setEnableGravity(true);
        m_settings.system->world().setGravity({0.0f, 10.0f});
        m_settings.system->world().setLinearVelocityDamping(0.0f);
        m_settings.system->world().setAirFrictionCoefficient(0.0f);
        m_settings.system->world().setAngularVelocityDamping(0.0f);
        m_settings.system->world().enableSleep() = true;

        polygon.append({{0, 0}, {30, 0}, {30, 30}, {0, 30}});
        edge.set(Vector2{0.0f, 0.0f}, Vector2{1060.0f, 0.0f});

        uint32_t mask = 0x01;

        for (real i = 0; i < 10.0f; i += 1.0f)
        {
            for (real j = 0; j < i; j += 1.0f)
            {
                Body *box = m_settings.system->world().createBody();
                box->setShape(&polygon);
                box->setType(Body::BodyType::Dynamic);
                box->position().set({300.0f + i * 40.0f, j * 40.0f});
                box->setMass(1);
                box->setFriction(1.0f);
                box->setRestitution(0);
                box->setBitmask(mask);
                m_settings.system->tree().insert(box);
            }
        }

        Body *ground = m_settings.system->world().createBody();
        ground->setShape(&edge);
        ground->setType(Body::BodyType::Static);
        ground->position().set({10, 580});
        ground->setMass(Constant::Max);
        ground->setFriction(1.0f);
        ground->setRestitution(0);
        ground->setBitmask(mask);
        m_settings.system->tree().insert(ground);

        mask = mask << 1;
    }
}