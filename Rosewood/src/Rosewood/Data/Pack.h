#pragma once
#include "rwpch.h"

#include "minizip/zip.h"
#include "minizip/unzip.h"

#include "Rosewood/Core/Types.h"

//typedef void (*zipper_read_cb_t)(const unsigned char *buf, size_t size, void *thunk);

namespace Rosewood
{
    enum class PackResult
    {
        PACK_ERROR = 0,
        PACK_SUCCESS,
        PACK_SUCCESS_EOF
    };

    class Pack
    {
    public:
        Pack(const std::string& filepath);
        ~Pack();

        void AddFile(const std::string& zipPath, const std::vector<byte>& file);
        void CreateDirectory(const std::string& filepath);

        std::vector<byte> ReadFile(PackResult& resultInfo);

        void SkipFile();
        const std::string FileName();
        bool IsDirectory();
        uint64_t FileSize();

    private:
        const std::string m_Path;
        zipFile m_ZipFile;
        unzFile m_UnzipFile;
    };
}