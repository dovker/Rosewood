#include <rwpch.h>
#include "Renderer2D.h"
#include "BatchRenderer.h"
#include "Rosewood/Assets/AssetManager.h"
#include "Rosewood/Files/FileSystem.h"
#include "Rosewood/Graphics/Graphics.h"


namespace Rosewood
{
    struct RendererData2D
    {
        std::vector<std::pair<RenderItem2D*, Transform>> TransparentSprites;
    };

    static RendererData2D s_Data;

    void Renderer2D::Init()
    {
        Rosewood::GraphicsCommand::ToggleBlending(true);
        Rosewood::GraphicsCommand::ToggleDepthTest(true);

        
        RenderCircle::CircleTexture = AssetManager::Load<Texture>("Textures/Circle.png", "Circle", FilePathType::ENGINE);
        RenderCircle::CircleTextureWidth = RenderCircle::CircleTexture->GetWidth();
        RenderCircle::CircleTextureHeight = RenderCircle::CircleTexture->GetHeight();
        
        s_Data.TransparentSprites = std::vector<std::pair<RenderItem2D*, Transform>>();
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
    bool compareSprites(std::pair<RenderItem2D*, Transform> s1, std::pair<RenderItem2D*, Transform> s2)
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

    void Renderer2D::Draw(Sprite sprite, Transform transform)
    {
        if(!sprite.Visible) return;
        if(!sprite.Transparent)
        {
            sprite.Draw(transform);
        }
        else
        {
            s_Data.TransparentSprites.push_back(std::pair<RenderItem2D*, Transform>((RenderItem2D*)&sprite, transform));
        }
    }
    void Renderer2D::DrawCircle(Rosewood::Circle circle, glm::vec4 color, float depth)
    {
        RenderCircle s(color);
        Transform t = Transform(glm::vec3(circle.Position, depth), glm::vec3(circle.Radius, circle.Radius, 1.0f));

        if(!s.Transparent)
        {
            s.Draw(t);
        }
        else
        {
            s_Data.TransparentSprites.push_back(std::pair<RenderItem2D*, Transform>((RenderItem2D*)&s, t));
        }
    }
    void Renderer2D::DrawRect(Rosewood::Rect rect, glm::vec4 color, float depth)
    {
        RenderQuad s(color);
        Transform t = Transform(glm::vec3(rect.Position(), depth), glm::vec3(0.0f), glm::vec3(rect.Width, rect.Height, 1.0f));

        if(!s.Transparent)
        {
            s.Draw(t);
        }
        else
        {
            s_Data.TransparentSprites.push_back(std::pair<RenderItem2D*, Transform>((RenderItem2D*)&s, t));
        }
    }
}
