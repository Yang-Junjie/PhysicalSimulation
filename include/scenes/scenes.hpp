#ifndef SCENES_HPP
#define SCENES_HPP
#include "render.hpp"
#include "ps.hpp"
#include "camera.hpp"
namespace ps
{
    struct Settings
    {
        PhysicsSystem system;
        Camera camera;
    };
    class Scene
    {
    protected:
        Settings m_settings;

    public:
        Scene() = default;
        virtual ~Scene() = default;
        Camera &getCamera();
        PhysicsSystem &getSystem();
        virtual void setScene() = 0;
    };
}
#endif