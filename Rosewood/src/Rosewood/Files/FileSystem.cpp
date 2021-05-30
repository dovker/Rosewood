#include "FileSystem.h"

namespace Rosewood
{
    const std::string FileSystem::EngineRoot = "../../../Rosewood/";

    std::string FileSystem::GetPath(const std::string& path, FilePathType type)
    {
        std::string contentName = "";
        std::string root = "";
        switch (type)
        {
        case FilePathType::ENGINE:
            contentName = "EngineContent/";
            root = EngineRoot;
            break;

        case FilePathType::PROJECT:
            contentName = "Content/";
            root = ProjectRoot;
            break;

        default:
            break;
        }
#ifdef RW_DEBUG
        root = "";
#endif
        std::filesystem::path currentPath(root + contentName + path);
        return currentPath.c_str();
    }
}