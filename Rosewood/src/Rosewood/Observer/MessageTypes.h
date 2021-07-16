#pragma once

#include "Rosewood/Core/Core.h"

namespace Rosewood
{
    enum class MessageCategory : uint32_t
    {
        NONE = BIT(0),
        UI = BIT(1),
        GAME = BIT(2),
        ECS = BIT(3),
        NETWORK = BIT(4)
    };
}