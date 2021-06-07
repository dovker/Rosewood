#include "Player.h"
#include "imgui.h"
#include "../Scene/Scene.h"
#include "../Game.h"


namespace TestGame
{
    Player::Player() : m_Collider(0.0f), m_Velocity(0.0f)
    {
        m_Transform.Position = glm::vec3(-17.0f, -17.0f, 0.0f);
        m_IsSolid = false;
    }
    
    void Player::OnLoad()
    {
        Rosewood::AssetManager::Load<Rosewood::Texture>("Player.png", "Player.png");

        m_Sprite = Rosewood::Sprite::Create(Rosewood::AssetManager::Get<Rosewood::Texture>("Player.png"));
        m_Collider = Rosewood::Rect(m_Transform.Position.x, m_Transform.Position.y, m_Sprite->SpriteTexture->GetWidth(), m_Sprite->SpriteTexture->GetHeight());

        m_Map = Game::GetScene()->GetMap();
    }
    glm::vec2 PrevMousePos, pPrev;

    void Player::OnUpdate(float dt, std::vector<Entity*> entities)
    {
        glm::vec2 MousePos = {Rosewood::Input::GetMouseX(), Rosewood::Input::GetMouseY()};
        
        
        
        CalculateMovement();
        CalculateCollisions(dt, entities);
        
        m_Transform.Position.x += m_Velocity.x * dt;
        m_Transform.Position.y += m_Velocity.y * dt;
        m_Collider.SetPosition(m_Transform.Position);

        // glm::vec2 p = Game::GetScene()->GetCamera()->ScreenToWorldCoords(MousePos);
        // if(Rosewood::Input::IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        // {
        //     m_Map->SetLine((int)(pPrev.x/TileSize), (int)(pPrev.y/TileSize), (int)(p.x/TileSize), (int)(p.y/TileSize), 0);
        // }
        // if(Rosewood::Input::IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        // {
        //     m_Map->SetLineCustom((int)(pPrev.x/TileSize), (int)(pPrev.y/TileSize), (int)(p.x/TileSize), (int)(p.y/TileSize), SET_TEX_INDEX(5) | TILE_ISBLOCK, [&](int x, int y, uint32_t val){
        //         m_Map->SetCircleOutline({glm::vec2(x * TileSize, y * TileSize), 25.0f}, val);
        //     });
        // }
        // if(Rosewood::Input::IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
        // {
        //     m_Map->SetStructure((int)(p.x/TileSize), (int)(p.y/TileSize), m_Map->GetStructure(0, 0, 16, 16));
        // }
        // PrevMousePos = MousePos;
        // pPrev = Game::GetScene()->GetCamera()->ScreenToWorldCoords(PrevMousePos);
    }

    void Player::CalculateMovement()
    {
        m_Velocity = glm::vec2(0.0f);
        int inputX = Rosewood::Input::IsKeyPressed(KEY_D) - Rosewood::Input::IsKeyPressed(KEY_A);
        int inputY = Rosewood::Input::IsKeyPressed(KEY_S) - Rosewood::Input::IsKeyPressed(KEY_W);

        m_Velocity.x = inputX;
        m_Velocity.y = inputY;

        if(inputX != 0 || inputY != 0) 
        {   
            m_Velocity = glm::normalize(m_Velocity);
            if(inputX == 0 && inputY ==0)
            {
                m_Velocity = glm::vec2(0.0f);
            }
            else
            {
                m_Velocity *= 1200.0f;
            }
        }
    }
    void Player::CalculateCollisions(float dt, std::vector<Entity*> entities)
    {
        Rosewood::BenchmarkTimer timer = Rosewood::BenchmarkTimer("Player Advanced Collisions");
        std::vector<std::pair<Rosewood::Rect, float>> rects = std::vector<std::pair<Rosewood::Rect, float>>();
        glm::vec2 cp, cn;
        float t;

        //MAP COLLISIONS
        Rosewood::Rect bounds = Rosewood::Rect(m_Transform.Position.x + (m_Velocity.x * dt), m_Transform.Position.y+(m_Velocity.y* dt), m_Collider.Width, m_Collider.Height);
        int left =      glm::clamp(glm::min(bounds.Left  , m_Collider.Left  )/TileSize, 0.0f, (float)m_Map->SizeX);
        int right =     glm::ceil(glm::clamp(glm::max(bounds.Right , m_Collider.Right )/TileSize, 0.0f, (float)m_Map->SizeX));
        int top =       glm::clamp(glm::min(bounds.Top   , m_Collider.Top   )/TileSize, 0.0f, (float)m_Map->SizeY);
        int bottom =    glm::ceil(glm::clamp(glm::max(bounds.Bottom, m_Collider.Bottom)/TileSize, 0.0f, (float)m_Map->SizeY));

        //Rosewood::BatchRenderer::DrawQuad({left, top, -10.0f}, {right-left, bottom-top}, glm::vec4(1.0f, 0.0f, 0.0f, 0.2f));

        for(int j = top; j<bottom; j++)
        {
            for (int i = left; i < right; i++)
            {
                uint32_t tile = m_Map->Get(i, j);
                if(tile & TILE_ISBLOCK)
                {
                    Rosewood::Rect r = Rosewood::Rect(glm::vec2(i, j) * (float)TileSize, glm::vec2(TileSize));
                    if (Collision::DynamicRectVsRect(m_Collider, r, m_Velocity, dt, cp, cn, t))
			        {
				        rects.push_back({ r, t });
			        }
                }
            }
        }

        //Rosewood::Renderer2D::DrawRect({(float)left*TileSize, (float)top*TileSize, (float)(right-left) * TileSize, (float)(bottom-top) * TileSize}, glm::vec4(1.0f, 0.0f, 0.0f, 0.4f), -10.0f);

        //ENTITY COLLISIONS
        for(auto e : entities)
        {
            if(e->GetSolid())
            {
                if (Collision::DynamicRectVsRect(m_Collider, e->GetBounds(), m_Velocity, dt, cp, cn, t))
			    {
				    rects.push_back({ e->GetBounds(), t });
			    }
            }
        }

        std::sort(rects.begin(), rects.end(), [](const std::pair<Rosewood::Rect, float>& a, const std::pair<Rosewood::Rect, float>& b)
		{
			return a.second < b.second;
		});


        ResolveStaticCollisions(dt, rects);
    }

    void Player::ResolveStaticCollisions(float dt, std::vector<std::pair<Rosewood::Rect, float>> rects)
    {
        for (auto r : rects)
        {
            glm::vec2 contact_point, contact_normal;
            float contact_time = 0.0f;
            if (Collision::DynamicRectVsRect(m_Collider, r.first, m_Velocity, dt, contact_point, contact_normal, contact_time))
            {
                m_Velocity += contact_normal * glm::vec2(glm::abs(m_Velocity.x), glm::abs(m_Velocity.y)) * (1 - contact_time);
            }
        }
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
