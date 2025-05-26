#ifndef SCENES_JOINT_HPP
#define SCENES_JOINT_HPP
#include "scenes/scenes.hpp"
namespace ps
{
    class SceneNewTonPendulum : public Scene
    {
    private:
        Circle circle;
        Edge edge;
    public:
        void setScene() override;
    };
}
#endif