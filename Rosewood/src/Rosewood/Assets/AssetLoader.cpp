#include "rwpch.h"
#include "AssetLoader.h"

#include "AssetManager.h"
#include "AssetTypes.h"
#include "Rosewood/Files/File.h"
#include "Rosewood/Assets/Asset.h"
#include "Rosewood/Graphics/3D/Model.h"
#include "Rosewood/Audio/Audio.h"
#include "Rosewood/Graphics/API/Shader.h"
#include "Rosewood/Graphics/API/Texture.h"

#include "nlohmann/json.hpp"

using nlohmann::json;


namespace Rosewood
{
    AssetType findAssetType(std::string& name)
    {
        for(int i = 0; i < AssetTypeCount; i++)
        {
            if(AssetTypeNames[i] == name)
                return (AssetType)i;
        }
        return AssetType::Undefined;
    }
    std::string findAssetTypeName(AssetType t)
    {
        return AssetTypeNames[(int)t];
    }
    FilePathType findFilePathType(std::string& name)
    {
        for(int i = 0; i < FilePathTypeCount; i++)
        {
            if(FilePathTypeNames[i] == name)
                return (FilePathType)i;
        }
        return FilePathType::PROJECT;
    }
    std::string findFilePathTypeName(FilePathType t)
    {
        return FilePathTypeNames[(int)t];
    }

    //Parse the project File to get folder directories for each thing
    void AssetLoader::LoadAssets(const std::string& packageDescriptorPath, bool archive)
    {
        json j;
        std::ifstream ifs(packageDescriptorPath);
        ifs >> j;

        for ( auto& keyValue : j.items() )
        {
            auto& a = keyValue.value();
            std::string pathType = a["PathType"].get<std::string>();
            std::string assetType = a["AssetType"].get<std::string>();
            Asset asset(a["Path"], keyValue.key(), findFilePathType(pathType), findAssetType(assetType), a["Version"], a["Archived"], a["Compressed"], a["LoadOnInit"]);
            if(asset.GetLoadOnInit())
            {
                switch (asset.GetAssetType())
                {
                case AssetType::Texture:
                    asset.Load<Texture>();
                break;
                case AssetType::Sound:
                    asset.Load<Sound>();
                break;
                case AssetType::Model:
                    asset.Load<Model>();
                break;
                case AssetType::BinaryFile:
                    asset.Load<BinaryFile>();
                break;
                case AssetType::TextFile:
                    asset.Load<TextFile>();
                break;
                case AssetType::Shader:
                    asset.Load<Shader>();
                break;
                
                default:
                    RW_CORE_ERROR("Undefined Asset Type");
                    break;
                }
            }
            AssetManager::Add(asset);
        }
    }
    
    void AssetLoader::ExportAssetIndex(const std::string& path, FilePathType type)
    {
        json j;
        for(auto& asset : AssetManager::GetAssets())
        {
            if(asset.second.GetFilePathType() == type)
            {
                j[asset.first] = json{
                    {"AssetType",   findAssetTypeName(asset.second.GetAssetType())},
                    {"Path",        asset.second.GetPath()},
                    {"PathType",    findFilePathTypeName(asset.second.GetFilePathType())},
                    {"Version",     asset.second.GetVersion()},
                    {"Compressed",  asset.second.GetCompressed()},
                    {"Archived",    asset.second.GetArchived()},
                    {"LoadOnInit",  asset.second.GetLoadOnInit()},
                };
            }
        }

        std::ofstream ofs(path);
        ofs<<std::setw(4)<<j<<std::endl;
    }
}