#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include "renderer.hpp"
#include "ps.hpp"
#include <SDL3/SDL.h>
#include "scenes.hpp"
#include "heap.hpp"
#include "sleep.hpp"
#include "newton_pendulum.hpp"
#include "simple.hpp"
#include "point_joint.hpp"
#include "scenes_joints.hpp"
#include "bitmask.hpp"
#include "catapult.hpp"
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
        bool m_running = true;
        Scene *m_scene;

        PhysicsSystem m_system;
        Camera m_camera;
        Settings m_settings;
        real m_frequency = 60.0f;

        bool m_mouse_down = false;
        bool m_cameraViewportMove = false;

        Vector2 m_screenMousePos;
        Vector2 m_lastMousePos;
        Vector2 m_cameraStartOffset;

        Body *m_selectedBody = nullptr;
        PointJoint *m_mouseJoint = nullptr;
        PointJointPrimitive m_pointJointPrimitive;
        Vector2 m_mousePos;
        real m_zoomFactor = 0.5f;

        std::array<std::function<Scene *(const Settings &settings)>, 8> m_scenesList;

    public:
        Application();
        ~Application();
        bool init();
        void setupScene();
        void renderGUI();

        void run();
        void pause();
        void restart();
        void simulate();
        void step();

        void cleanup();
        void clearALL();

        void mouseMove(const SDL_Event &event);
        void mousePressed(const SDL_Event &event);
        void mouseRelease(const SDL_Event &event);
        void mouseWheel(const SDL_Event &event);
    };
}
#endif // APPLICATION_HPP