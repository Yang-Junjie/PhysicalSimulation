#ifndef SCENES_CATAPULT_HPP
#define SCENES_CATAPULT_HPP
#include "scenes/scenes.hpp"
namespace ps
{
    class SceneCatapult : public Scene
    {
    private:
        Edge edge;
        Polygon polygon;
        Polygon polygon1;
        Circle circle;
        PointJointPrimitive pjp;
    public:
        void setScene() override;
    };
}
#endif // SCENES_CATAPULT_HPP