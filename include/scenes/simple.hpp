﻿#ifndef SCENE_SIMPLE_HPP
#define SCENE_SIMPLE_HPP
#include "scenes/scenes.hpp"
namespace ps
{
    class SceneSimple : public Scene
    {
    private:
        Polygon box;
        Edge edge;

    public:
        void setScene() override;
    };
}

#endif