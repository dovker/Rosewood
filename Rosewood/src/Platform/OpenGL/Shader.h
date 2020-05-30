#pragma once
#include <rwpch.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

namespace Rosewood
{
    class Shader
    {
    public:
        // the program ID
        unsigned int ID;

        Shader();
        // constructor reads and builds the shader
        Shader(const std::string& filepath);
        // use/activate the shader
        void use();
        // utility uniform functions
        unsigned int CompileShader(unsigned int type, const std::string& source);
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setMat4(const std::string& name, const glm::mat4& mat) const;
        void setMat3(const std::string& name, const glm::mat3& mat) const;
        void setMat2(const std::string& name, const glm::mat2& mat) const;
        void setVec4(const std::string& name, float x, float y, float z, float w) const;
        void setVec4(const std::string& name, const glm::vec4& value) const;
        void setVec3(const std::string& name, float x, float y, float z) const;
        void setVec3(const std::string& name, const glm::vec3& value) const;
        void setVec2(const std::string& name, float x, float y) const;
        void setVec2(const std::string& name, const glm::vec2& value) const;

    };
}