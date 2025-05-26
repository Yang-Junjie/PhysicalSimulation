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
        void setScene() override;
    };
}
#endif