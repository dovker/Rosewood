#pragma once
#include "rwpch.h"
#include "Rosewood/Core/Types.h"

struct zip;

namespace Rosewood
{
    class Pack
    {
    public:
        Pack(const std::string& filepath);
        ~Pack();

        void CreateDirectory(const std::string& filepath);

        std::vector<byte> ReadFile(const std::string& filepath);
        void AddFile(const std::string& filepath, const std::vector<byte>& file);

        bool Exists(const std::string& filepath);

        //Compress
        //Encrypt

    private:
        const std::string m_Path;
        zip* m_ZipFile;
    };
}
