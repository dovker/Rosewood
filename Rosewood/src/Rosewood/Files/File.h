#pragma once

#include "rwpch.h"
#include "Rosewood/Core/Types.h"
#include "Rosewood/Assets/AssetTypes.h"

namespace Rosewood
{
    class TextFile;

    class BinaryFile
    {
    public:
        BinaryFile() {}
        BinaryFile(const std::string& filepath);
        BinaryFile(const std::vector<byte>& data);
        BinaryFile(const BinaryFile& data);

        ~BinaryFile();

        void Reload();
        void Write();
        void Write(const std::string& filepath);

        const std::string& GetPath() const { return m_Path; }
        std::vector<byte> GetData() const { return m_Data; }
        void SetData(const std::vector<byte>& data) { m_Data = data; } // Maybe copy the data?  
        void Compress();
        void Decompress();


        TextFile ToTextFile() const;
        static AssetType GetAssetType() { return AssetType::BinaryFile; }

        static Ref<BinaryFile> Create(const std::string& filepath)
        {
            return CreateRef<BinaryFile>(filepath);
        }
        static Ref<BinaryFile> Create(const std::vector<byte>& data)
        {
            return CreateRef<BinaryFile>(data);
        }

    private:
        void m_Load(const std::string& filepath);
        std::string m_Path;
        std::vector<byte> m_Data;
    };

    class TextFile
    {
    public:
        TextFile() {}
        TextFile(const std::string& filepath);
        TextFile(std::string& data);
        TextFile(const BinaryFile& data);

        ~TextFile() {};

        void Reload();
        void Write();
        void Write(const std::string& filepath);

        const std::string& GetPath() const { return m_Path; }
        const std::string& GetData() const { return m_Data; }
        const std::vector<byte> GetRawData();
        void SetData(const std::string& data) { m_Data = data; } // Maybe copy the data?


        BinaryFile ToBinaryFile() const;
        static AssetType GetAssetType() { return AssetType::TextFile; }

        static Ref<TextFile> Create(const std::string& filepath)
        {
            return CreateRef<TextFile>(filepath);
        }
        static Ref<TextFile> Create(std::string& data)
        {
            return CreateRef<TextFile>(data);
        }
        static Ref<TextFile> Create(const BinaryFile& data)
        {
            return CreateRef<TextFile>(data);
        }
    private:
        void m_Load(const std::string& filepath);
        std::string m_Path;
        std::string m_Data;
    };
}
