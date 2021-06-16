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
        Asset(std::any asset, const std::string& path, const std::string& name, FilePathType pathType, uint32_t version, bool archived = false, bool compressed = false, bool load = true)
            : m_Asset(asset), m_Path(path), m_Name(name), m_Version(version), m_PathType(pathType), m_Loaded(false), m_Compressed(compressed), m_Archived(archived), m_LoadOnInit(load)
        {}
        Asset(const std::string& path, const std::string& name, FilePathType pathType, AssetType assetType, uint32_t version, bool archived = false, bool compressed = false, bool load = true)
            : m_Path(path), m_Name(name), m_Version(version), m_PathType(pathType), m_AssetType(assetType), m_Loaded(false), m_Compressed(compressed), m_Archived(archived), m_LoadOnInit(load)
        {}
        ~Asset(){};

        template <class T> Ref<T> Load(const std::string& path, const std::string& name, FilePathType pathType = FilePathType::PROJECT, bool archived = false, bool compressed = false, uint32_t version = 0)
        {
            BinaryFile file;


            m_Archived = archived;
            m_AssetType = T::GetAssetType();
            m_Name = name;
            m_Path = path;
            m_Version = version;
            m_PathType = pathType;
            m_Loaded = true;
            m_Compressed = compressed;

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
            m_Asset = ref;

            return ref;
        }
        //LoadArchived

    
        template <class T> Ref<T> Get()
        {
            if(T::GetAssetType() == m_AssetType)
            {
                if(m_Loaded)
                {
                    return std::any_cast<Ref<T>>(m_Asset);
                }
                else
                     RW_CORE_ERROR("ASSET NAMED {0} IS NOT LOADED", m_Name);
            }
            else
            {
                RW_CORE_ERROR("ASSET TYPES {0} and {1} DON'T MATCH", AssetTypeNames[(int)T::GetAssetType()], AssetTypeNames[(int)m_AssetType]);
            }
            return nullptr;
        }
        template <class T> void Unload()
        {
            if(m_Loaded)
            {
                m_Loaded = false;
                std::any_cast<Ref<T>>(m_Asset).reset();
            }
        }
        template <class T> Ref<T> Load()
        {
            if(!m_Loaded)
            {
                BinaryFile file;

                if(m_Archived)
                {
                    Pack pack(FileSystem::GetRootPath(m_PathType) + FileSystem::GetFolderName(m_PathType) + ".zip");
                    file = BinaryFile(pack.ReadFile(m_Path));
                }
                else
                {
                    file = BinaryFile(Rosewood::FileSystem::GetPath(m_Path, m_PathType));
                }
                
                if(m_Compressed) file.Decompress(); 
                auto ref = T::Create(file);
                m_Loaded = true;
                m_Asset = ref;
                return ref;
            }
            return this->Get<T>();
        }

        AssetType GetAssetType() const { return m_AssetType; }
        std::string GetName() const { return m_Name; }
        std::string GetPath() const { return m_Path; }
        uint32_t GetVersion() const { return m_Version; }
        FilePathType GetFilePathType() const { return m_PathType; }
        bool GetArchived() const {return m_Archived;}
        bool GetCompressed() const {return m_Compressed;}
        bool GetLoadOnInit() const {return m_LoadOnInit;}
        
        template <class T>
        void SetData(const T& data) { m_Asset = data; m_Loaded = true; }

    private:
        std::string m_Name;

        AssetType m_AssetType;
        std::string m_Path;
        uint32_t m_Version = 0;
        FilePathType m_PathType;
        bool m_Compressed;
        bool m_Archived;
        bool m_LoadOnInit;
        
        bool m_Loaded;
        std::any m_Asset;

        //LoadBytes() {if(Compressed) do this else do that}
        
    };

}
