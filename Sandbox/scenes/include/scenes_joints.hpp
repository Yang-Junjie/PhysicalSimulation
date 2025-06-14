#ifndef SCENE_JOINTS_HPP
#define SCENE_JOINTS_HPP
#include "scenes.hpp"
namespace ps
{
    class SceneJoints : public Scene
    {
    private:
        Polygon box;
        Edge edge;
        Polygon board;
        Polygon small_board;
        DistanceJointPrimitive djp;
        PointJointPrimitive pjp;

    public:
        SceneJoints() = default;
        SceneJoints(const Settings &settings) : Scene(settings) {}

        void setScene() override;
    };
}

#endif