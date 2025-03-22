#ifndef OEWINDOW_HPP
#define OEWINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <string>
#include <functional>
#include <iostream>
class OEWindow {
    public:
        OEWindow(int width, int height, const std::string& title);
        ~OEWindow();
    
        bool init();
        void run();
        void mainWindow(std::function<void()> code);
    
    
        void setKeyCallback(GLFWkeyfun callback);
        void setMouseButtonCallback(GLFWmousebuttonfun callback);
        void setScrollCallback(GLFWscrollfun callback);
        void glfwSetFramebufferSizeCallback(GLFWwindow* window, int width, int height);

       
        GLFWwindow* getGLFWWindow();
        void getSize(int& width, int& height) const;
        bool shouldClose() const;
    
    private:
        int width_;
        int height_;
        std::string title_;
        GLFWwindow* window_;
        std::function<void()> sourceCode_;

        bool initGLFW();
        bool initImGui();
};

#endif