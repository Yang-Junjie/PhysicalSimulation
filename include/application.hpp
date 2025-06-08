#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include "render.hpp"
#include "ps.hpp"
#include <SDL3/SDL.h>
#include "scenes/scenes.hpp"
#include "scenes/heap.hpp"
#include "scenes/sleep.hpp"
#include "scenes/newton_pendulum.hpp"
#include "scenes/simple.hpp"
#include "scenes/point_joint.hpp"
#include "scenes/bitmask.hpp"
#include "scenes/catapult.hpp"
#include "camera.hpp"
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"
namespace ps
{

    class Application
    {
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        int m_current_scene_id = 0;
        Scene *m_scene;

        PhysicsSystem m_system;
        Camera m_camera;
        Settings m_settings;

        bool mouse_down = false;
        Body *m_selectedBody = nullptr;
        PointJoint *m_mouseJoint = nullptr;
        PointJointPrimitive m_pointJointPrimitive;
        Vector2 m_MousePos;

        std::array<std::function<Scene*(const Settings& settings)>, 7> m_scenesList;

    public:
        Application();
        ~Application();
        bool init();
        void setupScene();
        void renderGUI();
        void run();
        void cleanup();
        void clearALL();
        void mouseMove(const SDL_Event &event);
        void mousePressed(const SDL_Event &event);
        void mouseRelease(const SDL_Event &event);
    };
}
#endif // APPLICATION_HPP