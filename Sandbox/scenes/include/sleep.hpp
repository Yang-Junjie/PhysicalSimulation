#ifndef SCENES_SLEEP_HPP
#define SCENES_SLEEP_HPP
#include "scenes.hpp"
namespace ps
{
    class SceneSleep : public Scene
    {
    private:
        Edge edge;
        Polygon polygon;

    public:
        SceneSleep() = default;
        SceneSleep(const Settings &settings) : Scene(settings) {}
        void setScene() override;
    };
}
#endif