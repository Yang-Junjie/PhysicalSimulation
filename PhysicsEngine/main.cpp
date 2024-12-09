#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <thread>
#include <chrono>
#include "Window.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "ImGuiManager.h"
#include "InputHandler.h"
#include "math.h"

#include "body.h"
#include "type.h"
#include "world.h"
#include "collision.h"

Renderer renderer;
oeWorld world(&renderer);

bool lock120FPS = true;
bool intersect = false;
static int bodyid = 0; // ����һ���������������������ֵ

oeBody* selectedBody = nullptr;

//������
static void dome1() {
    int count = 1;
    Property prop_data;
    PolygonType polygon_data;
    CircleType data1;
    PolygonType data3;
    prop_data.stationary_ = true;
    polygon_data.vertices[2] = { 10.0f,-0.1f };
    polygon_data.vertices[3] = { 10.0f,0.1f };
    world.CreatPolygon(polygon_data, prop_data);
    world.FindBody(0)->MoveTo({ 0.0f,-0.22f });
    prop_data.stationary_ = false;
    for (int i = 10; i > 0; i--) {
        for (int j = 10 - i; j >= 0; j--) {

            world.CreatPolygon(data3, prop_data);
            world.FindBody(count)->Move({ (i) * 0.2f + j * 0.1f, (j) * 0.2f });
            count++;
        }
    }
}


static void dome2() {

    ForceGenerator forceGen;
    forceGen.GenGravityAcc({ 0.0f,-100.0f });
    int count = 4;
    Property prop_data;
    prop_data.inherent_static_friction_ = 0.3f;
    prop_data.inherent_dynamic_friction_ = 0.2f;
    prop_data.restitution_ = 0.01f;

    PolygonType polygon_data;
    prop_data.stationary_ = true;
    polygon_data.vertices[2] = { 10.0f,-0.1f };
    polygon_data.vertices[3] = { 10.0f,0.1f };
    world.CreatPolygon(polygon_data, prop_data);
    world.FindBody(0)->MoveTo({ 0.0f,-0.5f });

    polygon_data.vertices[2] = { 6.0f,-0.1f };
    polygon_data.vertices[3] = { 6.0f,0.1f };
    world.CreatPolygon(polygon_data, prop_data);
    world.FindBody(1)->MoveTo({ 0.0f,3.0f });

    polygon_data.vertices[2] = { 4.0f,-0.1f };
    polygon_data.vertices[3] = { 4.0f,0.1f };
    world.CreatPolygon(polygon_data, prop_data);
    world.FindBody(2)->MoveTo({ 3.0f,1.5f });
    world.FindBody(2)->Rotation(oeVec2::AngleToRadian(20));

    polygon_data.vertices[2] = { 4.0f,-0.1f };
    polygon_data.vertices[3] = { 4.0f,0.1f };
    world.CreatPolygon(polygon_data, prop_data);
    world.FindBody(3)->MoveTo({ -0.0f,0.5f });
    world.FindBody(3)->Rotation(oeVec2::AngleToRadian(-15));

    polygon_data.vertices[0] = { -0.05f,1.0f };
    polygon_data.vertices[1] = { -0.05f,-0.1f };
    polygon_data.vertices[2] = { 0.05f,-0.1f };
    polygon_data.vertices[3] = { 0.05f,1.0f };

    prop_data.stationary_ = false;
    for (int i = 0; i < 10; i++) {
        world.CreatPolygon(polygon_data, prop_data);
        world.FindBody(count)->MoveTo({ -2.0f + i * 0.5f ,3.41f });
        
        count++;
    }
    world.FindBody(4)->Rotation(oeVec2::AngleToRadian(-10));
        

}



static void dome3() {
    CircleType data1;
    Property prop_data;
    prop_data.inherent_static_friction_ = 0.00f;
    prop_data.inherent_dynamic_friction_ = 0.0f;
    prop_data.restitution_ = 1.0f;
    
   
    prop_data.stationary_ = true;
    world.CreatCircle(data1, prop_data);
    world.FindBody(0)->MoveTo({ 0.0f,-0.005f });
    
    PolygonType polygon_data;
    prop_data.stationary_ = false;
    polygon_data.vertces_count = 6;
    polygon_data.vertices[2] = { 5.0f,-1.0f };
    polygon_data.vertices[3] = { 10.0f,-0.1f };
    polygon_data.vertices[4] = { 10.0f,0.1f };
    polygon_data.vertices[5] = { 5.0f,1.0f };
    world.CreatPolygon(polygon_data, prop_data);
    world.FindBody(1)->MoveTo({ 0.0f,-0.0f });
}

static void ContorlAllBody() {
    for (auto& body : *(world.GetBodysList())) {
        body.Rotation(oeVec2::AngleToRadian(1));
    }
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
int main() {
    try {
        // Create a window
        Window window(1000, 800, "PhysicsEngine");

        // Load OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        // ���ûص�����
        glfwSetFramebufferSizeCallback(window.getWindow(), framebuffer_size_callback);
        glfwSetMouseButtonCallback(window.getWindow(), mouseButtonCallback);
        glfwSetCursorPosCallback(window.getWindow(), cursorPositionCallback);
        glfwSetScrollCallback(window.getWindow(), scrollCallback); // ע�������ֻص�����
        glfwSetKeyCallback(window.getWindow(), keyCallback);

        // Initialize ImGui
        ImGuiManager imguiManager(window.getWindow());

        // Compile and link shaders
        Shader shader("vertex_shader.glsl", "fragment_shader.glsl");

        dome2();

        auto lastFrameTime = std::chrono::high_resolution_clock::now(); // ��һ֡��ʱ��
        float startTime = static_cast<float>(glfwGetTime()); // ��¼��������ʱ��

        // ��ʼ��ѡ�е�����
        if (world.GetBodyNum()>0) {
            selectedBody = world.FindBody(0);
        }

        while (!window.shouldClose()) {
            // ���㵱ǰ֡��ʱ��
            auto currentFrameTime = std::chrono::high_resolution_clock::now();
            auto deltaTime = std::chrono::duration<float>(currentFrameTime - lastFrameTime).count();
            lastFrameTime = currentFrameTime;

            // Input handling
            imguiManager.handleInput();

            // Start the Dear ImGui frame
            imguiManager.newFrame();

            // ��ȡ���ڵĵ�ǰ�ߴ�
            int width, height;
            glfwGetFramebufferSize(window.getWindow(), &width, &height);

            // Rendering commands here
            renderer.setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            renderer.clear();

            shader.use();
            shader.scale(OE_ZOOM);

            // ����ͶӰ����
            shader.setupProjection(width, height);

            // ������ͼ����
            glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(translation.x, translation.y, 0.0f));
            shader.setMat4("view", view);

            // ����������
            float color[4] = { 1.0f, 0.0f, 0.0f, 0.3f };
            renderer.drawLine(oeVec2(0, -100), oeVec2(0, 100), color);
            renderer.drawLine(oeVec2(-100, 0), oeVec2(100, 0), color);

           // ContorlAllBody();

            world.RenderBody();

            // ImGui rendering
            {
                ImGui::Begin("console");
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::Text("num of Body : %d", world.GetBodyNum());

                
                static bool button_clicked = false;
                static bool checkbox_state = false;
                // ��ѡ��
                ImGui::Checkbox("drawAABB", &checkbox_state);
                if (checkbox_state) { 
                    world.RenderAABB();
                    
                }
                ImGui::Checkbox("Lock 120FPS", &lock120FPS);
                ImGui::InputInt("Find body value", &bodyid);
                if (bodyid + 1 <= world.GetBodyNum() && bodyid>=0) {
                    oeBody* body = world.FindBody(bodyid);
                    ImGui::Text("Body %d position:(%.3f,%.3f) mass:%.3f", bodyid, body->mass_center_.x, body->mass_center_.y, body->GetMass());
                    ImGui::Text("Shape:%d volume:%.3f density:%.3f", body->shape_, body->GetVolume(), body->GetDensity());
                    ImGui::Text("abbmax:(%.3f,%.3f) aabbmin:(%.3f,%.3f)", body->aabb_.max.x, body->aabb_.max.y, body->aabb_.min.x, body->aabb_.min.y);
                    ImGui::Text("velocity:(%.3f,%.3f)acc:(%.3f,%.3f)", body->GetVelocity().x, body->GetVelocity().y, body->GetAcceleration().x, body->GetAcceleration().y);

                }
                else {
                    ImGui::Text("Body %d is nonexistence", bodyid);
                }
                static int prevBodyid = -1; // ���ڼ�¼��һ�ε� bodyid5
                if (bodyid != prevBodyid) {
                    prevBodyid = bodyid;
                    if (bodyid >= 0 && bodyid < world.GetBodyNum()) {
                        selectedBody = world.FindBody(bodyid);
                    }
                    else {
                        selectedBody = nullptr;
                    }
                }
               
                ImGui::End();
            }


            imguiManager.render();

            // ���������120FPS��������ȷ��ÿ֡��������1/120���ʱ��
            if (lock120FPS) {
                const float targetFPS = 120.0f;
                const float targetFrameTime = 1.0f / targetFPS;

                // ����ʣ����Ҫ�ȴ���ʱ�䣨����Ϊ��λ��
                float remainingTime = targetFrameTime - deltaTime;
                if (remainingTime > 0.0f) {
                    std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(remainingTime * 1000000)));
                }
            }
            
            world.Interation(deltaTime,4);
            // Swap buffers and poll events
            window.update();
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}

// ���̻ص�����
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (selectedBody != nullptr) {
            float moveSpeed = 100; // �ƶ��ٶ�
            switch (key) {
            case GLFW_KEY_W:
                selectedBody->SetAcceleration(oeVec2(0, moveSpeed));
                break;
            case GLFW_KEY_S:
                selectedBody->SetAcceleration(oeVec2(0, -moveSpeed));
                break;
            case GLFW_KEY_A:
                selectedBody->SetAcceleration(oeVec2(-moveSpeed, 0));
                break;
            case GLFW_KEY_D:
                selectedBody->SetAcceleration(oeVec2(moveSpeed, 0));
                break;
            case GLFW_KEY_R:
                selectedBody->SetAngularVelocity(oeVec2::AngleToRadian(-90));
                break;
            case GLFW_KEY_Q:
                selectedBody->SetAngularVelocity(oeVec2::AngleToRadian(90));
                break;
            case GLFW_KEY_RIGHT:
                
                break;
            case GLFW_KEY_LEFT:
                
                break;
            }


        }
    }
}