#pragma once
#include "rwpch.h"

namespace Rosewood
{
    enum class FilePathType
    {
        ENGINE,
        PROJECT
    };

    class FileSystem
    {
    public:
        static const std::string EngineRoot;
        static const std::string ProjectRoot;

        

        static std::string GetPath(const std::string& path, FilePathType type = FilePathType::PROJECT);
        static void CreateDirectory(const std::string& path, FilePathType type = FilePathType::PROJECT);
        static void CreateDirectories(const std::string& path, FilePathType type = FilePathType::PROJECT);

        static bool Exists(const std::string& path, FilePathType type = FilePathType::PROJECT);
        static bool Exists(std::filesystem::path& path);

        static void CopyFile(const std::string& pathFrom, const std::string& pathTo, FilePathType type = FilePathType::PROJECT);
        static void RenameFile(const std::string& path, const std::string& name, FilePathType type = FilePathType::PROJECT);
        static void RemoveFile(const std::string& path, FilePathType type = FilePathType::PROJECT);
        static void RemoveFolder(const std::string& path, FilePathType type = FilePathType::PROJECT);


        static std::vector<std::string> GetDirectory(const std::string& path, FilePathType type = FilePathType::PROJECT);
        static std::string GetFilename(const std::string& path);
        static std::string GetExtension(const std::string& path);

        static uintmax_t FileSize(const std::string& path, FilePathType type = FilePathType::PROJECT);


        // FILE ReadFile(Path)
        // void WriteFile(FILE file);
        // FILE ReadFileCompressed();
        // void WriteFileCompressed;
        // void MakeDir
        // void CopyFile(FILE);
        // std::string ListDirectory

        //Unordered map for default storing places
        //Also contains platform specific application folders for save files

        //Also make a file watcher??
        //USE FILESYSTEM FOR COPYING AND SUCH
        //Get List of files in a path

        //Also, ZLIB?
        //Zlib functions in loading?
        //Byte Data loading

        //Abstracting FILE Class which holds file data and reads / writes.
    private:
        static std::filesystem::path getFSPath(const std::string& path, FilePathType type);
    };
}