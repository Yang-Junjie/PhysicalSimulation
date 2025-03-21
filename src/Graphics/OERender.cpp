#include "OERender.hpp"

BatchRenderer::BatchRenderer(size_t maxVertices, size_t maxIndices)
    : maxVertices(maxVertices), maxIndices(maxIndices)
{
    // 初始化OpenGL对象
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);

    // 配置VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, maxVertices * VERTEX_SIZE * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

    // 设置顶点属性指针
    // 位置属性（location=0）
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // 颜色属性（location=1）
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxIndices * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
}

void BatchRenderer::beginBatch()
{
    vertexBuffer.clear();
    indexBuffer.clear();
    currentVertex = 0;
}

void BatchRenderer::addTriangle(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2,
                                const glm::vec4 &c0, const glm::vec4 &c1, const glm::vec4 &c2)
{
    if (currentVertex + 3 > maxVertices || indexBuffer.size() + 3 > maxIndices)
    {
        endBatch();
        flush();
        beginBatch();
    }

    const glm::vec3 vertices[3] = {p0, p1, p2};
    const glm::vec4 colors[3] = {c0, c1, c2};

    for (int i = 0; i < 3; ++i)
    {
        vertexBuffer.push_back(vertices[i].x);
        vertexBuffer.push_back(vertices[i].y);
        vertexBuffer.push_back(vertices[i].z);
        vertexBuffer.push_back(colors[i].r);
        vertexBuffer.push_back(colors[i].g);
        vertexBuffer.push_back(colors[i].b);
        vertexBuffer.push_back(colors[i].a);
    }

    indexBuffer.push_back(currentVertex);
    indexBuffer.push_back(currentVertex + 1);
    indexBuffer.push_back(currentVertex + 2);

    currentVertex += 3;
}

void BatchRenderer::addRect(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec4 &c0, const glm::vec4 &c1, const glm::vec4 &c2,const glm::vec4 &c3)
{
    addTriangle(p0,p1,p2,c0,c1,c2);
    addTriangle(p2,p3,p0,c2,c3,c0);

}
void BatchRenderer::endBatch()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertexBuffer.size() * sizeof(float), vertexBuffer.data());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexBuffer.size() * sizeof(unsigned int), indexBuffer.data());
}

void BatchRenderer::flush()
{
    if (indexBuffer.empty())
        return;

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexBuffer.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


