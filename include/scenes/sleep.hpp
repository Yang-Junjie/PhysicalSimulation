#ifndef SCENES_SLEEP_HPP
#define SCENES_SLEEP_HPP
#include "scenes/scenes.hpp"
namespace ps
{
    class SceneSleep : public Scene
    {
    private:
        Edge edge;
        Polygon polygon;

    public:
        void setScene() override;
    };
}
#endif