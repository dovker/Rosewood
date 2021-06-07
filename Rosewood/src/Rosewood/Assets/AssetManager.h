#pragma once
#include "rwpch.h"
#include "Rosewood/Files/FileSystem.h"
#include "Rosewood/Assets/Asset.h"

namespace Rosewood {
    


    struct AssetsData
    {
        std::unordered_map<std::string, Asset> Assets;
    };

    static AssetsData assetsData;

    class AssetManager
    {
    public:
        AssetManager(){};
        ~AssetManager(){};
        template <class T> static Ref<T> Load(const std::string& path, const std::string& name, FilePathType pathType = FilePathType::PROJECT, uint32_t version = 0)
        {
            Asset temp;
            auto ptr = temp.Load<T>(path, name, pathType, version);
            assetsData.Assets[name] = temp;
            return ptr;
        }
        template <class T> static void Unload(const std::string& name)
        {
            assetsData.Assets[name].Get<T>().reset();
        }
        template <class T> static Ref<T> Get(const std::string& name)
        {
            RW_CORE_ASSERT(Exists<T>(name), "{0} {1} not found", AssetTypeNames[(int)T::GetAssetType()], name);
            return assetsData.Assets[name].Get<T>();
        }
        template <class T> static bool Exists(const std::string& name)
        {
            return assetsData.Assets.find(name) != assetsData.Assets.end();
        }

        template <class T> static void Add(const Ref<T>& asset, const std::string& path, const std::string& name, FilePathType pathType = FilePathType::PROJECT, uint32_t version = 0)
        {
            Asset temp = Asset(asset, path, name, pathType, version);
            assetsData.Assets[name] = temp;
        }

        
    };
    
}
