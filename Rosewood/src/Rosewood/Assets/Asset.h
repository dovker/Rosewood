#pragma once
#include "rwpch.h"
#include "Rosewood/Files/FileSystem.h"

namespace Rosewood {
    
    
    enum class AssetType
    {
        Undefined,
        BinaryFile,
        TextFile,
        Model,
        Texture,
        Sound,
        Shader,
    };

    const std::string AssetTypeNames[8] =
    {
        "Undefined",
        "BinaryFile",
        "TextFile",
        "Model",
        "Texture",
        "Sound",
        "Shader"
    };

    class Asset
    {
    public:
        Asset(){};
        Asset(std::any asset, const std::string& path, const std::string& name, FilePathType pathType, uint32_t version)
            : m_Asset(asset), m_Path(path), m_Name(name), m_Version(version), m_PathType(pathType)
        {}
        ~Asset(){};

        template <class T> Ref<T> Load(const std::string& path, const std::string& name, FilePathType pathType = FilePathType::PROJECT, uint32_t version = 0)
        {
            auto ref = T::Create(Rosewood::FileSystem::GetPath(path, pathType));
            
            m_AssetType = T::GetAssetType();
            m_Name = name;
            m_Path = path;
            m_Version = version;
            m_PathType = pathType;
            m_Asset = ref;

            return ref;
        }
    
        template <class T> Ref<T> Get()
        {
            if(T::GetAssetType() == m_AssetType)
            {
                return std::any_cast<Ref<T>>(m_Asset);
            }
            else
            {
                RW_CORE_ERROR("ASSET TYPES {0} and {1} DON'T MATCH", AssetTypeNames[(int)T::GetAssetType()], AssetTypeNames[(int)m_AssetType]);
                return nullptr;
            }
        }

        AssetType GetAssetType() const { return m_AssetType; }
        std::string GetName() const { return m_Name; }
        std::string GetPath() const { return m_Path; }
        uint32_t GetVersion() const { return m_Version; }
        FilePathType GetFilePathType() const { return m_PathType; }
        
        template <class T>
        void SetData(const T& data) { m_Asset = data; }

    private:
        AssetType m_AssetType;
        std::string m_Name;
        std::string m_Path;
        uint32_t m_Version;
        FilePathType m_PathType;

        std::any m_Asset;
    };

}
