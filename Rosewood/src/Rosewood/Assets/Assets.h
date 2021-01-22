#pragma once
#include "rwpch.h"
#include "Rosewood/Graphics/API/Texture.h"
#include "Rosewood/Graphics/API/Shader.h"
#include "Rosewood/Audio/Audio.h"
#include "Rosewood/Graphics/3D/Model.h"


namespace Rosewood {
    class AssetManager
    {
    public:
        AssetManager(){};
        ~AssetManager(){};
        template <class T>
        Ref<T> Load(const std::string path, const std::string name);
        template <class T>
        void Unload(const std::string name); // Split between different assets with <Texture> and so on
        template <class T>
        Ref<T> Get(const std::string name);
        
        template <class T>
        bool Exists(const std::string name);

        template <class T>
        void Add(const Ref<T>& Asset, std::string name);
        
    private:
        std::unordered_map<std::string, Ref<Texture>> m_Textures;
        std::unordered_map<std::string, Ref<Shader>>  m_Shaders;
        std::unordered_map<std::string, Ref<Sound>>  m_Sounds;
        std::unordered_map<std::string, Ref<Model>> m_Models;

    };
    
}
