#pragma once 
#include "rwpch.h"

#include "Rosewood/Core/Types.h"

namespace Rosewood
{
    class Compression
    {
    public:
        static std::vector<byte> Compress(const std::vector<byte>& bytes);
        static std::vector<byte> Decompress(const std::vector<byte>& bytes, size_t maxSize = std::numeric_limits<size_t>::max());

        static std::vector<byte> CompressRaw(const std::vector<byte>& bytes, bool insertLength);
        static std::vector<byte> DecompressRaw(const std::vector<byte>& bytes, size_t maxSize, size_t expectedSize = 0);
    };
}