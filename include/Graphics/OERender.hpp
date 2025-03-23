#ifndef OERENDER_HPP
#define OERENDER_HPP
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>


class BatchRenderer
{
private:
    GLuint VAO, VBO, IBO;
    std::vector<float> vertexBuffer;       // 顶点数据缓冲区
    std::vector<unsigned int> indexBuffer; // 索引数据缓冲区
    size_t maxVertices, maxIndices;
    size_t currentVertex = 0; // 当前顶点偏移量

    // 每个顶点的属性结构：pos(3) + color(4)= 7 floats
    static const int VERTEX_SIZE = 7;

public:
    BatchRenderer() = delete;
    BatchRenderer(size_t maxVertices, size_t maxIndices);
    void setClearColor(float r, float g, float b, float a);
    void clear();


    void beginBatch();

    void addTriangle(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2,
                     const glm::vec4 &c0, const glm::vec4 &c1, const glm::vec4 &c2);

    void addRect(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec4 &c0, const glm::vec4 &c1, const glm::vec4 &c2,const glm::vec4 &c3);
    void addCircle(const glm::vec3 &center, float radius, const glm::vec4 &color, int segments);
    void endBatch();

    void flush();
};
class Renderer : public BatchRenderer
{

    void addRect(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec4 &c0, const glm::vec4 &c1, const glm::vec4 &c2);
};

#endif