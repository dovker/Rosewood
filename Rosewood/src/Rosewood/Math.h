#pragma once
#include "rwpch.h"

namespace Rosewood {
    class Math
    {
    public:
        static uint32_t RGBAToUint(int r, int g, int b, int a)
        {
            return (uint32_t)((a << 24) | (b << 16) |
            (g << 8) | (r << 0));
        }
        static uint32_t RGBAToUint(float r, float g, float b, float a)
        {
            return (uint32_t)(((int)(a*255) << 24) | ((int)(b*255) << 16) |
            ((int)(g*255) << 8) | ((int)(r*255) << 0));
        }
    };
}
