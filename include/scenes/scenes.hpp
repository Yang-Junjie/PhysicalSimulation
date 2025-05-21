#ifndef SCENES_HPP
#define SCENES_HPP
#include "render.hpp"
#include "ps.hpp"
#include "camera.hpp"
namespace ps
{
    struct Settings
    {
        // Physics
        PhysicsWorld world ;
        ContactMaintainer maintainer ;
        Tree tree ;
        UniformGrid grid ;
        PhysicsSystem system ;

        // Render
        Camera camera ;
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
        virtual void setBody() = 0;
    };
}
#endif