#include <rwpch.h>
#include "OpenGL.h"
#include <glad/glad.h>

#include <glm/glm.hpp>

namespace Rosewood
{
    //bool OpenGL::Old = true; //fix this

    void OpenGL::Init()
    {
        glEnable(GL_DEPTH_TEST);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        //glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glBlendFunc(GL_ONE, GL_ONE);
        //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

    }

    void OpenGL::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGL::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
    void OpenGL::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGL::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
    {
        uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    void OpenGL::BindTexture(uint32_t ID, uint32_t slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, ID);
    }
    void OpenGL::ToggleDepthTest(bool toggle)
    {
        toggle ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    }
    void OpenGL::ToggleBlending(bool toggle)
    {
        toggle ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
    }
    void OpenGL::ToggleBackfaceCulling(bool toggle)
    {
        toggle ?         glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
        glFrontFace(GL_CCW);

        glCullFace(GL_BACK);
    }
}
