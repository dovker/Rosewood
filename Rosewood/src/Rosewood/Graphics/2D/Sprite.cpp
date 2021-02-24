#include "rwpch.h"

#include "Rosewood/Graphics/Graphics.h"
#include "Rosewood/Application.h"
#include "BatchRenderer.h"

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
        
        glm::vec2 texSize = glm::vec2(Texture->GetWidth(), Texture->GetHeight());
        
        glm::vec2 pos = glm::vec2(transform.Position.x, transform.Position.y) + (SourceRect.RelativeWidth() * scale) * Offset.Offset;
        
        glm::vec2 UVX;
        glm::vec2 UVY;
        
        if(!Offset.FlippedX) UVX = glm::vec2(frameRect.Right, frameRect.Left);
        else UVX = glm::vec2(frameRect.Left, frameRect.Right);
        
        if(Offset.FlippedY) UVY = glm::vec2(frameRect.Bottom, frameRect.Top);
        else UVY = glm::vec2(frameRect.Top, frameRect.Bottom);
        
        if(transform.Rotation.z > 0.00001)
        {
            BatchRenderer::DrawQuad(glm::vec3(pos, transform.Position.z), SourceRect.RelativeWidth() * scale, Texture, {UVX.x, UVY.x}, {UVX.y, UVY.y}, Color);
        }
        else
        {
            BatchRenderer::DrawQuad(glm::vec3(pos, transform.Position.z), SourceRect.RelativeWidth() * scale, Texture, transform.Rotation.z, {UVX.x, UVY.x}, {UVX.y, UVY.y}, Color);
        }
        
    }
    
}
