#include "rwpch.h"

#include "Model.h"
#include "Mesh.h"
#include "Rosewood/Graphics/Graphics.h"
#include "Rosewood/Core/Application.h"




namespace Rosewood
{
    void Model::loadModel(const std::string &path)
    {
        Assimp::Importer import;
        const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);
        
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            RW_ERROR("ASSIMP : {0}", import.GetErrorString());
            return;
        }
        
        m_Path = path.substr(0, path.find_last_of('/'));

        processNode(scene->mRootNode, scene);
        
    }
    void Model::processNode(aiNode *node, const aiScene *scene)
    {
        // process all the node's meshes (if any)
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            m_Meshes.push_back(processMesh(mesh, scene));
        }
        // then do the same for each of its children
        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }
    Ref<Mesh> Model::processMesh(aiMesh *mesh, const aiScene *scene) {
        std::vector<float> vertices;
        std::vector<uint32_t> indices;
        std::vector<Ref<Texture>> textures;


        vertices.reserve(mesh->mNumVertices * (3 + 3 + 3 + 3 + 2));
        
        indices.reserve(mesh->mNumFaces * 3);

        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            glm::vec2 uvCoord;

            if (mesh->mTextureCoords[0]) {
                uvCoord.x = mesh->mTextureCoords[0][i].x;
                uvCoord.y = mesh->mTextureCoords[0][i].y;
            }
            else {
                uvCoord.x = 0.0f;
                uvCoord.y = 0.0f;
            }

            vertices.push_back(mesh->mVertices[i].x);
            vertices.push_back(mesh->mVertices[i].y);
            vertices.push_back(mesh->mVertices[i].z);
            vertices.push_back(mesh->mNormals[i].x);
            vertices.push_back(mesh->mNormals[i].y);
            vertices.push_back(mesh->mNormals[i].z);
            vertices.push_back(mesh->mTangents[i].x);
            vertices.push_back(mesh->mTangents[i].y);
            vertices.push_back(mesh->mTangents[i].z);
            vertices.push_back(mesh->mBitangents[i].x);
            vertices.push_back(mesh->mBitangents[i].y);
            vertices.push_back(mesh->mBitangents[i].z);
            vertices.push_back(uvCoord.x);
            vertices.push_back(uvCoord.y);

        }

        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; ++j) {
                indices.push_back(face.mIndices[j]);
            }
        }
        aiMaterial* materialA = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Ref<Texture>> diffuseMaps = loadMaterialTextures(materialA, aiTextureType_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        
        std::vector<Ref<Texture>> normalMaps = loadMaterialTextures(materialA, aiTextureType_NORMALS);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        
        std::vector<Ref<Texture>> specularMaps = loadMaterialTextures(materialA, aiTextureType_SPECULAR);

        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end()); // Metalic
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end()); // Roughness
        
        std::vector<Ref<Texture>> aoMaps = loadMaterialTextures(materialA, aiTextureType_AMBIENT);
        textures.insert(textures.end(), aoMaps.begin(), aoMaps.end());
        
        std::vector<Ref<Texture>> emissiveMaps = loadMaterialTextures(materialA, aiTextureType_EMISSIVE);
        textures.insert(textures.end(), emissiveMaps.begin(), emissiveMaps.end());
        
        m_Material = Material::Create(nullptr);
        return Mesh::Create(vertices, indices, textures);
    }

    std::vector<Ref<Texture>> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type)
    {
        std::vector<Ref<Texture>> textures;
        for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);

            bool skip = false;
            for(unsigned int j = 0; j < m_LoadedTextures.size(); j++)
            {
                if(std::strcmp(m_LoadedTextures[j]->GetPath().data(), str.C_Str()) == 0)
                {
                    textures.push_back(m_LoadedTextures[j]);
                    skip = true; 
                    break;
                }
            }
            if(!skip)
            {
                std::string fixedPath =  std::string(str.C_Str());
                for (int i = 0; i < fixedPath.length(); ++i) {
                  if (fixedPath[i] == '\\')
                      fixedPath[i] = '/';
                }
                
                Ref<Texture> tex =Texture::Create(m_Path + "/" + fixedPath);
                textures.push_back(tex);
                m_LoadedTextures.push_back(tex);
            }
        }
        if(mat->GetTextureCount(type) == 0)
            textures.push_back(nullptr);
        return textures;
    }

}
