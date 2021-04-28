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
        template <class T> static Ref<T> Load(const std::string path, const std::string name);
        template <class T> static void Unload(const std::string name); // Split between different assets with <Texture> and so on
        template <class T> static Ref<T> Get(const std::string name);
        template <class T> static bool Exists(const std::string name);
        template <class T> static void Add(const Ref<T>& Asset, std::string name);
        
        static void CheckChanges();
        static int ReloadSeconds;

    };
    
}
