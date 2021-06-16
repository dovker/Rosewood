#pragma once

namespace Rosewood
{
    enum class AssetType
    {
        Undefined   = 0,
        BinaryFile  = 1,
        TextFile    = 2,
        Model       = 3,
        Texture     = 4,
        Sound       = 5,
        Shader      = 6,
    };
    const uint32_t AssetTypeCount = 7;
    const std::string AssetTypeNames[7] =
    {
        "ud",
        "bf",
        "tf",
        "md",
        "tx",
        "sn",
        "sh"
    };
}