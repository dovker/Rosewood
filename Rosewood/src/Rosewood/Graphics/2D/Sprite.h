#pragma once
#include "rwpch.h"
#include <glm/glm.hpp>
#include "Rosewood/Graphics/2D/RenderItem2D.h"



namespace Rosewood
{
    struct Animation2D
    {
        float Speed = 1; //Seconds Per Frame TODO: FIX THIS
        uint32_t Frame = 0;
        uint32_t TotalFrames = 1;
        bool Playing = false;
        bool Loops = true;
        Animation2D() {}
        Animation2D(float speed, uint32_t frames, bool loops = true, bool playing = true)
        : Speed(speed), TotalFrames(frames), Loops(loops), Playing(playing){}
    };
    struct Offset2D
    {
        glm::vec2 Pivot = {0.0f, 0.0f};
        bool FlippedX = false;
        bool FlippedY = false;
        Offset2D() {}
    };


    
    // struct NineSlice2D //TODO: IMPLEMENT THIS
    // {
    //     bool Enabled = false;
    //     Rect SourceRect;
    // };

    class Sprite : public RenderItem2D
    {
    public:
        Ref<Texture> SpriteTexture;
        Rect SourceRect;
        
        Animation2D Animation;
        Offset2D Offset;
        
        Rect GetBounds(const Transform& transform)
        {
            glm::vec2 scale = {transform.Scale.x, transform.Scale.y};
            return Rect(glm::vec2(transform.Position.x, transform.Position.y) + (SourceRect.RelativeWidth() * scale) * Offset.Pivot,
                        SourceRect.RelativeWidth() * scale);//TODO: FIXXXXXX
        }
        
        Sprite()
            : SpriteTexture(nullptr), RenderItem2D(glm::vec4(1.0f), false) {}

        Sprite(Ref<Rosewood::Texture> texture, glm::vec4 color = glm::vec4(1.0f), bool transparent = false)
            :SpriteTexture(texture),  RenderItem2D(color, transparent), SourceRect(Rect(texture)) {}

        Sprite(const std::string& spriteName);
        
        Sprite(Ref<Rosewood::Texture> texture, glm::vec4 color, bool transparent, Rect sourceRect, Offset2D offset, Animation2D animation)
        :SpriteTexture(texture),  RenderItem2D(color, transparent), SourceRect(sourceRect), Offset(offset), Animation(animation) {}
        
        virtual void Draw(Transform transform) override;

        void ReloadTexture(const std::string& textureName);
        void ResetSourceRect() { SourceRect = Rect(SpriteTexture); }
    private:
        float timer = 0.0f;
    };
    
        
}
