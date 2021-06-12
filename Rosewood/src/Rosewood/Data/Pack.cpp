#include "rwpch.h"

#include "Pack.h"
#include <stdio.h>
#include <stdlib.h>
#include "zip.h"

#define BUF_SIZE 8192

namespace Rosewood
{
    Pack::Pack(const std::string& filepath)
        : m_Path(filepath)
    {
        int error = 0;
        m_ZipFile = zip_open(filepath.c_str(), ZIP_CREATE, &error);
        if(!m_ZipFile)
        {
            RW_CORE_ERROR("libzip: Failed to open {0} for zipping", m_Path);
        }
    }
    Pack::~Pack()
    {
        if (zip_close(m_ZipFile) != 0)
        {
            RW_CORE_ERROR("libzip: Failed to close zip archive: {0}", m_Path);
        }
    }
    void Pack::AddFile(const std::string& filepath, const std::vector<byte>& file)
    {
        int lastSeparator = filepath.rfind('/');
        if(lastSeparator != -1)
        {
            std::string directory = filepath.substr(0, lastSeparator+1);
            CreateDirectory(directory);
        }
        auto ptr = static_cast<char*>(std::malloc(file.size()));

        std::memcpy(ptr, file.data(), file.size());
        
    //     zip_source* source = zip_source_buffer(zipHandle, data, length, freeData);
        zip_source* source = zip_source_buffer(m_ZipFile, ptr, file.size(), 1);
        
        if(source != nullptr)
        {
            int64_t result = zip_file_add(m_ZipFile, filepath.c_str(), source, ZIP_FL_OVERWRITE | ZIP_FL_ENC_GUESS);
            if(result < 0) 
            {
                RW_CORE_ERROR("libzip: FAILED TO ADD FILE {0}", filepath);
                zip_source_free(source);
            }
        }
        else
        {
            RW_CORE_ERROR("libzip: FAILED TO CREATE SOURCE {0}", filepath);
        }
    }

    void Pack::CreateDirectory(const std::string& filepath)
    {
        int separator = filepath.find('/');
        while(separator != -1)
        {
            std::string subPath = filepath.substr(0, separator+1);
            if(!Exists(filepath))
            {
                int64_t result = zip_dir_add(m_ZipFile, filepath.c_str(), ZIP_FL_ENC_GUESS);
                if (result==-1) { RW_CORE_ERROR("libzip: Failed to create directory {0}", filepath); }
            }
            separator = filepath.find('/', separator+1);
        }
    }
    bool Pack::Exists(const std::string& filepath)
    {
        return zip_name_locate(m_ZipFile, filepath.c_str(), ZIP_FL_ENC_GUESS) >= 0;
    }

    std::vector<byte> Pack::ReadFile(const std::string& filepath)
    {
        std::vector<byte> return_vector;
        byte chunk[BUF_SIZE];
        int bytes_read;

        struct zip_file* file = zip_fopen_index(m_ZipFile, zip_name_locate(m_ZipFile, filepath.c_str(), ZIP_FL_ENC_GUESS), 0);
        if (!file)
        {
            RW_CORE_ERROR("libzip: ERROR OPENING FILE: {0}", filepath);
        }

        return_vector.clear();

        //bytes_read = unzReadCurrentFile(m_UnzipFile, chunk, sizeof(chunk));
        bytes_read = zip_fread(file, chunk, sizeof(chunk));
        if(bytes_read > 0)
            return_vector.insert(return_vector.begin(), chunk, chunk+bytes_read);
        else RW_CORE_ERROR("libzip: READING FILE THAT IS 0 BYTES: {0}", filepath);


        while ((bytes_read = zip_fread(file, chunk, sizeof(chunk))) > 0) {
            return_vector.insert(return_vector.end(), chunk, chunk+bytes_read);
        }

        zip_fclose(file);

        return return_vector;
    }

}