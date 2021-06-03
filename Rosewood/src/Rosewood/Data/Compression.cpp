#include "rwpch.h"

#include "Compression.h"
#include "zlib.h"
#include <cstdlib>
#include "Rosewood/Core/Log.h"
#include "Rosewood/Core/Core.h"

//Based off of https://github.com/amzeratul/halley/blob/develop/src/engine/utils/src/bytes/compression.cpp
//I am currently saving my time and implementing this while referencing other code just for the sake of speed.

static voidpf zlibAlloc (voidpf opaque, uInt items, uInt size)
{
	return malloc(size_t(items * size));
}

static void zlibFree(voidpf opaque, voidpf address)
{
	free(address);
}


namespace Rosewood
{
    std::vector<byte> Compression::Compress(const std::vector<byte>& bytes)
    {
        return CompressRaw(bytes, true);
    }

    std::vector<byte> Compression::Decompress(const std::vector<byte>& bytes, size_t maxSize)
    {
        RW_CORE_ASSERT(sizeof(uint64_t) == 8, "Type \"uint64_t\" is not 8 bytes in size");
        RW_CORE_ASSERT(bytes.size() >= 8, "File trying to decompress is too small");
        uint64_t expectedOutSize;
        memcpy(&expectedOutSize, bytes.data(), 8);

        std::vector<byte>::const_iterator first = bytes.begin() + 8;
        std::vector<byte>::const_iterator last  = bytes.end();
        std::vector<byte> newVec(first, last);

        auto out = DecompressRaw(newVec, maxSize, size_t(expectedOutSize));

        return out;
    }


    std::vector<byte> Compression::CompressRaw(const std::vector<byte>& bytes, bool insertLength)
    {
        RW_CORE_ASSERT(sizeof(uint64_t) == 8, "Type \"uint64_t\" is not 8 bytes in size");

        const uint64_t inSize = bytes.size();
        const size_t headerSize = insertLength ? 8 : 0;
        std::vector<byte> result(size_t(inSize) + headerSize + 16); // Header size, plus 16 bytes for headroom, should be enough for any compression

        if (insertLength) {
            memcpy(result.data(), &inSize, 8);
        }

        z_stream stream;
        stream.zalloc = &zlibAlloc;
        stream.zfree = &zlibFree;
        stream.opaque = nullptr;
        int res = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
        if (res != Z_OK) {
            RW_CORE_CRITICAL("Unable to initialize zlib compression");
        }

        stream.avail_in = uInt(bytes.size());
        stream.next_in = reinterpret_cast<unsigned char*>(const_cast<byte*>(bytes.data())); //Check this
        stream.avail_out = uInt(result.size() - headerSize);
        stream.next_out = result.data() + headerSize;

        do {
            res = deflate(&stream, Z_FINISH);
            if (res == Z_STREAM_ERROR || res == Z_BUF_ERROR) {
                deflateEnd(&stream);
                RW_CORE_CRITICAL("Unable to compress data.");
            }
        } while (res != Z_STREAM_END);

        const size_t outSize = size_t(stream.total_out);
        deflateEnd(&stream);

        result.resize(headerSize + outSize);
        
        return result;
    }

    std::vector<byte> Compression::DecompressRaw(const std::vector<byte>& bytes, size_t maxSize, size_t expectedSize)
    {
        if (expectedSize > uint64_t(maxSize)) {
            RW_CORE_CRITICAL("File is too big to inflate: {0}", expectedSize);
        }
        
        z_stream stream;
        stream.zalloc = &zlibAlloc;
        stream.zfree = &zlibFree;
        stream.opaque = nullptr;
        stream.avail_in = 0;
        stream.next_in = nullptr;
        int ret = inflateInit(&stream);
        if (ret != Z_OK) {
            RW_CORE_CRITICAL("Unable to initialize zlib");
        }
        stream.avail_in = uInt(bytes.size());
        stream.next_in = reinterpret_cast<unsigned char*>(const_cast<byte*>(bytes.data()));

        if (expectedSize > 0) {
            std::vector<byte> result(expectedSize);
            stream.avail_out = uInt(result.size());
            stream.next_out = result.data();
            
            const int res = inflate(&stream, Z_NO_FLUSH);
            const size_t totalOut = size_t(stream.total_out);
            inflateEnd(&stream);

            if (res != Z_STREAM_END) {
                RW_CORE_CRITICAL("Unable to inflate stream.");
            }
            if (totalOut != expectedSize) {
                RW_CORE_CRITICAL("Unexpected outsize ({0}) when inflating data, expected ({1}).", result.size(), expectedSize);
            }

            return result;
        } else {
            constexpr size_t blockSize = 256 * 1024;
            std::vector<byte> result(std::min(blockSize, maxSize));

            int res = 0;
            do {
                // Expand if needed
                if (result.size() - size_t(stream.total_out) < blockSize / 2) {
                    if (result.size() >= maxSize) {
                        inflateEnd(&stream);
                        RW_CORE_CRITICAL("Unable to inflate stream, maximum size has been exceeded.");
                    }
                    auto newSize = std::min(result.size() + blockSize, maxSize);
                    result.resize(newSize);
                }
                stream.avail_out = uInt(result.size()) - stream.total_out;
                stream.next_out = result.data() + size_t(stream.total_out);
                res = inflate(&stream, Z_NO_FLUSH);
            } while (res == Z_OK);

            const size_t totalOut = size_t(stream.total_out);
            inflateEnd(&stream);

            if (res != Z_STREAM_END) {
                RW_CORE_CRITICAL("Unable to inflate stream.");
            }
            result.resize(totalOut);

            return result;
        }
    }
}