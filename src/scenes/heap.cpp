#include "scenes/heap.hpp"
namespace ps
{
    void SceneHeap::setScene()
    {
        m_settings.system->world().setGravity({0.0f, 0.0f});
        m_settings.system->world().setEnableGravity(true);
        m_settings.system->world().setLinearVelocityDamping(0.0f);
        m_settings.system->world().setAirFrictionCoefficient(0.0f);
        m_settings.system->world().setAngularVelocityDamping(0.0f);
        m_settings.system->world().enableSleep() = true;

        polygon.append({{0, 0}, {20, 0}, {20, 20}, {0, 20}});
        edge.set(Vector2{0.0f, 0.0f}, Vector2{1060.0f, 0.0f});

        uint32_t mask = 0x01;

        for (real j = 0; j < 15.0f; j += 1.0f)
        {
            for (real i = 0; i < 15.0f; i += 1.0f)
            {
                Body *polygonBody = m_settings.system->world().createBody();
                polygonBody->setShape(&polygon);
                polygonBody->setType(Body::BodyType::Dynamic);
                polygonBody->position().set(Vector2(300.0f + i * 20.1f, 200.5f) + Vector2(0, j * 20.1f));
                polygonBody->setMass(1);
                polygonBody->setBitmask(mask);
                m_settings.system->tree().insert(polygonBody);
            }
        }

        Body *ground = m_settings.system->world().createBody();
        ground->setShape(&edge);
        ground->setType(Body::BodyType::Static);
        ground->setMass(Constant::Max);
        ground->position().set({10.0f, 580.0f});
        ground->setBitmask(mask);
        m_settings.system->tree().insert(ground);

        mask = mask << 1;
    }
}