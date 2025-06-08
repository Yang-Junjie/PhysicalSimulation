#ifndef SCENES_HEAP_HPP
#define SCENES_HEAP_HPP
#include "scenes/scenes.hpp"
namespace ps
{
    class SceneHeap : public Scene
    {
    private:
        Edge edge;
        Polygon polygon;

    public:
        SceneHeap() = default;
        SceneHeap(const Settings &settings) : Scene(settings) {}
        void setScene() override;
    };
}
#endif