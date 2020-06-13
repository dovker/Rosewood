#pragma once


namespace Rosewood
{
	class Texture
	{
    public:
        // the program ID
        
        Texture();
        Texture(const std::string& path);
        Texture(uint32_t width, uint32_t height);
        
        
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual uint32_t GetID() const = 0;

        virtual void SetData(void* data, uint32_t size) const = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;
	};

}
