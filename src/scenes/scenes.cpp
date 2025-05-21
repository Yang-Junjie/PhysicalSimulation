#include "scenes/scenes.hpp"

namespace ps
{
    Camera &Scene::getCamera()
    {
        return m_settings.camera;
    }

    PhysicsSystem &Scene::getSystem()
    {
        return m_settings.system;
    }

}