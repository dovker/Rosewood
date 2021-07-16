#include "rwpch.h"

#include "Rosewood/Graphics/Graphics.h"
#include "Rosewood/Core/Application.h"
#include "Rosewood/Assets/AssetManager.h"
#include "BatchRenderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "Rosewood/Benchmark/Benchmark.h"

#include "Sprite.h"

namespace Rosewood
{
    void Sprite::Draw(Transform transform)
    {
        if(Animation.Playing)
        {
            timer += (float)Application::GetDeltaTime();
            if(timer >= Animation.Speed && (Animation.Loops && Animation.Frame < Animation.TotalFrames))
            {
                Animation.Frame++;
                timer = 0.0f;
            }
            if(Animation.Frame >= Animation.TotalFrames && Animation.Loops)
            {
                Animation.Frame = 0;
            }
        }
        Rect frameRect = Rect(SourceRect.Position() + glm::vec2(Animation.Frame * SourceRect.Width, 0.0f), SourceRect.RelativeWidth());
        
        glm::vec2 scale = glm::vec2(transform.Scale.x, transform.Scale.y);
                
        glm::vec2 UVX;
        glm::vec2 UVY;
        
        if(!Offset.FlippedX) UVX = glm::vec2(frameRect.Left, frameRect.Right);
        else UVX = glm::vec2(frameRect.Right, frameRect.Left);
        
        if(Offset.FlippedY) UVY = glm::vec2(frameRect.Bottom, frameRect.Top);
        else UVY = glm::vec2(frameRect.Top, frameRect.Bottom);

        glm::mat4 result;
        if(Offset.Pivot.x > 0.0f || Offset.Pivot.y > 0.0f)
        {
            BenchmarkTimer benchTimer("Matrix Multiplication");
            result = 
              glm::translate(glm::mat4(1.0f), transform.Position + glm::vec3(Offset.Pivot, 0.0f)) *
              glm::toMat4(glm::quat(transform.Rotation)) *
              glm::scale(glm::mat4(1.0f), glm::vec3(SourceRect.RelativeWidth() * scale, 1.0f)) *
              glm::translate(glm::mat4(1.0f), -glm::vec3(Offset.Pivot, 0.0f));
        }
        else
        {
            result = glm::translate(glm::mat4(1.0f), transform.Position) *
              glm::toMat4(glm::quat(transform.Rotation)) *
              glm::scale(glm::mat4(1.0f), glm::vec3(SourceRect.RelativeWidth() * scale, 1.0f));
        }

        BatchRenderer::DrawQuad(result, SpriteTexture, {UVX.x, UVY.x}, {UVX.y, UVY.y}, Color);
    }

    Sprite::Sprite(const std::string& spriteName)
        : SpriteTexture(AssetManager::Get<Texture>(spriteName)) ,RenderItem2D({1.0f, 1.0f, 1.0f, 1.0f}, false), SourceRect(Rect(SpriteTexture))
    {
    }
    void Sprite::ReloadTexture(const std::string& textureName)
    {
        SpriteTexture = AssetManager::Get<Texture>(textureName);
    }
}
