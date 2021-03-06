#pragma once
#include "rwpch.h"

namespace Rosewood
{
    enum class FilePathType
    {
        ENGINE  = 0,
        PROJECT = 1,
        USER    = 2,
    };  
    const uint32_t FilePathTypeCount = 3;
    const std::string FilePathTypeNames[3] =
    {
        "Engine",
        "Project",
        "User"
    };

    class FileSystem
    {
    public:
        static const std::string EngineRoot;
        static const std::string ProjectRoot;
        static const std::string EngineFolder;
        static const std::string ProjectFolder;
        

        static std::string GetPath(const std::string& path, FilePathType type = FilePathType::PROJECT);
        static std::string GetRootPath(FilePathType type = FilePathType::PROJECT);
        static std::string GetFolderName(FilePathType type = FilePathType::PROJECT);

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

    private:
        static std::filesystem::path getFSPath(const std::string& path, FilePathType type);
    };
}