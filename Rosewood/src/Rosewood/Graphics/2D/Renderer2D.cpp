#include <rwpch.h>
#include "Renderer2D.h"
#include "BatchRenderer.h"
#include "Rosewood/Assets/Assets.h"
#include "Rosewood/Files/FileSystem.h"


namespace Rosewood
{
    struct RendererData2D
    {
        std::vector<std::pair<Ref<RenderItem2D>, Transform>> TransparentSprites;
        Ref<Texture> CircleTexture;
    };

    static RendererData2D s_Data;

    void Renderer2D::Init()
    {
        Rosewood::GraphicsCommand::ToggleBlending(true);
        Rosewood::GraphicsCommand::ToggleDepthTest(true);

        
        s_Data.CircleTexture = AssetManager::Load<Texture>(FileSystem::GetPath("Textures/Circle.png", FilePathType::ENGINE), "Circle");

        
        s_Data.TransparentSprites = std::vector<std::pair<Ref<RenderItem2D>, Transform>>();
        s_Data.TransparentSprites.reserve(100);
        BatchRenderer::Init();
    }
    void Renderer2D::Shutdown()
    {
        BatchRenderer::Shutdown();
    }
    void Renderer2D::SetShader(Ref<Shader> shader)
    {
        BatchRenderer::SetShader(shader);
    }

    void Renderer2D::Begin(const OrthographicCamera& camera)
    {
        BatchRenderer::Begin(camera);
    }
    void Renderer2D::Begin(const EditorCamera& camera)
    {
        BatchRenderer::Begin(camera);
    }
    void Renderer2D::Begin(const Camera& camera, const glm::mat4& transform)
    {
        BatchRenderer::Begin(camera, transform);
    }
    bool compareSprites(std::pair<Ref<RenderItem2D>, Transform> s1, std::pair<Ref<RenderItem2D>, Transform> s2)
    {
        return (s1.second.Position.z > s2.second.Position.z);
    }
    void Renderer2D::End()
    {
        std::sort(s_Data.TransparentSprites.begin(), s_Data.TransparentSprites.end(), compareSprites);
        for(auto& s : s_Data.TransparentSprites)
        {
            s.first->Draw(s.second);
        }
        BatchRenderer::End();
        s_Data.TransparentSprites.clear();
    }

    void Renderer2D::Draw(Ref<Sprite> sprite, Transform transform)
    {
        if(!sprite->Transparent)
        {
            sprite->Draw(transform);
        }
        else
        {
            s_Data.TransparentSprites.push_back(std::pair<Ref<RenderItem2D>, Transform>(sprite, transform));
        }
    }
    void Renderer2D::DrawCircle(Rosewood::Circle circle, glm::vec4 color, float depth)
    {
        Ref<RenderCircle> s = RenderCircle::Create(color, s_Data.CircleTexture);
        Transform t = Transform(glm::vec3(circle.Position, depth), glm::vec3(circle.Radius, circle.Radius, 1.0f));

        if(!s->Transparent)
        {
            s->Draw(t);
        }
        else
        {
            s_Data.TransparentSprites.push_back(std::pair<Ref<RenderItem2D>, Transform>(s, t));
        }
    }
    void Renderer2D::DrawRect(Rosewood::Rect rect, glm::vec4 color, float depth)
    {
        Ref<RenderQuad> s = RenderQuad::Create(color);
        Transform t = Transform(glm::vec3(rect.Position(), depth), glm::vec3(0.0f), glm::vec3(rect.Width, rect.Height, 1.0f));

        if(!s->Transparent)
        {
            s->Draw(t);
        }
        else
        {
            s_Data.TransparentSprites.push_back(std::pair<Ref<RenderItem2D>, Transform>(s, t));
        }
    }
}
