#include "Renderer.h"
#include <vector>
#include <cmath>

void Renderer::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void Renderer::clear() {
    glEnable(GL_BLEND); // ���û��
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // ���û�Ϻ���
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawArrays(GLenum mode, GLint first, GLsizei count) {
    glDrawArrays(mode, first, count);
}

void Renderer::drawRectangle(float x, float y, float width, float height, const float* color) {
    float vertices[] = {
        x,     y,      0.0f, // Bottom-left corner
        x + width, y,  0.0f, // Bottom-right corner
        x + width, y + height, 0.0f, // Top-right corner
        x,     y + height, 0.0f  // Top-left corner
    };

    float colors[] = {
        color[0], color[1], color[2], color[3],
        color[0], color[1], color[2], color[3],
        color[0], color[1], color[2], color[3],
        color[0], color[1], color[2], color[3]
    };

    unsigned int indices[] = {
        0, 1, 2,  // First triangle
        2, 3, 0   // Second triangle
    };

    // Create and bind VAO
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create and bind VBO for vertices
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set up vertex attribute pointers for positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Create and bind VBO for colors
    unsigned int cbo;
    glGenBuffers(1, &cbo);
    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // Set up vertex attribute pointers for colors
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // Create and bind EBO
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Draw the rectangle
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Clean up
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &cbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

void Renderer::drawCircle(float centerX, float centerY, float radius, const float* color, int segments) {
    float angleStep = static_cast<float>(2.0f * M_PI / segments);
    std::vector<float> vertices;
    std::vector<float> colors;

    // Center vertex
    vertices.push_back(centerX);
    vertices.push_back(centerY);
    vertices.push_back(0.0f);

    // Center color
    colors.push_back(color[0]);
    colors.push_back(color[1]);
    colors.push_back(color[2]);
    colors.push_back(color[2]);

    for (int i = 0; i <= segments; ++i) {
        float angle = i * angleStep;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f);

        colors.push_back(color[0]);
        colors.push_back(color[1]);
        colors.push_back(color[2]);
        colors.push_back(color[3]);
    }

    // Create and bind VAO
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create and bind VBO for vertices
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Set up vertex attribute pointers for positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Create and bind VBO for colors
    unsigned int cbo;
    glGenBuffers(1, &cbo);
    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STATIC_DRAW);

    // Set up vertex attribute pointers for colors
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // Draw the circle using Triangle Fan
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 3);

    // Clean up
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &cbo);
    glDeleteVertexArrays(1, &vao);
}
void Renderer::drawCircle(oeVec2 center, float radius, const float* color, int segments)
{
    Renderer::drawCircle(center.x, center.y, radius, color, segments);
}
void Renderer::drawLine(float startX, float startY, float endX, float endY, const float* color) {
    float vertices[] = {
        startX, startY, 0.0f,
        endX,   endY,   0.0f
    };

    float colors[] = {
        color[0], color[1], color[2], color[3],
        color[0], color[1], color[2], color[3]
    };

    // Create and bind VAO
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create and bind VBO for vertices
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set up vertex attribute pointers for positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Create and bind VBO for colors
    unsigned int cbo;
    glGenBuffers(1, &cbo);
    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // Set up vertex attribute pointers for colors
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // Draw the line
    glDrawArrays(GL_LINES, 0, 2);

    // Clean up
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &cbo);
    glDeleteVertexArrays(1, &vao);
}

void Renderer::drawLine(oeVec2 start, oeVec2 end, const float* color)
{
    float vertices[] = {
        start.x, start.y, 0.0f,
        end.x,   end.y,   0.0f
    };

    float colors[] = {
        color[0], color[1], color[2], color[3],
        color[0], color[1], color[2], color[3]
    };

    // Create and bind VAO
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create and bind VBO for vertices
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set up vertex attribute pointers for positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Create and bind VBO for colors
    unsigned int cbo;
    glGenBuffers(1, &cbo);
    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // Set up vertex attribute pointers for colors
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // Draw the line
    glDrawArrays(GL_LINES, 0, 2);

    // Clean up
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &cbo);
    glDeleteVertexArrays(1, &vao);
}

