#include "rwpch.h"

#include "FileSystem.h"

namespace Rosewood
{
    const std::string FileSystem::EngineRoot = "../../../Rosewood/";
    const std::string FileSystem::EngineFolder = "EngineContent";
    const std::string FileSystem::ProjectFolder = "Content";

    std::filesystem::path FileSystem::getFSPath(const std::string& path, FilePathType type)
    {
        std::string contentName = "";
        std::string root = "";
        switch (type)
        {
        case FilePathType::ENGINE:
            contentName = EngineFolder + "/";
            root = EngineRoot;
            break;

        case FilePathType::PROJECT:
            contentName = ProjectFolder + "/";
            root = ProjectRoot;
            break;

        default:
            break;
        }

        #ifndef RW_DEBUG
            root = "";
        #endif

        std::filesystem::path currentPath(root + contentName + path);
        return currentPath.make_preferred();
    }

    std::string FileSystem::GetRootPath(FilePathType type)
    {
        std::string root = "";
        switch (type)
        {
        case FilePathType::ENGINE:
            root = EngineRoot;
            break;

        case FilePathType::PROJECT:
            root = ProjectRoot;
            break;

        default:
            break;
        }

        #ifndef RW_DEBUG
            root = "";
        #endif

        std::filesystem::path currentPath(root);
        return currentPath.make_preferred().string();
    }
    std::string FileSystem::GetFolderName(FilePathType type)
    {
        switch (type)
        {
        case FilePathType::ENGINE:
            return EngineFolder;
            break;

        case FilePathType::PROJECT:
            return ProjectFolder;
            break;

        default:
            return "";
            break;
        }
    }


    std::string FileSystem::GetPath(const std::string& path, FilePathType type)
    {
        return getFSPath(path, type).string();
    }

    void FileSystem::CreateDirectory(const std::string& path, FilePathType type)
    {
        try
        {
            std::filesystem::create_directory(getFSPath(path, type));
        }
        catch(std::filesystem::filesystem_error& e)
        {
            RW_CORE_ERROR("FileSystem error: ", e.what());
        }
    }
    void FileSystem::CreateDirectories(const std::string& path, FilePathType type)
    {
        try
        {
            std::filesystem::create_directories(getFSPath(path, type));
        }
        catch(std::filesystem::filesystem_error& e)
        {
            RW_CORE_ERROR("FileSystem error: ", e.what());
        }
    }
    bool FileSystem::Exists(const std::string& path, FilePathType type)
    {
        return Exists(getFSPath(path, type));
    }
    bool FileSystem::Exists(std::filesystem::path& path)
    {
        return std::filesystem::exists(path);
    }
    
    void FileSystem::CopyFile(const std::string& pathFrom, const std::string& pathTo, FilePathType type)
    {
        std::filesystem::path from = getFSPath(pathFrom, type);
        std::filesystem::path to = getFSPath(pathTo, type);

        std::filesystem::path directory = getFSPath(pathTo, type).remove_filename();

        try
        {
            if(!Exists(directory))
            {
                std::filesystem::create_directories(directory);
            }
            std::filesystem::copy(from, to, std::filesystem::copy_options::recursive);
        }
        catch(std::filesystem::filesystem_error& e)
        {
            RW_CORE_ERROR("FileSystem error: ", e.what());
        }            

    }
    void FileSystem::RemoveFile(const std::string& path, FilePathType type)
    {
        try {
            std::filesystem::remove(getFSPath(path, type));
        } catch(std::filesystem::filesystem_error& e) {
            std::cout << e.what() << '\n';
        }
    }
    void FileSystem::RemoveFolder(const std::string& path, FilePathType type)
    {
        try {
            std::filesystem::remove_all(getFSPath(path, type));
        } catch(std::filesystem::filesystem_error& e) {
            std::cout << e.what() << '\n';
        }
    }
    void FileSystem::RenameFile(const std::string& path, const std::string& name, FilePathType type)
    {
        std::filesystem::path from = getFSPath(path, type);
        std::filesystem::path to = getFSPath(path, type).remove_filename() / std::filesystem::path(name);
        RW_CORE_TRACE(to.string());
        try {
            std::filesystem::rename(from, to);
        } catch(std::filesystem::filesystem_error& e) {
            std::cout << e.what() << '\n';
        }
    }

    std::vector<std::string> FileSystem::GetDirectory(const std::string& path, FilePathType type)
    {
        std::vector<std::string> vec;
        try {
            for(auto& p: std::filesystem::directory_iterator(getFSPath(path, type)))
            {
                std::string str = p.path().string();
                str.erase(0, getFSPath("", type).string().size());
                vec.push_back(str);
            }

        } catch(std::filesystem::filesystem_error& e) {
            std::cout << e.what() << '\n';
        }
        return vec;
    }
    std::string FileSystem::GetFilename(const std::string& path)
    {
        return std::filesystem::path(path).filename().string();
    }
    std::string FileSystem::GetExtension(const std::string& path)
    {
        return std::filesystem::path(path).extension().string();
    }
    uintmax_t FileSystem::FileSize(const std::string& path, FilePathType type)
    {
        try {
            return std::filesystem::file_size(getFSPath(path, type));
        } catch(std::filesystem::filesystem_error& e) {
            std::cout << e.what() << '\n';
        }

        return 0;
    }
}