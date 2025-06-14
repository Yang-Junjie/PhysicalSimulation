#include "scenes_joints.hpp"
namespace ps
{

    void SceneJoints::setScene()
    {
        m_settings.system->world().setGravity({0.0f, 10.0f});
        m_settings.system->world().setEnableGravity(true);
        m_settings.system->world().setLinearVelocityDamping(0.0f);
        m_settings.system->world().setAirFrictionCoefficient(0.0f);
        m_settings.system->world().setAngularVelocityDamping(0.0f);

        edge.set(Vector2{0.0f, 0.0f}, Vector2{20000.0f, 0.0f});
        box.append({{0, 0}, {50, 0}, {50, 50}, {0, 50}});
        board.append({{0, 0}, {300, 0}, {300, 20}, {0, 20}});
        small_board.append({{0, 0}, {100, 0}, {100, 10}, {0, 10}});
        uint32_t mask = 1;

        Body *ground = m_settings.system->world().createBody();
        ground->setShape(&edge);
        ground->setType(Body::BodyType::Static);
        ground->position().set({10, 600});
        ground->setMass(Constant::Max);
        ground->setBitmask(mask);
        m_settings.system->tree().insert(ground);
        // 联合体
        {
            djp.minDistance = 100.0f;
            djp.maxDistance = 100.0f;

            Body *my_box1 = m_settings.system->world().createBody();
            my_box1->setShape(&box);
            my_box1->position().set({200.0f, 400.0f});
            my_box1->setMass(1);
            my_box1->setType(Body::BodyType::Dynamic);
            my_box1->setBitmask(mask);
            m_settings.system->tree().insert(my_box1);

            Body *my_box2 = m_settings.system->world().createBody();
            my_box2->setShape(&box);
            my_box2->position().set({300.0f, 400.0f});
            my_box2->setMass(1);
            my_box2->setType(Body::BodyType::Dynamic);
            my_box2->setBitmask(mask);
            m_settings.system->tree().insert(my_box2);

            Body *my_box3 = m_settings.system->world().createBody();
            my_box3->setShape(&box);
            my_box3->position().set({250.0f, 300.0f});
            my_box3->setMass(1);
            my_box3->setType(Body::BodyType::Dynamic);
            my_box3->setBitmask(mask);
            m_settings.system->tree().insert(my_box3);

            djp.bodyA = my_box1;
            djp.localPointA.set(0.0f, 0.0f);
            djp.bodyB = my_box2;
            djp.localPointB.set(0.0f, 0.0f);
            m_settings.system->world().createJoint(djp);

            djp.bodyA = my_box2;
            djp.localPointA.set(0.0f, 0.0f);
            djp.bodyB = my_box3;
            djp.localPointB.set(0.0f, 0.0f);
            m_settings.system->world().createJoint(djp);

            djp.bodyA = my_box3;
            djp.localPointA.set(0.0f, 0.0f);
            djp.bodyB = my_box1;
            djp.localPointB.set(0.0f, 0.0f);
            m_settings.system->world().createJoint(djp);
        }
        // 双摆
        {
            mask <<= 1;
            Body *board2 = m_settings.system->world().createBody();
            board2->setShape(&board);
            board2->position().set({600.0f, 0.0f});
            board2->setMass(1);
            board2->setType(Body::BodyType::Dynamic);
            board2->setBitmask(mask);
            m_settings.system->tree().insert(board2);

            mask <<= 1;
            Body *board1 = m_settings.system->world().createBody();
            board1->setShape(&board);
            board1->position().set({599.0f, 0.0f});
            board1->setMass(1);
            board1->setType(Body::BodyType::Dynamic);
            board1->setBitmask(mask);
            m_settings.system->tree().insert(board1);

            rjp.referenceAngle = Math::degreeToRadian(0.0f);

            

            pjp.targetPoint.set(720.0f, 0.0f);
            pjp.bodyA = board2;
            pjp.localPointA.set(120, 0);
            pjp.maxForce = 100000.0f;
            m_settings.system->world().createJoint(pjp);

            // djp.minDistance = 1.0f;
            // djp.maxDistance = 1.0f;

            // djp.bodyA = board2;
            // djp.localPointA.set(-120, 0);
            // djp.bodyB = board1;
            // djp.localPointB.set(-120, 0);
            rjp.bodyA = board1;
            rjp.localPointA.set(-120, 0);
            rjp.bodyB = board2;
            rjp.localPointB.set(-120, 0);
            rjp.angularLimit = false;
            

            m_settings.system->world().createJoint(rjp);
        }
    }
}
