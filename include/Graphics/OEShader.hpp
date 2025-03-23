#ifndef OESHADER_HPP
#define OESHADER_HPP
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
class OEShader
{
public:
    unsigned int ID;
    OEShader(const char *vertexPath, const char *fragmentPath);

    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void scale(float coeff)const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setupProjection(int width, int height) const;

private:
    void checkCompileErrors(unsigned int shader, std::string type);
};
#endif