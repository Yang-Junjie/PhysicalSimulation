#ifndef SCENES_BITMASK_HPP
#define SCENES_BITMASK_HPP
#include "scenes/scenes.hpp"

namespace ps
{
    class SceneBitmask : public Scene
    {
    private:
        Edge edge;
        Polygon polygon;

    public:
        SceneBitmask() = default;
        SceneBitmask(const Settings &settings) : Scene(settings) {}
        void setScene() override;
    };
}
#endif // SCENES_BITMASK_HPP