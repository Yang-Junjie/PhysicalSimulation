﻿#include "application.hpp"
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
            { return new SceneCatapult(settings); },
            [&](const Settings &settings)
            { return new SceneJoints(settings); }};
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
        const char *ttf_path = "./Resources/msyh.ttc";
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
        m_mousePos = pos;
        m_screenMousePos = pos;
        if (m_cameraViewportMove)
        {
            Vector2 delta = pos - m_lastMousePos;

            Vector2 worldDelta = m_camera.screenToWorld(pos) - m_camera.screenToWorld(m_lastMousePos);
            m_camera.setTransform(m_cameraStartOffset - worldDelta);
        }
        m_mousePos = m_camera.screenToWorld(pos);

        auto prim = m_mouseJoint->primitive();
        prim.targetPoint = m_mousePos;

        m_mouseJoint->set(prim);
    }
    void Application::mousePressed(const SDL_Event &event)
    {
        Vector2 pos(event.motion.x, event.motion.y);
        m_screenMousePos = pos;
        m_mousePos = m_camera.screenToWorld(pos);

        if (event.button.button == SDL_BUTTON_RIGHT)
        {
            m_cameraViewportMove = true;
            m_lastMousePos = pos;
            m_cameraStartOffset = m_camera.transform();
        }

        if (event.button.button == SDL_BUTTON_LEFT && m_mouseJoint != nullptr)
        {
            // 查询鼠标与哪个物体相交
            AABB mouseBox;
            mouseBox.position = m_mousePos;
            mouseBox.width = 0.01f;
            mouseBox.height = 0.01f;
            auto bodies = m_system.tree().query(mouseBox);
            // auto bodies = m_system.grid().query(mouseBox);

            for (auto &body : bodies)
            {
                Vector2 point = m_mousePos - body->position();
                point = Matrix2x2(-body->rotation()).multiply(point);
                if (body->shape()->contains(point) && m_selectedBody == nullptr && body->type() != Body::BodyType::Static)
                {
                    m_selectedBody = body;

                    PointJointPrimitive prim;
                    prim.localPointA = body->toLocalPoint(m_mousePos);
                    prim.bodyA = body;
                    prim.targetPoint = m_mousePos;
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

        Vector2 pos(event.motion.x, event.motion.y);
        m_mousePos = m_camera.screenToWorld(pos);
        m_screenMousePos = pos;

        if (m_mouseJoint == nullptr)
            return;
        m_mouseJoint->primitive().clear();
        m_mouseJoint->setActive(false);

        m_cameraViewportMove = false;

        m_selectedBody = nullptr;
        m_scene->setCurrentBody(nullptr);
    }
    void Application::mouseWheel(const SDL_Event &event)
    {

        Vector2 mouseScreenPos = m_screenMousePos;
        Vector2 beforeWorldPos = m_camera.screenToWorld(mouseScreenPos);
        float scale = (event.wheel.y > 0) ? 1.1f : 1.0f / 1.1f;
        m_camera.setTargetMeterToPixel(m_camera.meterToPixel() * scale);
        Vector2 afterWorldPos = m_camera.screenToWorld(mouseScreenPos);
        Vector2 offset = beforeWorldPos - afterWorldPos;
        m_camera.setTransform(m_camera.transform() + offset);
    }




    void Application::renderGUI()
    {
        real window_size = 200.0f;
        {
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(window_size, 0), ImGuiCond_Once);
            ImGui::Begin("物理仿真信息");
            const char *pauseText = !m_running ? "开启" : "暂停";
            if (ImGui::Button(pauseText, ImVec2(-FLT_MIN, 0.0f)))
                pause();
            if (ImGui::Button("重启", ImVec2(-FLT_MIN, 0.0f)))
                restart();

            static float fps_history[100] = {0};
            static float fps_1percent_history[100] = {0};
            static int fps_offset = 0;
            float current_fps = ImGui::GetIO().Framerate;
            fps_history[fps_offset] = current_fps;

            // 计算1% low帧
            std::vector<float> fps_sorted(fps_history, fps_history + IM_ARRAYSIZE(fps_history));
            std::sort(fps_sorted.begin(), fps_sorted.end());
            int count_1percent = std::max(1, int(fps_sorted.size() * 0.01f));
            float sum_1percent = 0.0f;
            for (int i = 0; i < count_1percent; ++i)
                sum_1percent += fps_sorted[i];
            float fps_1percent_low = sum_1percent / count_1percent;

            // 保存1% low帧率历史
            fps_1percent_history[fps_offset] = fps_1percent_low;

            fps_offset = (fps_offset + 1) % IM_ARRAYSIZE(fps_history);

            ImGui::Text("当前帧率: %.1f FPS", current_fps);
            ImGui::Text("1%% Low: %.1f FPS", fps_1percent_low);

            ImGui::PlotLines("帧率", fps_history, IM_ARRAYSIZE(fps_history), fps_offset, nullptr, current_fps - current_fps + 100.0f, current_fps + 100.0f, ImVec2(0, 30));
            ImGui::PlotLines("1% Low", fps_1percent_history, IM_ARRAYSIZE(fps_1percent_history), fps_offset, nullptr, fps_1percent_low - 100.0f, fps_1percent_low + 100.0f, ImVec2(0, 30));

            ImGui::Text("鼠标位置: (%.1f, %.1f)", m_mousePos.x, m_mousePos.y);
            ImGui::Text("鼠标屏幕位置: (%.1f, %.1f)", m_screenMousePos.x, m_screenMousePos.y);
            ImGui::Text("摄像机位置: (%.1f, %.1f)", m_camera.transform().x, m_camera.transform().y);

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
            ImGui::End();
        }

        {
            ImGui::SetNextWindowPos(ImVec2(window_size * 1, 0), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(window_size, 0), ImGuiCond_Once);
            ImGui::Begin("选择场景");
            std::vector<std::string> select_m_scene = {
                "heap", "sleep", "newton_pendulum", "simple", "point_joint", "Bitmask", "Catapult", " Joints"};
            std::vector<const char *> cstrs;
            for (const auto &s : select_m_scene)
                cstrs.push_back(s.c_str());
            ;
            if (ImGui::Combo(" ", &m_current_scene_id, cstrs.data(), cstrs.size()))
            {
                setupScene();
            }

            ImGui::End();
        }
        {
            ImGui::SetNextWindowPos(ImVec2(ImGui::GetMainViewport()->Size.x - window_size, 0), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(window_size, 600), ImGuiCond_Once);
            ImGui::SetNextWindowCollapsed(true, ImGuiCond_Once);
            ImGui::Begin("设置", nullptr, ImGuiWindowFlags_NoMove);

            ImGui::SetNextItemOpen(false, ImGuiCond_Once);
            if (ImGui::CollapsingHeader("可视化选项"))
            {
                ImGui::BeginChild("可视化选项", ImVec2(0, 130), true);
                ImGui::Checkbox("显示刚体", &m_scene->getCamera()->bodyVisible());
                ImGui::Checkbox("显示关节", &m_scene->getCamera()->jointVisible());
                ImGui::Checkbox("显示AABB", &m_scene->getCamera()->aabbVisible());
                ImGui::Checkbox("显示速度", &m_scene->getCamera()->velocityVisible());
                ImGui::EndChild();
            }
            if (ImGui::CollapsingHeader("世界设置"))
            {
                ImGui::BeginChild("世界设置", ImVec2(0, 130), true);
                ImGui::Checkbox("开启重力", &m_system.world().enableGravity());
                Vector2 gravity = m_system.world().gravity();
                ImGui::SetNextItemWidth(100);
                if (ImGui::DragFloat("重力X", &gravity.x, 0.1f, -10.0f, 10.0f, "%.2f"))
                {
                    m_system.world().setGravity(gravity);
                }
                ImGui::SetNextItemWidth(100);
                if (ImGui::DragFloat("重力Y", &gravity.y, 0.1f, -10.0f, 10.0f, "%.2f"))
                {
                    m_system.world().setGravity(gravity);
                }

                ImGui::Checkbox("开启睡眠", &m_system.world().enableSleep());
                ImGui::EndChild();
            }
            if (ImGui::CollapsingHeader("系统设置"))
            {
                ImGui::BeginChild("系统设置", ImVec2(0, 300), true);
                ImGui::Checkbox("开启CCD", &m_system.enableCCD());
                ImGui::Separator();
                ImGui::Text("迭代次数");
                ImGui::SetNextItemWidth(100);
                ImGui::SliderInt("位置迭代次数", &m_system.positionIteration(), 1, 50);
                ImGui::SetNextItemWidth(100);
                ImGui::SliderInt("速度迭代次数", &m_system.velocityIteration(), 1, 50);
                ImGui::Separator();
                ImGui::Text("求解选项");
                ImGui::Checkbox("切片DeltaTime", &m_system.sliceDeltaTime());
                ImGui::Checkbox("求解关节速度", &m_system.solveJointVelocity());
                ImGui::Checkbox("求解关节位置", &m_system.solveJointPosition());
                ImGui::Checkbox("求解接触速度", &m_system.solveContactVelocity());
                ImGui::Checkbox("求解接触位置", &m_system.solveContactPosition());

                ImGui::Separator();
                ImGui::EndChild();
            }
            if (ImGui::CollapsingHeader("接触设置"))
            {
                ImGui::BeginChild("接触设置", ImVec2(0, 300), true);
                ImGui::InputFloat("bias", &m_system.maintainer().m_biasFactor);
                ImGui::Checkbox("warm", &m_system.maintainer().m_warmStart);
                ImGui::Separator();
                ImGui::EndChild();
            }
            ImGui::End();
        }
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
                else if (event.type == SDL_EVENT_MOUSE_WHEEL)
                {
                    mouseWheel(event);
                }
            }
            ImGui_ImplSDL3_NewFrame();
            ImGui_ImplSDLRenderer3_NewFrame();
            ImGui::NewFrame();

            renderGUI();
            
            simulate();
            m_scene->getCamera()->render(window, renderer);

            ImGui::Render();
            ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

            SDL_RenderPresent(renderer);
        }
    }
    void Application::pause()
    {
        m_running = !m_running;
    }

    void Application::restart()
    {
        setupScene();
    }

    void Application::step()
    {
        const real dt = 1.0f / static_cast<real>(m_frequency);
        m_system.step(dt);
    }
    
    void Application::simulate()
    {
        if (m_running)
            step();
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