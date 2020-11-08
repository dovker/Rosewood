#include "Player.h"

namespace TestGame
{
    Player::Player()
    {
        m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
    }
    Player::~Player()
    {
        
    }
    void Player::OnLoad()
    {
        
        RW_TRACE("");
        
    }
    void Player::OnUpdate()
    {
        RW_TRACE("");
    }
    void Player::OnDraw()
    {
        RW_TRACE("");
    }
    void Player::OnUnload()
    {
        RW_TRACE("");
    }
}
