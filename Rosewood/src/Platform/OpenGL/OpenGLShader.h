#pragma once
#include <rwpch.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Rosewood/Graphics/API/Shader.h"

namespace Rosewood
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& filepath);
        virtual ~OpenGLShader() {}
        
        virtual void Bind() override;
        virtual void Unbind() override;
        
        virtual void setBool(const std::string& name, bool value) override;
        virtual void setInt(const std::string& name, int value) override;
        virtual void setIntPtr(const std::string& name, int count, int* value) override;
        virtual void setFloat(const std::string& name, float value) override;
        virtual void setMat4(const std::string& name, const glm::mat4& mat) override;
        virtual void setMat3(const std::string& name, const glm::mat3& mat) override;
        virtual void setMat2(const std::string& name, const glm::mat2& mat) override;
        virtual void setVec4(const std::string& name, const glm::vec4& value) override;
        virtual void setVec3(const std::string& name, const glm::vec3& value) override;
        virtual void setVec2(const std::string& name, const glm::vec2& value) override;
        
        virtual void Recompile(const std::string& filepath) override;
        virtual void Recompile(const std::string& vs, const std::string& fs) override;

    private:
        uint32_t m_ID;
        uint32_t CompileShader(unsigned int type, const std::string& source);
    };
}
