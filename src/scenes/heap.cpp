#include "scenes/heap.hpp"
namespace ps
{
   

    void SceneHeap::setBody()
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
        Vector2 pos[15];
        pos[0].set({300.0f, 240.0f});
        pos[1].set({320.0f, 240.0f});
        pos[2].set({340.0f, 240.0f});
        pos[3].set({360.0f, 240.0f});
        pos[4].set({380.0f, 240.0f});
        pos[5].set({400.0f, 240.0f});
        pos[6].set({420.0f, 240.0f});
        pos[7].set({440.0f, 240.0f});
        pos[8].set({460.0f, 240.0f});
        pos[9].set({480.0f, 240.0f});
        pos[10].set({500.0f,240.0f});
        pos[11].set({520.0f,240.0f});
        pos[12].set({540.0f,240.0f});
        pos[13].set({560.0f,240.0f});
        pos[14].set({580.0f,240.0f});

        for (real j = 0; j < 15; j += 1.0f)
        {
            for (real i = 0; i < 15; i += 1.0f)
            {
                Body *polygonBody = m_settings.system.world().createBody();
                polygonBody->setShape(&polygon);
                polygonBody->setFriction(1.0f);
                polygonBody->position().set(pos[int(i)] + Vector2(0, j * 20));
                polygonBody->setBitmask(mask);
                polygonBody->setRestitution(0);
                polygonBody->setMass(1);
                polygonBody->setType(Body::BodyType::Dynamic);
                m_settings.system.tree().insert(polygonBody);
            }
        }
        for (real i = 0; i < 1.0f; i += 1.0f)
        {
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
}