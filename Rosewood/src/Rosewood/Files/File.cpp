#include "rwpch.h"

#include "File.h"
#include "Rosewood/Data/Compression.h"

namespace Rosewood
{
    void BinaryFile::m_Load(const std::string& filepath)
    {
        try //TEST TRY CATCH ERRORS
        {
            std::ifstream ifs(filepath, std::ios::binary);
            

            ifs.unsetf(std::ios::skipws);

            std::streampos fileSize;

            ifs.seekg(0, std::ios::end);
            fileSize = ifs.tellg();
            ifs.seekg(0, std::ios::beg);
            if (ifs.bad() || fileSize < 0)
            {
                throw std::invalid_argument("Error Reading the file");
            }

            // reserve capacity
            m_Data.clear();
            m_Data.reserve(fileSize);

            // read the data:
            m_Data.insert(m_Data.begin(),
                    std::istream_iterator<byte>(ifs),
                    std::istream_iterator<byte>());
		}
		catch (const std::invalid_argument& e)
		{
			RW_CORE_ERROR("BINARY FILE IFSTREAM ERROR: {0}", e.what());
		}
    }
    BinaryFile::BinaryFile(const std::string& filepath)
        : m_Path(filepath)
    {
        m_Data = std::vector<byte>();
        m_Load(filepath);
    }
    BinaryFile::BinaryFile(const std::vector<byte>& data)
        : m_Data(data)
    {

    }
    BinaryFile::BinaryFile(const BinaryFile& data)
        : m_Data(data.GetData())
    {

    }
    void BinaryFile::Compress(){
        m_Data = Rosewood::Compression::Compress(m_Data);
    }
    void BinaryFile::Decompress(){
        m_Data = Rosewood::Compression::Decompress(m_Data);
    }
    BinaryFile::~BinaryFile()
    {

    }
    void BinaryFile::Reload()
    {
        if(!m_Path.empty())
            m_Load(m_Path);
        else
            RW_CORE_ERROR("BINARY FILE DOESN'T HAVE A SET PATH");
    }
    void BinaryFile::Write()
    {
        if(!m_Path.empty())
            Write(m_Path);
        else
            RW_CORE_ERROR("BINARY FILE DOESN'T HAVE A SET PATH");
    }
    void BinaryFile::Write(const std::string& filepath)
    {
        try
        {
            std::ofstream ofs(filepath, std::ios::out | std::ios::binary); 
            ofs.write(reinterpret_cast<const char*>(m_Data.data()), m_Data.size());
            if(ofs.bad())
			{
				throw std::invalid_argument("Error Reading the file");
			}
		}
		catch (const std::invalid_argument& e)
		{
            RW_CORE_ERROR("BINARY OFSTREAM ERROR: {0}", e.what());
        }
    }
    TextFile BinaryFile::ToTextFile() const 
    {
        return TextFile(*this);
    }
    

    BinaryFile TextFile::ToBinaryFile() const
    {
        return BinaryFile(std::vector<byte>(m_Data.begin(), m_Data.end()));
    }
    const std::vector<byte> TextFile::GetRawData()
    {
        return std::vector<byte>(m_Data.begin(), m_Data.end());
    }
    void TextFile::m_Load(const std::string& filepath)
    {
        try
        {
            std::ifstream ifs(filepath);
            m_Data.assign( (std::istreambuf_iterator<char>(ifs) ),
                (std::istreambuf_iterator<char>()) );
            if(ifs.bad())
			{
				throw std::invalid_argument("Error Reading the file");
			}
		}
		catch (const std::invalid_argument& e)
		{
            RW_CORE_ERROR("TEXT FILE IFSTREAM ERROR: {0}", e.what());
        }
        
    }
    TextFile::TextFile(const std::string& filepath)
        : m_Path(filepath)
    {
        m_Data = std::string();
        m_Load(filepath);

    }
    TextFile::TextFile(std::string& data)
        : m_Data(data)
    {
    }
    TextFile::TextFile(const BinaryFile& data)
    {
        m_Path = data.GetPath();
        m_Data.resize(data.GetData().size());
        std::memcpy(m_Data.data(), data.GetData().data(), data.GetData().size());
    }

    void TextFile::Reload()
    {
        if(!m_Path.empty())
            m_Load(m_Path);
        else
            RW_CORE_ERROR("TEXT FILE DOESN'T HAVE A SET PATH");
    }
    void TextFile::Write()
    {
        if(!m_Path.empty())
            Write(m_Path);
        else
            RW_CORE_ERROR("TEXT FILE DOESN'T HAVE A SET PATH");
    }
    void TextFile::Write(const std::string& filepath)
    {
        try
        {
            std::ofstream ofs(filepath);
            ofs.exceptions(std::ofstream::badbit | std::ofstream::failbit);
            ofs << m_Data;
            if(ofs.bad())
			{
				throw std::invalid_argument("Error Reading the file");
			}
		}
		catch (const std::invalid_argument& e)
		{
            RW_CORE_ERROR("TEXT OFSTREAM ERROR: {0}", e.what());
        }
    }
}
