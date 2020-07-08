#include "rwpch.h"
#include "OpenGLShader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

namespace Rosewood
{
	
	OpenGLShader::OpenGLShader(const std::string& path)
	{

		std::ifstream stream(path);
		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};
		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		try
		{
			while (getline(stream, line))
			{
				if (line.find("#shader") != std::string::npos)
				{
					if (line.find("vertex") != std::string::npos)
						type = ShaderType::VERTEX;
					else if (line.find("fragment") != std::string::npos)
						type = ShaderType::FRAGMENT;

				}
				else
				{
					ss[(int)type] << line << "\n";
				}
			}
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const std::string vertexShader = ss[0].str();
		const std::string fragmentShader = ss[1].str();
		//std::cout << vertexShader << std::endl;
		//std::cout << fragmentShader << std::endl;
		m_ID = glCreateProgram();
		uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(m_ID, vs);
		glAttachShader(m_ID, fs);
		glLinkProgram(m_ID);
		glValidateProgram(m_ID);

		glDeleteShader(vs);
		glDeleteShader(fs);

	}

	uint32_t OpenGLShader::CompileShader(unsigned int type, const std::string& source)
	{
		uint32_t id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;

		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " Shader" << std::endl;
			std::cout << message << std::endl;
			glDeleteShader(id);
			return 0;
		}
        std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "Shader compiled successfully" << std::endl;
		return id;
	}


	void OpenGLShader::Bind()
	{

		glUseProgram(m_ID);
	}
    void OpenGLShader::Unbind()
    {

        glUseProgram(0);
    }

	void OpenGLShader::setBool(const std::string& name, bool value)
	{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
	}
	void OpenGLShader::setInt(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
	}
	void OpenGLShader::setIntPtr(const std::string& name, int count, int* value)
	{
		glUniform1iv(glGetUniformLocation(m_ID, name.c_str()), count, value);
	}
	void OpenGLShader::setFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
    }
	void OpenGLShader::setVec2(const std::string& name, const glm::vec2& value)
	{
		glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
	}
	// ------------------------------------------------------------------------
	void OpenGLShader::setVec3(const std::string& name, const glm::vec3& value)
	{
		glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
	}
	void OpenGLShader::setVec4(const std::string& name, const glm::vec4& value)
	{
		glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
	}

	void OpenGLShader::setMat2(const std::string& name, const glm::mat2& mat)
	{
		glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void OpenGLShader::setMat3(const std::string& name, const glm::mat3& mat)
	{
		glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void OpenGLShader::setMat4(const std::string& name, const glm::mat4& mat)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
}
