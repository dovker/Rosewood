#include "Pack.h"
#include <stdio.h>
#include <stdlib.h>


#ifdef RW_PLATFORM_WINDOWS
#  include <minizip/iowin32.h>
#endif

#define BUF_SIZE 8192
#define MAX_NAMELEN 512

namespace Rosewood
{
    Pack::Pack(const std::string& filepath)
        : m_Path(filepath)
    {
        m_ZipFile = zipOpen64(m_Path.c_str(), 0);
        RW_CORE_ASSERT(m_ZipFile != NULL, "miniZip: Failed to open {0} for zipping", m_Path);

        m_UnzipFile = unzOpen64(m_Path.c_str());
        RW_CORE_ASSERT(m_ZipFile != NULL, "miniZip: Failed to open {0} for Reading", m_Path);
    }
    Pack::~Pack()
    {
        zipClose(m_ZipFile, NULL);
        unzClose(m_UnzipFile);
    }
    void Pack::AddFile(const std::string& zipPath, const std::vector<byte>& file)
    {
        int status;
        if(file.size() == 0 || m_ZipFile == NULL)
        {
            RW_CORE_ERROR("miniZip: Error, file \"{0}\" is Empty.", zipPath);
            return;
        }
        status = zipOpenNewFileInZip64(m_ZipFile, zipPath.c_str(), NULL, NULL, 0, NULL, 0, NULL,
            Z_DEFLATED, Z_DEFAULT_COMPRESSION, (file.size() > 0xffffffff)?1:0);

        if (status != ZIP_OK)
        {
            RW_CORE_ERROR("miniZip: Error, failed opening file {0}", zipPath);
            return;
        }

        status = zipWriteInFileInZip(m_ZipFile, (void*)file.data(), file.size());

        zipCloseFileInZip(m_ZipFile);
        if (status != ZIP_OK)
        {
            RW_CORE_ERROR("miniZip: Error, failed writing file {0}", zipPath);
            return;
        }
    }
    void Pack::CreateDirectory(const std::string& filepath)
    {
        std::string modified = filepath;
        //Add Check if Path Exists
        if(filepath[filepath.size()-1] != '/')
            modified += '/';
        modified += '\0';

        zipOpenNewFileInZip64(m_ZipFile, modified.c_str(), NULL, NULL, 0, NULL, 0, NULL, 0, 0, 0);
        zipCloseFileInZip(m_ZipFile);
    }

    std::vector<byte> Pack::ReadFile(PackResult& resultInfo)
    {
        std::vector<byte> return_vector;
        byte chunk[BUF_SIZE];
        int bytes_read;
        int status;

        if (m_UnzipFile == NULL)
            resultInfo = PackResult::PACK_ERROR;

        status = unzOpenCurrentFile(m_UnzipFile);
        if (status != UNZ_OK)
            resultInfo = PackResult::PACK_ERROR;
        
        return_vector.clear();

        bytes_read = unzReadCurrentFile(m_UnzipFile, chunk, sizeof(chunk));
        return_vector.insert(return_vector.begin(), chunk, chunk+bytes_read);

        while ((bytes_read = unzReadCurrentFile(m_UnzipFile, chunk, sizeof(chunk))) > 0) {
            return_vector.insert(return_vector.end(), chunk, chunk+bytes_read);
        }

        if (bytes_read < 0) {
            unzCloseCurrentFile(m_UnzipFile);
            resultInfo = PackResult::PACK_ERROR;
        }

        unzCloseCurrentFile(m_UnzipFile);
        if (unzGoToNextFile(m_UnzipFile) != UNZ_OK)
            resultInfo = PackResult::PACK_SUCCESS_EOF;
        resultInfo = PackResult::PACK_SUCCESS;

        return return_vector;
    }

    void Pack::SkipFile()
    {
        unzGoToNextFile(m_UnzipFile);
    }
    const std::string Pack::FileName()
    {
        char name[MAX_NAMELEN];
        unz_file_info64 finfo;
        int status;

        status = unzGetCurrentFileInfo64(m_UnzipFile, &finfo, name, sizeof(name), NULL, 0, NULL, 0);
        //FIX THE WHITE SPACE
        // CHeck filename lenght and then create a string that size

        return std::string(name);

    }
    bool Pack::IsDirectory()
    {
        char            name[MAX_NAMELEN];
        unz_file_info64 finfo;
        size_t          len;
        int             ret;

        ret = unzGetCurrentFileInfo64(m_UnzipFile, &finfo, name, sizeof(name), NULL, 0, NULL, 0);
        if (ret != UNZ_OK)
            return false;

        len = strlen(name);
        if (finfo.uncompressed_size == 0 && len > 0 && name[len-1] == '/')
            return true;
        return false;
    }
    uint64_t Pack::FileSize()
    {
        unz_file_info64 finfo;
        int status;

        if (m_UnzipFile == NULL)
            return 0;

        status = unzGetCurrentFileInfo64(m_UnzipFile, &finfo, NULL, 0, NULL, 0, NULL, 0);
        if (status != UNZ_OK)
            return 0;
        return finfo.uncompressed_size;
    }
}