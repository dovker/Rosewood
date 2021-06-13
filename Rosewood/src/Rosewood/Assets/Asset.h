#pragma once
#include "rwpch.h"
#include "Rosewood/Files/FileSystem.h"
#include "Rosewood/Data/Pack.h"
#include "Rosewood/Files/File.h"
#include "AssetTypes.h"

namespace Rosewood {

    class Asset
    {
    public:
        Asset(){};
        Asset(std::any asset, const std::string& path, const std::string& name, FilePathType pathType, uint32_t version)
            : m_Asset(asset), m_Path(path), m_Name(name), m_Version(version), m_PathType(pathType), m_Loaded(false)
        {}
        ~Asset(){};

        template <class T> Ref<T> Load(const std::string& path, const std::string& name, FilePathType pathType = FilePathType::PROJECT, bool archived = false, bool compressed = false, uint32_t version = 0)
        {
            BinaryFile file;

            if(archived)
            {
                Pack pack(FileSystem::GetRootPath(pathType) + FileSystem::GetFolderName(pathType) + ".zip");
                file = BinaryFile(pack.ReadFile(path));
            }
            else
            {
                file = BinaryFile(Rosewood::FileSystem::GetPath(path, pathType));
            }
            
            if(compressed) file.Decompress(); 
            auto ref = T::Create(file);
            
            m_Archived = archived;
            m_AssetType = T::GetAssetType();
            m_Name = name;
            m_Path = path;
            m_Version = version;
            m_PathType = pathType;
            m_Asset = ref;
            m_Loaded = true;
            m_Compressed = compressed;

            return ref;
        }
        //LoadArchived

    
        template <class T> Ref<T> Get()
        {
            if(T::GetAssetType() == m_AssetType)
            {
                if(m_Loaded)
                    return std::any_cast<Ref<T>>(m_Asset);
                else
                     RW_CORE_ERROR("ASSET NAMED {0} IS NOT LOADED", m_Name);
            }
            else
            {
                RW_CORE_ERROR("ASSET TYPES {0} and {1} DON'T MATCH", AssetTypeNames[(int)T::GetAssetType()], AssetTypeNames[(int)m_AssetType]);
                return nullptr;
            }
        }
        template <class T> void Unload()
        {
            if(m_Loaded)
            {
                m_Loaded = false;
                std::any_cast<Ref<T>>(m_Asset).reset();
            }
        }

        AssetType GetAssetType() const { return m_AssetType; }
        std::string GetName() const { return m_Name; }
        std::string GetPath() const { return m_Path; }
        uint32_t GetVersion() const { return m_Version; }
        FilePathType GetFilePathType() const { return m_PathType; }
        
        template <class T>
        void SetData(const T& data) { m_Asset = data; m_Loaded = true; }

    private:
        AssetType m_AssetType;
        std::string m_Name;
        std::string m_Path;
        uint32_t m_Version;
        FilePathType m_PathType;
        bool m_Compressed;
        bool m_Archived;
        //bool toLoadOnInit
        bool m_Loaded;

        std::any m_Asset;

        //LoadBytes() {if(Compressed) do this else do that}
        
    };

}
