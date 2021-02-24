#include <rwpch.h>
#include "Renderer2D.h"
#include "BatchRenderer.h"
#include "Rosewood/Assets/Assets.h"

namespace Rosewood
{
    struct RendererData2D
    {
        std::vector<std::pair<Ref<Sprite>, Transform>> TransparentSprites;
    };

    static RendererData2D s_Data;

    void Renderer2D::Init()
    {
        Rosewood::GraphicsCommand::ToggleBlending(true);
        Rosewood::GraphicsCommand::ToggleDepthTest(true);
        
        AssetManager::Load<Texture>("EngineContent/Textures/Circle.png", "Circle");
        
        
        s_Data.TransparentSprites = std::vector<std::pair<Ref<Sprite>, Transform>>();
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
    bool compareSprites(std::pair<Ref<Sprite>, Transform> s1, std::pair<Ref<Sprite>, Transform> s2)
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
            s_Data.TransparentSprites.push_back(std::pair<Ref<Sprite>, Transform>(sprite, transform));
        }
    }
}
