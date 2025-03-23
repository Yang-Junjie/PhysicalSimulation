#include "OEWindow.hpp"
#include "OEShader.hpp"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "OERender.hpp"
#include <cmath>

OEWindow::OEWindow(int width, int height, const std::string &title)
    : width_(width), height_(height), title_(title), window_(nullptr) {}

OEWindow::~OEWindow()
{
    if (window_)
    {
        glfwDestroyWindow(window_);
    }
    glfwTerminate();
}

bool OEWindow::init()
{
    if (!initGLFW())
        return false;
    if (!initImGui())
        return false;
    return true;
}

bool OEWindow::shouldClose() const
{
    return glfwWindowShouldClose(window_);
}

void OEWindow::run()
{
    glfwSwapInterval(1);
    OEShader globalShader = OEShader("../shader/vertex_shader.glsl", "../shader/fragment_shader.glsl");
    BatchRenderer renderer(65536, 65536);

    {
        while (!glfwWindowShouldClose(window_))
        {

            //===================================================
            //==============处理MVP变换激活着色器==================
            //===================================================
            // 获取窗口的当前尺寸
            int width, height;
            glfwGetFramebufferSize(window_, &width, &height);
            globalShader.use(); // 激活着色器
            globalShader.scale(0.1);
            // 设置视口
            glViewport(0, 0, width, height);
            // 设置投影矩阵
            globalShader.setupProjection(width, height);
            // 创建视图矩阵（含缩放和平移）
            static glm::vec2 translation(0.0f);
            glm::mat4 view = glm::translate(glm::mat4(1.0f),
                                            glm::vec3(-translation.x, -translation.y, 0.0f));
            view = glm::scale(view, glm::vec3(2.0f));
            globalShader.setMat4("view", view);
            //=======================end========================

            
            
            //===================================================
            //=====================绘制IMGUI=====================
            //===================================================
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            double the_scan1 = 200 / static_cast<double>(height_);                      
            int OEWindowHeight = 0;                                                    
            glfwGetWindowSize(window_, nullptr, &OEWindowHeight);
            const int ImGuiWindowWidth = the_scan1 * OEWindowHeight;

            ImGui::SetNextWindowPos(ImVec2(5, 5));
            ImGui::SetNextWindowSize(ImVec2(ImGuiWindowWidth, OEWindowHeight - 10));
            ImGui::Begin("Hello, world!", nullptr, ImGuiWindowFlags_NoResize);
            ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate); // 格式化为1位小数;
            ImGui::Text("test.");
            ImGui::SliderFloat2("Position", &translation.x, -5.0f, 5.0f);
            ImGui::End();
            
            //=======================end========================
            



            //==================================================
            //=====================渲染图形======================
            //==================================================
            renderer.beginBatch();
            sourceCode_();
            
            renderer.addRect(glm::vec3(-0.5, 0.5, 0), glm::vec3(0.5, 0.5, 0), glm::vec3(0.5, -0.5, 0), glm::vec3(-0.5, -0.5, 0), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), glm::vec4(0, 0, 1, 1), glm::vec4(1, 1, 0, 1));
            renderer.addTriangle(glm::vec3(-0.5+1, 0.5+1, 0), glm::vec3(0.5+1, 0.5+1, 0), glm::vec3(0.5+1, -0.5+1, 0),glm::vec4(1, 1, 1, 1),glm::vec4(1, 1, 1, 1),glm::vec4(1, 1, 1, 1));
            renderer.addCircle(glm::vec3(-0.5-1, 0.5-1, 0),1.0,glm::vec4(1, 0, 1, 1),32);
            renderer.setClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            renderer.clear();
            renderer.endBatch();
            renderer.flush();
            ImGui::Render();


            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            //=======================end========================


            //========================
            //========处理事件=========
            //========================
            glfwSwapBuffers(window_);
            glfwPollEvents();
        }
    }

    // 清理 ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void OEWindow::setKeyCallback(GLFWkeyfun callback)
{
    glfwSetKeyCallback(window_, callback);
}

void OEWindow::setMouseButtonCallback(GLFWmousebuttonfun callback)
{
    glfwSetMouseButtonCallback(window_, callback);
}

void OEWindow::setScrollCallback(GLFWscrollfun callback)
{
    glfwSetScrollCallback(window_, callback);
}

void OEWindow::mainWindow(std::function<void()> sourceCode)
{
    sourceCode_ = sourceCode;
}

GLFWwindow *OEWindow::getGLFWWindow()
{
    return window_;
}

void OEWindow::getSize(int &width, int &height) const
{
    width = this->width_;
    height = this->height_;
}

bool OEWindow::initGLFW()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    // 设置OpenGL版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    window_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
    if (!window_)
    {
        std::cerr << "Failed to create GLFW window: " << std::endl;
        glfwTerminate();
        return false;
    }

    // 设置当前上下文
    glfwMakeContextCurrent(window_);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}

bool OEWindow::initImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // 绑定到当前窗口的上下文和OpenGL版本
    if (!ImGui_ImplGlfw_InitForOpenGL(window_, true))
    {
        std::cerr << "Failed to initialize ImGui GLFW binding" << std::endl;
        return false;
    }
    if (!ImGui_ImplOpenGL3_Init("#version 130"))
    {
        std::cerr << "Failed to initialize ImGui OpenGL binding" << std::endl;
        return false;
    }
    return true;
}