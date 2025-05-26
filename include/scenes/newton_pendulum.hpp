#ifndef SCENES_NEWTON_PENDULUM_HPP
#define SCENES_NEWTON_PENDULUM_HPP
#include "scenes/scenes.hpp"
namespace ps
{
    class SceneNewTonPendulum : public Scene
    {
    private:
        Circle circle;
        Edge edge;
        DistanceJointPrimitive djp;
    public:
        void setScene() override;
    };
}
#endif