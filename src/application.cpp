#include "application.hpp"
namespace ps
{

    Application::Application()
        : window(nullptr), renderer(nullptr), m_scene(nullptr)
    {
        m_scenesList = {
            [&](const Settings &settings)
            { return new SceneHeap(settings); },
            [&](const Settings &settings)
            { return new SceneSleep(settings); },
            [&](const Settings &settings)
            { return new SceneNewTonPendulum(settings); },
            [&](const Settings &settings)
            { return new SceneSimple(settings); },
            [&](const Settings &settings)
            { return new ScenePointJoint(settings); },
            [&](const Settings &settings)
            { return new SceneBitmask(settings); },
            [&](const Settings &settings)
            { return new SceneCatapult(settings); }};
        m_settings.system = &m_system;
        m_settings.camera = &m_camera;
        m_pointJointPrimitive.bodyA = nullptr;
        m_mouseJoint = m_system.world().createJoint(m_pointJointPrimitive);
        m_mouseJoint->setActive(false);
        setupScene();
    }

    Application::~Application()
    {
        cleanup();
    }

    bool Application::init()
    {
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
            return false;
        }

        if (!SDL_CreateWindowAndRenderer("PhysicalSimulation", 1080, 680, 0, &window, &renderer))
        {
            SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
            SDL_Quit();
            return false;
        }
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        ImGui::StyleColorsDark();
        ImGuiStyle &style = ImGui::GetStyle();
        style.Colors[ImGuiCol_WindowBg].w = 0.3f;
        const char *ttf_path = "./res/msyh.ttc";
        if (!io.Fonts->AddFontFromFileTTF(ttf_path, 14.0f, NULL, io.Fonts->GetGlyphRangesChineseFull()))
        {
            SDL_Log("Failed to load font:");
            SDL_Log(ttf_path);
        }
        ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
        ImGui_ImplSDLRenderer3_Init(renderer);
        return true;
    }

    void Application::setupScene()
    {
        // static SceneBitmask bitmask(m_settings);
        // // static SceneCatapult catapult(m_settings);
        // m_scene = &bitmask;
        // m_scene->setScene();
        // m_scene->getCamera()->setWorld(&m_system.world());
        clearALL();
        Settings settings;
        settings.camera = &m_camera;
        settings.system = &m_system;

        m_scene = m_scenesList[m_current_scene_id](settings);
        if (m_scene != nullptr)
        {
            m_scene->setScene();
            m_scene->getCamera()->setWorld(&m_system.world());
        }
    }

    void Application::mouseMove(const SDL_Event &event)
    {
        Vector2 pos(event.motion.x, event.motion.y);
        m_MousePos = pos;

        auto prim = m_mouseJoint->primitive();
        prim.targetPoint = m_MousePos;

        m_mouseJoint->set(prim);
    }
    void Application::mousePressed(const SDL_Event &event)
    {
        Vector2 pos(event.motion.x, event.motion.y);
        m_MousePos = pos;
        if (event.button.button == SDL_BUTTON_LEFT && m_mouseJoint != nullptr)
        {
            // 查询鼠标与哪个物体相交
            AABB mouseBox;
            mouseBox.position = m_MousePos;
            mouseBox.width = 0.01f;
            mouseBox.height = 0.01f;
            auto bodies = m_system.tree().query(mouseBox);
            // auto bodies = m_system.grid().query(mouseBox);

            for (auto &body : bodies)
            {
                Vector2 point = m_MousePos - body->position();
                point = Matrix2x2(-body->rotation()).multiply(point);
                if (body->shape()->contains(point) && m_selectedBody == nullptr && body->type() != Body::BodyType::Static)
                {
                    m_selectedBody = body;

                    PointJointPrimitive prim;
                    prim.localPointA = body->toLocalPoint(m_MousePos);
                    prim.bodyA = body;
                    prim.targetPoint = m_MousePos;
                    prim.maxForce = 1000 * body->mass();
                    m_mouseJoint->set(prim);
                    m_mouseJoint->prepare(static_cast<real>(1 / 60.0f));

                    m_mouseJoint->setActive(true);
                    m_selectedBody->setSleep(false);
                    m_scene->setCurrentBody(m_selectedBody);
                    break;
                }
            }
        }
    }
    void Application::mouseRelease(const SDL_Event &event)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            Vector2 pos(event.motion.x, event.motion.y);
            m_MousePos = m_camera.screenToWorld(pos);
            m_MousePos = pos;

            if (m_mouseJoint == nullptr)
                return;
            m_mouseJoint->primitive().clear();
            m_mouseJoint->setActive(false);

            m_selectedBody = nullptr;
            m_scene->setCurrentBody(nullptr);
        }
    }
    void Application::renderGUI()
    {
        ImGui::Begin("物理仿真信息");
        ImGui::Text("鼠标位置: (%.1f, %.1f)", m_MousePos.x, m_MousePos.y);

        ImGui::Separator();
        ImGui::Text("选中物体的属性");
        ImGui::BeginChild("BodyProperties", ImVec2(0, 130), true);
        if (m_selectedBody)
        {
            ImGui::Text("ID: %.d", m_selectedBody->id());
            ImGui::Text("质量: %.1f", m_selectedBody->mass());
            ImGui::Text("位置: (%.1f, %.1f)", m_selectedBody->position().x, m_selectedBody->position().y);
            ImGui::Text("速度: (%.1f, %.1f)", m_selectedBody->velocity().x, m_selectedBody->velocity().y);
            ImGui::Text("动能: %.1f", m_selectedBody->kineticEnergy());
            ImGui::Text("转动惯量: %.1f", m_selectedBody->inertia());
        }
        else
        {
            ImGui::Text("未选中任何刚体");
        }
        ImGui::EndChild();

        ImGui::Separator();

        std::vector<std::string> select_m_scene = {
            "heap", "sleep", "newton_pendulum", "simple", "point_joint", "Bitmask", "Catapult"};
        std::vector<const char *> cstrs;
        for (const auto &s : select_m_scene)
            cstrs.push_back(s.c_str());

        if (ImGui::Combo("选择场景", &m_current_scene_id, cstrs.data(), cstrs.size()))
        {
            setupScene();
        }

        ImGui::End();
    }
    void Application::run()
    {
        SDL_Event event;
        bool keep_going = true;
        while (keep_going)
        {
            while (SDL_PollEvent(&event))
            {
                ImGui_ImplSDL3_ProcessEvent(&event);
                if (event.type == SDL_EVENT_QUIT)
                {
                    keep_going = false;
                }
                else if (event.type == SDL_EVENT_MOUSE_MOTION)
                {
                    mouseMove(event);
                }
                else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
                {
                    mousePressed(event);
                }
                else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
                {
                    mouseRelease(event);
                }
            }
            ImGui_ImplSDL3_NewFrame();
            ImGui_ImplSDLRenderer3_NewFrame();
            ImGui::NewFrame();

            renderGUI();
            const real dt = 1.0f / 60.0f;
            m_scene->getSystem()->step(dt);
            m_scene->getCamera()->render(window, renderer);

            ImGui::Render();
            ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

            SDL_RenderPresent(renderer);
            SDL_Delay(0.5f);
        }
    }

    void Application::cleanup()
    {

        if (renderer)
            SDL_DestroyRenderer(renderer);
        if (window)
            SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Application::clearALL()
    {
        m_system.world().clearAllBodies();
        m_system.world().clearAllJoints();
        m_system.maintainer().clearAll();
        m_system.tree().clearAll();
        m_system.grid().clearAll();
        m_pointJointPrimitive.bodyA = nullptr;
        m_mouseJoint = m_system.world().createJoint(m_pointJointPrimitive);
        m_mouseJoint->setActive(false);
        if (m_scene != nullptr)
        {
            delete m_scene;
            m_scene = nullptr;
        }
    }
}