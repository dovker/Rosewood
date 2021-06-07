#pragma once
#include "Rosewood/Files/File.h"
#include "Rosewood/Assets/Asset.h"

namespace Rosewood
{
	class Texture
	{
    public:
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual uint32_t GetID() const = 0;
        virtual std::string& GetPath() = 0;

        virtual void SetData(void* data, uint32_t size) = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;
        
        virtual bool operator==(const Texture& other) const = 0;

        static AssetType GetAssetType() { return AssetType::Texture; }
        
        static Ref<Texture> Create(const std::string& path);
        static Ref<Texture> Create(const BinaryFile& file);
        static Ref<Texture> Create(uint32_t width, uint32_t height);
	};

}
