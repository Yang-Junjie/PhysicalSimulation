#include "scenes/point_joint.hpp"
namespace ps
{
    void ScenePointJoint::setScene()
    {
        m_settings.system.world().setGravity({0.0f, 10.0f});
        m_settings.system.world().setEnableGravity(true);

        box.append({{0, 0}, {50, 0}, {50, 50}, {0, 50}});

        Body *block = m_settings.system.world().createBody();
        block->setShape(&box);
        block->setType(Body::BodyType::Dynamic);
        block->setMass(8.0f);
        block->position().set(100.0f, 400.0f);
        block->rotation() = Math::degreeToRadian(60);
        block->setBitmask(0x01);
        m_settings.system.tree().insert(block);

        pjp.targetPoint.set(100.0f, 400.0f);
        pjp.bodyA = block;
        pjp.localPointA.set(0, 0);
        m_settings.system.world().createJoint(pjp);

        pjp.targetPoint.set(1000.0f, 100.0f);
        pjp.bodyA = block;
        pjp.localPointA.set(0, 0);
        m_settings.system.world().createJoint(pjp);

        pjp.targetPoint.set(1000.0f, 600.0f);
        pjp.bodyA = block;
        pjp.localPointA.set(0, 0);
        m_settings.system.world().createJoint(pjp);
    }
}