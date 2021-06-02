#include "rwpch.h"
#include "Rosewood/Core/Types.h"

namespace Rosewood
{
    class BinaryFile
    {
    public:
        BinaryFile(const std::string& filepath);
        BinaryFile(const std::vector<byte>& data);
        ~BinaryFile();

        void Reload();
        void Write();
        void Write(const std::string& filepath);

        const std::string& GetPath() { return m_Path; }
        std::vector<byte> GetData() { return m_Data; }
        void SetData(const std::vector<byte>& data) { m_Data = data; } // Maybe copy the data?

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
        TextFile(const std::string& filepath);
        TextFile(std::string& data);
        ~TextFile() {};

        void Reload();
        void Write();
        void Write(const std::string& filepath);

        const std::string& GetPath() { return m_Path; }
        const std::string& GetData() { return m_Data; }
        void SetData(const std::string& data) { m_Data = data; } // Maybe copy the data?

        static Ref<TextFile> Create(const std::string& filepath)
        {
            return CreateRef<TextFile>(filepath);
        }
        static Ref<TextFile> Create(std::string& data)
        {
            return CreateRef<TextFile>(data);
        }
    private:
        void m_Load(const std::string& filepath);
        std::string m_Path;
        std::string m_Data;
    };
}
