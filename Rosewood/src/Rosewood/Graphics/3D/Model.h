#pragma once
#include "rwpch.h"
#include "Rosewood/Core/Core.h"

#include "Rosewood/Graphics/API/Texture.h"
#include "Rosewood/Graphics/API/VertexArray.h"
#include "Rosewood/Graphics/API/Buffer.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Rosewood {
    class Material
    {
    public:
        Ref<Shader> shader;
        glm::vec3 Albedo = {1.0f, 1.0f, 1.0f};
        float Metalicness = 1.0f;
        float Roughness = 1.0f;
        glm::vec3 Emissive = {1.0f, 1.0f, 1.0f};//Do something about HDR colors and Physical intensity. ALSO, ACES TONE THING
        
        //Add Custom Textures that are specific to material that cannot be overriden such as procedural texturing
        //Also add some kind of scripting material-shader-property thing
        
        void SetShader(Ref<Shader> shd) { shader = shd; }
        Material ();
        Material (Ref<Shader> shader)
            : shader(shader)
        {
            
        }

        static Ref<Material> Create(Ref<Shader> shader)
        {
            return CreateRef<Material>(shader);
        }
        void Bind()
        {
            shader->setVec3("u_Albedo", Albedo);
            shader->setFloat("u_Metalic", Metalicness);
            shader->setFloat("u_Roughness", Roughness);
            shader->setVec3("u_Emissive", Emissive);
        }
        void BindPBRMaps(std::vector<Ref<Texture>> textures)
        {
            Bind();
            shader->setInt("u_AlbedoTexture", 0);
            shader->setInt("u_NormalTexture", 1);
            shader->setInt("u_MetalicTexture", 2);
            shader->setInt("u_RoughnessTexture", 3);
            shader->setInt("u_AmbientTexture", 4);
            shader->setInt("u_EmissiveTexture", 5);//UNBINDING TEXTURES???????
            
            for (int i = 0; i < 6; i++)
            {
                GraphicsCommand::BindTexture(textures.at(i) != nullptr ? textures.at(0)->GetID() : 0, i); //Change this
            }
        }
    };
    class Model
    {
    public:
        Model() {}
        Model(const std::string& path)
        {
            loadModel(path);
        }
        static Ref<Model> Create(const std::string& path)
        {
            return CreateRef<Model>(path);
        }
        void SetShader(Ref<Shader> shader) { m_Material->SetShader(shader); }
        Ref<Shader> GetShader() { return m_Material->shader; }
        
        std::vector<Ref<Mesh>> GetMeshes() { return m_Meshes; }
        
        void SetMaterial(Ref<Material> material) { m_Material = material; }
        void BindMaterial() { m_Material->Bind(); }
        void BindMeshTextures(Ref<Mesh> mesh) { m_Material->BindPBRMaps(mesh->textures); }
        
    private:
        std::vector<Ref<Mesh>> m_Meshes;
        Ref<Material> m_Material;
        std::string m_Path;
        std::vector<Ref<Texture>> m_LoadedTextures;
        void loadModel(const std::string& path);
        void processNode(aiNode *node, const aiScene *scene);
        Ref<Mesh> processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Ref<Texture>> loadMaterialTextures(aiMaterial *mat, aiTextureType type);
        
    };
}
