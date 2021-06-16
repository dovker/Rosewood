#pragma once
#include "rwpch.h"
#include "Rosewood/Files/FileSystem.h"

namespace Rosewood {
    
    class AssetLoader
    {
    public:
        static void LoadAssets(const std::string& packageDescriptorPath, bool archive = false);
        //static void LoadPackage(const std::string& packageDescriptorPath);

        static void ExportAssetIndex(const std::string& path, FilePathType type = FilePathType::PROJECT);
        //static TextFile ExportAssetIndex();

    };
}


/*
Package creation tool will be made later, all of the asset info will be taken from Asset_index
Engine Assets will have a separate package info bool, which says that it's engine content
Assets will be loaded from Asset_index if the packages are not compressed, otherwise 
The packages will go through each file, pulling it and check the path. If it matches some asset
in the Asset_index, it will use that.

Problems: 
- Loading / reloading / unloading assets mid-game for performance
- Reaching specific files in an archive
- Loading files asynchronously

Maybe I should use Json for this and leave YAML for Configurations?


Class is static, therefore you need to deserialize to gain data

How do I do references with them being different types??

Maybe put it all into Assets class
And then add Export function
Maybe just keep MetaData vector and add to it whenever you please and then export metadata instead of assets
Ching ching!!


ImportPacked
{
    name = ZipGetCurrentFilename
    metadata = deserialize(Yaml::find(name))
    std::vector<byte> file;


}

ImportRaw(vector file, metadata meta)
{
    switch(meta.type)
    {

    }
}

*/