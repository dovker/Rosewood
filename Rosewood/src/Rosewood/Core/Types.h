#pragma once

typedef unsigned char byte;

namespace Rosewood
{
    struct UnsafeBuffer
    {
        size_t Size;
        void* Data;
    };
}