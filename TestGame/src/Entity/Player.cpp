#include "Player.h"

namespace TestGame
{
    Player::Player()
    {
        m_Position = glm::vec3(1.0f, 0.0f, 0.0f);
        collider = AABB();
    }
    
    void Player::OnLoad(Rosewood::AssetManager &assetManager)
    {
        m_Texture = assetManager.Load<Rosewood::Texture>("Content/Player.png", "Player.png");
        collider = AABB(glm::vec2(0.0f), glm::vec2(m_Texture->GetWidth(), m_Texture->GetHeight()));
    }
    void Player::OnUpdate()
    {
        if(Rosewood::Input::IsKeyPressed(KEY_W))
        {
            m_Position.y -= 1;
        }
        if(Rosewood::Input::IsKeyPressed(KEY_S))
        {
            m_Position.y += 1;
        }
        if(Rosewood::Input::IsKeyPressed(KEY_A))
        {
            m_Position.x -= 1;
        }
        if(Rosewood::Input::IsKeyPressed(KEY_D))
        {
            m_Position.x += 1;
        }
        collider.Position = m_Position;
    }
    void Player::OnDraw()
    {
        AABB b = AABB({0.0f, 0.0f}, {10.0f, 10.0f});
        Rosewood::BatchRenderer::DrawQuad({0.0f, 0.0f, 1.0f}, {10.0f, 10.0f}, glm::vec4(1.0f));

        if (Collision::Check(collider, b))
        {
            Rosewood::BatchRenderer::DrawQuad(m_Position, m_Texture, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        } else
        {
            Rosewood::BatchRenderer::DrawQuad(m_Position, m_Texture);
        }
    }
    void Player::OnUnload(Rosewood::AssetManager &assetManager)
    {
        assetManager.Unload<Rosewood::Texture>("Player.png");
    }
    void Player::OnEvent(Rosewood::Event &e)
    {
        //RW_TRACE("");
    }
}
