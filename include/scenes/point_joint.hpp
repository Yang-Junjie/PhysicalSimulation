#ifndef SCENES_POINT_JOINT_HPP
#define SCENES_POINT_JOINT_HPP
#include "scenes/scenes.hpp"
namespace ps
{
    class ScenePointJoint : public Scene
    {
    private:
        Edge edge;
        Polygon box;
        PointJointPrimitive pjp;
    public:
        void setScene() override;
    };
}
#endif