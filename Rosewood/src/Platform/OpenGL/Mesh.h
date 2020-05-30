#pragma once
#include <rwpch.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Platform\OpenGL\Shader.h>
#include <Platform\OpenGL\Texture.h>
#include <glad/glad.h>

namespace Rosewood
{
    struct Vertex {
        glm::vec3 Position;
        // normal
        glm::vec3 Normal;
        // texCoords
        glm::vec2 TexCoords;
        Vertex::Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex)
            : Position(pos), Normal(norm), TexCoords(tex)
        {}
    };

    enum Orientation
    {
        Up,
        Down,
        Left,
        Right,
        Front,
        Back
    };

    class Mesh {
    public:
        /*  Mesh Data  */
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        Texture* texture;
        /*  Functions  */
        //Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
        Mesh::Mesh()
        {
        }
        Mesh::Mesh(Texture* texture)
        {
            this->texture = texture;
        }
        void Mesh::SetupMesh() { setupMesh(); }
        Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture* texture)
        {
            this->vertices = vertices;
            this->indices = indices;
            this->texture = texture;

            setupMesh();
        }
        void Mesh::AddQuad(glm::vec3 pos, Rosewood::Orientation orient, glm::vec2 uv0, glm::vec2 uv1)
        {
            size_t vecBack = vertices.size();
            
            glm::vec3 norm;
            switch (orient) {
            case Up:
                norm = glm::vec3(0.0f, 1.0f, 0.0f);
                vertices.push_back(Vertex(pos + glm::vec3(0.0f, 1.0f,  0.0f), norm, uv0));
                vertices.push_back(Vertex(pos + glm::vec3(0.0f, 1.0f, -1.0f), norm, glm::vec2(uv0.x, uv1.y)));
                vertices.push_back(Vertex(pos + glm::vec3(1.0f, 1.0f, -1.0f), norm, uv1));
                vertices.push_back(Vertex(pos + glm::vec3(1.0f, 1.0f,  0.0f), norm, glm::vec2(uv1.x, uv0.y)));
                break;
            case Down: 
                norm = glm::vec3(0.0f, -1.0f, 0.0f);
                vertices.push_back(Vertex(pos + glm::vec3(1.0f, 0.0f, 0.0f), norm, uv0));
                vertices.push_back(Vertex(pos + glm::vec3(1.0f, 0.0f, -1.0f), norm, glm::vec2(uv0.x, uv1.y)));
                vertices.push_back(Vertex(pos + glm::vec3(0.0f, 0.0f, -1.0f), norm, uv1));
                vertices.push_back(Vertex(pos + glm::vec3(0.0f, 0.0f, 0.0f), norm, glm::vec2(uv1.x, uv0.y)));
                break;
            case Left: 
                norm = glm::vec3(-1.0f, 0.0f, 0.0f);
                vertices.push_back(Vertex(pos + glm::vec3(0.0f, 0.0f, -1.0f), norm, uv0));
                vertices.push_back(Vertex(pos + glm::vec3(0.0f, 1.0f, -1.0f), norm, glm::vec2(uv0.x, uv1.y)));
                vertices.push_back(Vertex(pos + glm::vec3(0.0f, 1.0f, 0.0f), norm, uv1));
                vertices.push_back(Vertex(pos + glm::vec3(0.0f, 0.0f, 0.0f), norm, glm::vec2(uv1.x, uv0.y)));
                break;
            case Right:
                norm = glm::vec3(1.0f, 0.0f, 0.0f);
                vertices.push_back(Vertex(pos + glm::vec3(1.0f, 0.0f, 0.0f), norm, uv0));
                vertices.push_back(Vertex(pos + glm::vec3(1.0f, 1.0f, 0.0f), norm, glm::vec2(uv0.x, uv1.y)));
                vertices.push_back(Vertex(pos + glm::vec3(1.0f, 1.0f, -1.0f), norm, uv1));
                vertices.push_back(Vertex(pos + glm::vec3(1.0f, 0.0f, -1.0f), norm, glm::vec2(uv1.x, uv0.y)));
                break;
            case Front: 
                norm = glm::vec3(0.0f, 0.0f, -1.0f);
                vertices.push_back(Vertex(pos + glm::vec3(1.0f, 0.0f, -1.0f), norm, uv0));
                vertices.push_back(Vertex(pos + glm::vec3(1.0f, 1.0f, -1.0f), norm, glm::vec2(uv0.x, uv1.y)));
                vertices.push_back(Vertex(pos + glm::vec3(0.0f, 1.0f, -1.0f), norm, uv1));
                vertices.push_back(Vertex(pos + glm::vec3(0.0f, 0.0f, -1.0f), norm, glm::vec2(uv1.x, uv0.y)));
                break;
            case Back:
                norm = glm::vec3(0.0f, 0.0f, 1.0f); 
                vertices.push_back(Vertex(pos + glm::vec3(0.0f, 0.0f, 0.0f), norm, uv0));
                vertices.push_back(Vertex(pos + glm::vec3(0.0f, 1.0f, 0.0f), norm, glm::vec2(uv0.x, uv1.y)));
                vertices.push_back(Vertex(pos + glm::vec3(1.0f, 1.0f, 0.0f), norm, uv1));
                vertices.push_back(Vertex(pos + glm::vec3(1.0f, 0.0f, 0.0f), norm, glm::vec2(uv1.x, uv0.y)));
                break;
            }
            
            indices.push_back(vecBack + 0);
            indices.push_back(vecBack + 1);
            indices.push_back(vecBack + 2);
            indices.push_back(vecBack + 2);
            indices.push_back(vecBack + 3);
            indices.push_back(vecBack + 0);
          
        }
        static void Mesh::AddQuad(std::vector<unsigned int>* indices, std::vector<Vertex>* vertices, glm::vec3 pos, Rosewood::Orientation orient, glm::vec2 uv0, glm::vec2 uv1)
        {
            size_t vecBack = vertices->size();

            glm::vec3 norm;
            switch (orient) {
            case Up:
                norm = glm::vec3(0.0f, 1.0f, 0.0f);
                vertices->push_back(Vertex(pos + glm::vec3(0.0f, 1.0f, 0.0f), norm, uv0));
                vertices->push_back(Vertex(pos + glm::vec3(0.0f, 1.0f, -1.0f), norm, glm::vec2(uv0.x, uv1.y)));
                vertices->push_back(Vertex(pos + glm::vec3(1.0f, 1.0f, -1.0f), norm, uv1));
                vertices->push_back(Vertex(pos + glm::vec3(1.0f, 1.0f, 0.0f), norm, glm::vec2(uv1.x, uv0.y)));
                break;
            case Down:
                norm = glm::vec3(0.0f, -1.0f, 0.0f);
                vertices->push_back(Vertex(pos + glm::vec3(1.0f, 0.0f, 0.0f), norm, uv0));
                vertices->push_back(Vertex(pos + glm::vec3(1.0f, 0.0f, -1.0f), norm, glm::vec2(uv0.x, uv1.y)));
                vertices->push_back(Vertex(pos + glm::vec3(0.0f, 0.0f, -1.0f), norm, uv1));
                vertices->push_back(Vertex(pos + glm::vec3(0.0f, 0.0f, 0.0f), norm, glm::vec2(uv1.x, uv0.y)));
                break;
            case Left:
                norm = glm::vec3(-1.0f, 0.0f, 0.0f);
                vertices->push_back(Vertex(pos + glm::vec3(0.0f, 0.0f, -1.0f), norm, uv0));
                vertices->push_back(Vertex(pos + glm::vec3(0.0f, 1.0f, -1.0f), norm, glm::vec2(uv0.x, uv1.y)));
                vertices->push_back(Vertex(pos + glm::vec3(0.0f, 1.0f, 0.0f), norm, uv1));
                vertices->push_back(Vertex(pos + glm::vec3(0.0f, 0.0f, 0.0f), norm, glm::vec2(uv1.x, uv0.y)));
                break;
            case Right:
                norm = glm::vec3(1.0f, 0.0f, 0.0f);
                vertices->push_back(Vertex(pos + glm::vec3(1.0f, 0.0f, 0.0f), norm, uv0));
                vertices->push_back(Vertex(pos + glm::vec3(1.0f, 1.0f, 0.0f), norm, glm::vec2(uv0.x, uv1.y)));
                vertices->push_back(Vertex(pos + glm::vec3(1.0f, 1.0f, -1.0f), norm, uv1));
                vertices->push_back(Vertex(pos + glm::vec3(1.0f, 0.0f, -1.0f), norm, glm::vec2(uv1.x, uv0.y)));
                break;
            case Front:
                norm = glm::vec3(0.0f, 0.0f, -1.0f);
                vertices->push_back(Vertex(pos + glm::vec3(1.0f, 0.0f, -1.0f), norm, uv0));
                vertices->push_back(Vertex(pos + glm::vec3(1.0f, 1.0f, -1.0f), norm, glm::vec2(uv0.x, uv1.y)));
                vertices->push_back(Vertex(pos + glm::vec3(0.0f, 1.0f, -1.0f), norm, uv1));
                vertices->push_back(Vertex(pos + glm::vec3(0.0f, 0.0f, -1.0f), norm, glm::vec2(uv1.x, uv0.y)));
                break;
            case Back:
                norm = glm::vec3(0.0f, 0.0f, 1.0f);
                vertices->push_back(Vertex(pos + glm::vec3(0.0f, 0.0f, 0.0f), norm, uv0));
                vertices->push_back(Vertex(pos + glm::vec3(0.0f, 1.0f, 0.0f), norm, glm::vec2(uv0.x, uv1.y)));
                vertices->push_back(Vertex(pos + glm::vec3(1.0f, 1.0f, 0.0f), norm, uv1));
                vertices->push_back(Vertex(pos + glm::vec3(1.0f, 0.0f, 0.0f), norm, glm::vec2(uv1.x, uv0.y)));
                break;
            }

            indices->push_back(vecBack + 0);
            indices->push_back(vecBack + 1);
            indices->push_back(vecBack + 2);
            indices->push_back(vecBack + 2);
            indices->push_back(vecBack + 3);
            indices->push_back(vecBack + 0);

        }
        void Mesh::Draw(Shader shader)
        {
            //glActiveTexture(GL_TEXTURE0);
            texture->Bind();
            
            // draw mesh
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            // always good practice to set everything back to defaults once configured.
            //glActiveTexture(GL_TEXTURE0);
        }
        void Mesh::Draw()
        {
            //glActiveTexture(GL_TEXTURE0);
            texture->Bind(0);

            // draw mesh
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            // always good practice to set everything back to defaults once configured.
            //glActiveTexture(GL_TEXTURE0);
        }
    private:
        /*  Render data  */
        unsigned int VAO, VBO, EBO;
        /*  Functions    */

        void Mesh::setupMesh()
        {
            // create buffers/arrays
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);
            // load data into vertex buffers
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            // A great thing about structs is that their memory layout is sequential for all its items.
            // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
            // again translates to 3/2 floats which translates to a byte array.
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

            // set the vertex attribute pointers
            // vertex Positions
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
            // vertex normals
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
            // vertex texture coords
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

            glBindVertexArray(0);
        }

    };
}