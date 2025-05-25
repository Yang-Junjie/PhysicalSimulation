#include "scenes/simple.hpp"
namespace ps
{
    void SceneSimple::setScene()
    {
        // 设置系统中的世界属性
        m_settings.system.world().setEnableGravity(true);
        m_settings.system.world().setGravity({0.0f, 10.0f});

        edge.set(Vector2{10.0f, 580.0f}, Vector2{1070.0f, 580.0f});
        box.append({{0, 0}, {20, 0}, {20, 20}, {0, 20}});

        Body *ground = m_settings.system.world().createBody();
        ground->setShape(&edge);
        ground->setMass(Constant::Max);
        ground->setType(Body::BodyType::Static);
        m_settings.system.tree().insert(ground);

        Body *my_box = m_settings.system.world().createBody();
        my_box->setShape(&box);
        my_box->position().set({400.0f, 400.0f});
        my_box->setMass(1);
        my_box->setType(Body::BodyType::Dynamic);
        m_settings.system.tree().insert(my_box);
    }

}