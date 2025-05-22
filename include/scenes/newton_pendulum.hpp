#ifndef SCENES_JOINT_HPP
#define SCENES_JOINT_HPP
#include "scenes/scenes.hpp"
namespace ps
{
    class SceneNewTonPendulum : public Scene
    {
    private:
        Edge edge;
        Circle circle;
       // DistanceJointPrimitive distance_joint;
        Polygon polygon;

    public:
        SceneNewTonPendulum() = default;
        ~SceneNewTonPendulum() = default;
        void setBody() override;
    };
}
#endif