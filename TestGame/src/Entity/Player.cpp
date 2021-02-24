#include "Player.h"

namespace TestGame
{
    Player::Player() : m_Collider(0.0f)
    {
        m_Transform.Position = glm::vec3(1.0f, 0.0f, 0.0f);
    }
    
    void Player::OnLoad()
    {
        Rosewood::AssetManager::Load<Rosewood::Texture>("Content/Player.png", "Player.png");

        m_Sprite = Rosewood::Sprite::Create(Rosewood::AssetManager::Get<Rosewood::Texture>("Player.png"));
        m_Collider = Rosewood::Rect(m_Transform.Position.x, m_Transform.Position.y, m_Sprite->Texture->GetWidth(), m_Sprite->Texture->GetHeight());
    }
    void Player::OnUpdate(float dt, std::vector<Entity*> entities)
    {
        glm::vec2 vel = glm::vec2(0.0f);
        int inputX = Rosewood::Input::IsKeyPressed(KEY_D) - Rosewood::Input::IsKeyPressed(KEY_A);
        int inputY = Rosewood::Input::IsKeyPressed(KEY_S) - Rosewood::Input::IsKeyPressed(KEY_W);

        vel.x = inputX*60.0f*dt;
        vel.y = inputY*60.0f*dt;

        if(inputX != 0 || inputY != 0) vel = glm::normalize(vel);
        
        m_Transform.Position.x += vel.x * 2.0f;
        m_Transform.Position.y += vel.y * 2.0f;

        m_Transform.Position.x = glm::clamp(m_Transform.Position.x, 0.0f, 400.0f);
        m_Transform.Position.x = glm::clamp(m_Transform.Position.x, 0.0f, 400.0f);

        
        for(auto e : entities)
        {
            if(Collision::Check(m_Collider, e->GetBounds()))
            {
                if(e->GetSolid())
                {
                    
                } else
                {
                    
                }
            }
        }

        
    
        m_Collider.SetPosition(m_Transform.Position);
    }
    void Player::OnDraw()
    {
        Rosewood::Renderer2D::Draw(m_Sprite, m_Transform);
    }
    void Player::OnUnload()
    {
        Rosewood::AssetManager::Unload<Rosewood::Texture>("Player.png");
    }
    void Player::OnEvent(Rosewood::Event &e)
    {
        //RW_TRACE("");
    }
}
