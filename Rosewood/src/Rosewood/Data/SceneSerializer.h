#pragma once
#include "Rosewood/ECS/Scene.h"
#include "Rosewood/Core/Core.h"

namespace Rosewood
{
    class SceneSerializer
    {
    public:
        SceneSerializer(Ref<Scene> scene)
            : m_Scene(scene) {}
        
        std::string Serialize();
        void Deserialize(const std::string& data);
        
    private:
        Ref<Scene> m_Scene;
    };
}