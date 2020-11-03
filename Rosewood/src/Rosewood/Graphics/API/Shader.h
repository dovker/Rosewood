#pragma once
#include <rwpch.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Rosewood
{
    class Shader
    {
    public:
        virtual ~Shader() = default;
        
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        
        virtual void Recompile(const std::string& filepath) = 0;
        virtual void Recompile(const std::string& vs, const std::string& fs) = 0;

        
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
        
        static Ref<Shader> Create(const std::string& filepath);
    };
}
