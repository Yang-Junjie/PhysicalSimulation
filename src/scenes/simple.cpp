#include "scenes/simple.hpp"
namespace ps
{
    void SceneSimple::setScene()
    {
        m_settings.system.world().setEnableGravity(true);
        m_settings.system.world().setGravity({0.0f, 10.0f});

        edge.set(Vector2{0.0f, 0.0f}, Vector2{1060.0f, 0.0f});
        box.append({{0, 0}, {50, 0}, {50, 50}, {0, 50}});

        Body *ground = m_settings.system.world().createBody();
        ground->setShape(&edge);
        ground->position().set({10.0f, 580.0f});
        ground->setMass(Constant::Max);
        ground->setType(Body::BodyType::Static);
        m_settings.system.tree().insert(ground);

        Body *my_box = m_settings.system.world().createBody();
        my_box->setShape(&box);
        my_box->position().set({540.0f, 400.0f});
        my_box->setMass(1);
        my_box->setType(Body::BodyType::Dynamic);
        m_settings.system.tree().insert(my_box);
    }

}