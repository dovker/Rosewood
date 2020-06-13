#pragma once
#include <rwpch.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Rosewood
{
    class OpenGLShader
    {
    public:
        OpenGLShader();
        OpenGLShader(const std::string& filepath);
        virtual ~OpenGLShader();
        
        virtual void Bind();
        virtual void Unbind();
        
        virtual void setBool(const std::string& name, bool value);
        virtual void setInt(const std::string& name, int value);
        virtual void setIntPtr(const std::string& name, int count, int* value);
        virtual void setFloat(const std::string& name, float value);
        virtual void setMat4(const std::string& name, const glm::mat4& mat);
        virtual void setMat3(const std::string& name, const glm::mat3& mat);
        virtual void setMat2(const std::string& name, const glm::mat2& mat);
        virtual void setVec4(const std::string& name, const glm::vec4& value);
        virtual void setVec3(const std::string& name, const glm::vec3& value);
        virtual void setVec2(const std::string& name, const glm::vec2& value);
    private:
        uint32_t m_ID;
        uint32_t CompileShader(unsigned int type, const std::string& source);
    };
}
