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
    };
}