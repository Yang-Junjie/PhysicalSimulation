#include "bitmask.hpp"
namespace ps
{
    void SceneBitmask::setScene()
    {
        m_settings.system->world().setEnableGravity(true);
        m_settings.system->world().setGravity({0.0f, 10.0f});
        m_settings.system->world().setLinearVelocityDamping(0.0f);
        m_settings.system->world().setAirFrictionCoefficient(0.0f);
        m_settings.system->world().setAngularVelocityDamping(0.0f);
        m_settings.system->world().enableSleep() = true;

        edge.set(Vector2{0.0f, 0.0f}, Vector2{1060.0f, 0.0f});
        polygon.append({{0, 0}, {50, 0}, {50, 50}, {0, 50}});

        uint32_t mask = 1;
        Body *ground1 = m_settings.system->world().createBody();
        ground1->setShape(&edge);
        ground1->setType(Body::BodyType::Static);
        ground1->setMass(Constant::Max);
        ground1->position().set({10.0f, 380.0f});
        ground1->setBitmask(mask);
        m_settings.system->tree().insert(ground1);

        Body *polygon1 = m_settings.system->world().createBody();
        polygon1->setShape(&polygon);
        polygon1->setType(Body::BodyType::Dynamic);
        polygon1->position().set({300.0f, 200.0f});
        polygon1->setMass(1);
        polygon1->setBitmask(mask);
        m_settings.system->tree().insert(polygon1);

        mask = mask << 1;
        Body *ground2 = m_settings.system->world().createBody();
        ground2->setShape(&edge);
        ground2->setType(Body::BodyType::Static);
        ground2->setMass(Constant::Max);
        ground2->position().set({10.0f, 480.0f});
        ground2->setBitmask(mask);
        m_settings.system->tree().insert(ground2);

        Body *polygon2 = m_settings.system->world().createBody();
        polygon2->setShape(&polygon);
        polygon2->setType(Body::BodyType::Dynamic);
        polygon2->position().set({400.0f, 200.0f});
        polygon2->setMass(1);
        polygon2->setBitmask(mask);
        m_settings.system->tree().insert(polygon2);

        mask = mask << 1;
        Body *ground3 = m_settings.system->world().createBody();
        ground3->setShape(&edge);
        ground3->setType(Body::BodyType::Static);
        ground3->setMass(Constant::Max);
        ground3->position().set({10.0f, 580.0f});
        ground3->setBitmask(mask);
        m_settings.system->tree().insert(ground3);

        Body *polygon3 = m_settings.system->world().createBody();
        polygon3->setShape(&polygon);
        polygon3->setType(Body::BodyType::Dynamic);
        polygon3->position().set({500.0f, 200.0f});
        polygon3->setMass(1);
        polygon3->setBitmask(mask);
        m_settings.system->tree().insert(polygon3);
    }
}
