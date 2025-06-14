﻿#ifndef SCENES_CATAPULT_HPP
#define SCENES_CATAPULT_HPP
#include "scenes.hpp"
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
        SceneCatapult() = default;
        SceneCatapult(const Settings &settings) : Scene(settings) {}
        void setScene() override;
    };
}
#endif // SCENES_CATAPULT_HPP