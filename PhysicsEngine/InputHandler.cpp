#include "InputHandler.h"

// ����ȫ�ֱ���
bool rightMousePressed = false;
float lastX = 0.0f, lastY = 0.0f;
glm::vec2 translation = glm::vec2(0.0f, 0.0f);
float OE_ZOOM = 1.0f; // ��������

// ʵ����갴ť�ص�����
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        rightMousePressed = true;
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        lastX = static_cast<float>(x);
        lastY = static_cast<float>(y);
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        rightMousePressed = false;
    }
}

// ʵ�����λ�ûص�����
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    if (rightMousePressed) {
        float x = static_cast<float>(xpos);
        float y = static_cast<float>(ypos);
        float dx = x - lastX;
        float dy = lastY - y; // ע�� y �᷽���෴
        translation.x += dx * 0.0025f;
        translation.y += dy * 0.0025f;
        lastX = x;
        lastY = y;
    }
}

// ʵ���ӿڴ�С�ı�Ļص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// ʵ�������ֻص�����
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    OE_ZOOM += yoffset * 0.03f; // ������������
    if (OE_ZOOM < 0.03f) {
        OE_ZOOM = 0.03f; // ��ֹ�������ӹ�С
    }
}