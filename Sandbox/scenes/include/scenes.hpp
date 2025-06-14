#ifndef SCENES_HPP
#define SCENES_HPP
#include "renderer.hpp"
#include "ps.hpp"
#include "camera.hpp"
namespace ps
{
    struct Settings
    {
        PhysicsSystem *system = nullptr;
        Camera *camera = nullptr;
    };
    class Scene
    {
    protected:
        Settings m_settings;
        Body *m_currentBody = nullptr;

    public:
        Scene() = default;
        Scene(const Settings &settings);
        virtual ~Scene() = default;
        Camera *getCamera();
        PhysicsSystem *getSystem();
        virtual void setScene() = 0;
        void setCurrentBody(Body *body) { m_currentBody = body; }
        Body *currentBody() const { return m_currentBody; }
    };
}
#endif