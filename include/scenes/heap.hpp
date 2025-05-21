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
        ~SceneHeap() override = default;
        void setBody() override;
    };
}
#endif