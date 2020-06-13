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
        Shader();
        Shader(const std::string& filepath);
        virtual ~Shader();
        
        virtual void Bind();
        virtual void Unbind();
        
        virtual void setBool(const std::string& name, bool value)               = 0;
        virtual void setInt(const std::string& name, int value)                 = 0;
        virtual void setIntPtr(const std::string& name, int count, int* value)  = 0;
        virtual void setFloat(const std::string& name, float value)             = 0;
        virtual void setMat4(const std::string& name, const glm::mat4& mat)     = 0;
        virtual void setMat3(const std::string& name, const glm::mat3& mat)     = 0;
        virtual void setMat2(const std::string& name, const glm::mat2& mat)     = 0;
        virtual void setVec4(const std::string& name, const glm::vec4& value)   = 0;
        virtual void setVec3(const std::string& name, const glm::vec3& value)   = 0;
        virtual void setVec2(const std::string& name, const glm::vec2& value)   = 0;
    };
}
