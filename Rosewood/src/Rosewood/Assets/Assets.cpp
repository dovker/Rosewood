#include "rwpch.h"
#include "Assets.h"

namespace Rosewood
{
// // // // //
// // // // //    LOAD
// // // // //
    template <class T>
    Ref<T> AssetManager::Load(const std::string path, const std::string name)
    {
        RW_CORE_ASSERT(false, "FILE TYPE NOT SUPPORTED!!!");
    }

    template <>
    Ref<Texture> AssetManager::Load<Texture>(const std::string path, const std::string name)
    {
        auto ptr = Texture::Create(path);
        m_Textures[name] = ptr;
        return ptr;
    }

    template <>
    Ref<Shader> AssetManager::Load<Shader>(const std::string path, const std::string name)
    {
        auto ptr = Shader::Create(path);
        m_Shaders[name] = ptr;
        return ptr;
    }
    template <>
    Ref<Sound> AssetManager::Load<Sound>(const std::string path, const std::string name)
    {
        auto ptr = Sound::Create(path);
        m_Sounds[name] = ptr;
        return ptr;
    }
    template <>
    Ref<Model> AssetManager::Load<Model>(const std::string path, const std::string name)
    {
        auto ptr = Model::Create(path);
        m_Models[name] = ptr;
        return ptr;
    }
// // // // //
// // // // //    UNLOAD
// // // // //
    template <class T>
    void AssetManager::Unload(const std::string name)
    {
        RW_CORE_ASSERT(false, "FILE TYPE NOT SUPPORTED!!!");
    }

    template <>
    void AssetManager::Unload<Texture>(const std::string name)
    {
        m_Textures[name].reset();
    }

    template <>
    void AssetManager::Unload<Shader>(const std::string name)
    {
        m_Shaders[name].reset();
    }
    template <>
    void AssetManager::Unload<Sound>(const std::string name)
    {
        m_Sounds[name].reset();
    }
// // // // //
// // // // //    ADD
// // // // //
    template <class T>
    void AssetManager::Add(const Ref<T>& Asset, std::string name)
    {
        RW_CORE_ASSERT(false, "FILE TYPE NOT SUPPORTED!!!");
    }

    template <>
    void AssetManager::Add<Texture>(const Ref<Texture>& Asset, std::string name)
    {
        m_Textures[name] = Asset;
    }

    template <>
    void AssetManager::Add<Shader>(const Ref<Shader>& Asset, std::string name)
    {
        m_Shaders[name] = Asset;
    }
    template <>
    void AssetManager::Add<Sound>(const Ref<Sound>& Asset, std::string name)
    {
        m_Sounds[name] = Asset;
    }
    template <>
    void AssetManager::Add<Model>(const Ref<Model>& Asset, std::string name)
    {
        m_Models[name] = Asset;
    }
// // // // //
// // // // //    EXISTS
// // // // //
    template <class T>
    bool AssetManager::Exists(const std::string name)
    {
        RW_CORE_ASSERT(false, "FILE TYPE NOT SUPPORTED!!!");
    }

    template <>
    bool AssetManager::Exists<Texture>(const std::string name)
    {
        return m_Textures.find(name) != m_Textures.end();
    }

    template <>
    bool AssetManager::Exists<Shader>(const std::string name)
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }

    template <>
    bool AssetManager::Exists<Sound>(const std::string name)
    {
        return m_Sounds.find(name) != m_Sounds.end();
    }
    template <>
    bool AssetManager::Exists<Model>(const std::string name)
    {
        return m_Models.find(name) != m_Models.end();
    }
// // // // //
// // // // //    GET
// // // // //
    template <class T>
    Ref<T> AssetManager::Get(const std::string name)
    {
        RW_CORE_ASSERT(false, "FILE TYPE NOT SUPPORTED!!!");
    }

    template <>
    Ref<Texture> AssetManager::Get<Texture>(const std::string name)
    {
        RW_CORE_ASSERT(Exists<Texture>(name), "Texture {0} not found", name);
        return m_Textures[name];
    }

    template <>
    Ref<Shader> AssetManager::Get<Shader>(const std::string name)
    {
        RW_CORE_ASSERT(Exists<Shader>(name), "Shader {0} not found", name);
        return m_Shaders[name];
    }
    
    template <>
    Ref<Sound> AssetManager::Get<Sound>(const std::string name)
    {
        RW_CORE_ASSERT(Exists<Sound>(name), "Shader {0} not found", name);
        return m_Sounds[name];
    }
    template <>
    Ref<Model> AssetManager::Get<Model>(const std::string name)
    {
        RW_CORE_ASSERT(Exists<Model>(name), "Shader {0} not found", name);
        return m_Models[name];
    }
}
