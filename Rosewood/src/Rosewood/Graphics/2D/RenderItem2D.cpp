#include <rwpch.h>
#include "RenderItem2D.h"
#include "Rosewood/Assets/AssetManager.h"
#include "Rosewood/Files/FileSystem.h"
#include "Rosewood/Graphics/API/Texture.h"


namespace Rosewood
{
    Ref<Texture> RenderCircle::CircleTexture = nullptr;
    uint32_t RenderCircle::CircleTextureWidth = 0;
    uint32_t RenderCircle::CircleTextureHeight = 0;
}