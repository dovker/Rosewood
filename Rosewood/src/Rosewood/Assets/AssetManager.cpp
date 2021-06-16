#include "rwpch.h"
#include "AssetManager.h"
namespace Rosewood
{
    AssetsData AssetManager::assetsData = AssetsData();

    Asset AssetManager::GetAsset(const std::string& name)
    {
        RW_CORE_ASSERT(Exists(name), "{0} not found", name);
        return assetsData.Assets[name];
    }
    std::unordered_map<std::string, Asset> AssetManager::GetAssets()
    {
        return assetsData.Assets;
    }
    void AssetManager::Add(const Asset& asset)
    {
        assetsData.Assets[asset.GetName()] = asset;
    }
    bool AssetManager::Exists(const std::string& name)
    {
        return assetsData.Assets.find(name) != assetsData.Assets.end();
    }
}
