#pragma once

namespace Rosewood
{
    
    enum class AssetType
    {
        Undefined,
        BinaryFile,
        TextFile,
        Model,
        Texture,
        Sound,
        Shader,
    };

    const std::string AssetTypeNames[8] =
    {
        "Undefined",
        "BinaryFile",
        "TextFile",
        "Model",
        "Texture",
        "Sound",
        "Shader"
    };
}