#pragma once
#include "rwpch.h"
#include "Rosewood/Files/FileSystem.h"
#include "Rosewood/Assets/Asset.h"
#include "Rosewood/Assets/AssetTypes.h"


namespace Rosewood {
    
    struct AssetsData
    {
        std::unordered_map<std::string, Asset> Assets;
        //bool archived;
    };

    class AssetManager
    {
    public:
        static AssetsData assetsData;

        template <class T> static Ref<T> Load(const std::string& path, const std::string& name, FilePathType pathType = FilePathType::PROJECT, bool archived = false, bool compressed = false, uint32_t version = 0)
        {
            Asset temp;
            auto ptr = temp.Load<T>(path, name, pathType, archived, compressed, version);
            assetsData.Assets[name] = temp;
            return ptr;
        }
        template <class T> static Ref<T> Load(const std::string& name)
        {
            auto ptr = assetsData.Assets[name].Load<T>();
            return ptr;
        }
        template <class T> static void Unload(const std::string& name)
        {
            assetsData.Assets[name].Unload<T>();
        }
        template <class T> static Ref<T> Get(const std::string& name)
        {
            RW_CORE_ASSERT(Exists(name), "{0} {1} not found", AssetTypeNames[(int)T::GetAssetType()], name);
            return assetsData.Assets[name].Get<T>();
        }
        static Asset GetAsset(const std::string& name);
        static bool Exists(const std::string& name);

        template <class T> static void Add(const Ref<T>& asset, const std::string& path, const std::string& name, FilePathType pathType = FilePathType::PROJECT, uint32_t version = 0)
        {
            Asset temp = Asset(asset, path, name, pathType, version);
            assetsData.Assets[name] = temp;
        }
        static void Add(const Asset& asset);
        static std::unordered_map<std::string, Asset> GetAssets();

        //static bool packed;
    };
    
}
