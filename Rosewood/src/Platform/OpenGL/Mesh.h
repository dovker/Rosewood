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
        Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex)
            : Position(pos), Normal(norm), TexCoords(tex)
        {}
    };

    

    class Mesh {
    public:
        /*  Mesh Data  */
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        Texture* texture;
        /*  Functions  */
        //Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
        
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture* texture)
        {
            this->vertices = vertices;
            this->indices = indices;
            this->texture = texture;

            setupMesh();
        }

        void Draw(Shader shader)
        {
            //glActiveTexture(GL_TEXTURE0);
            texture->Bind();
            
            shader.setInt("meshTexture", 0);
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

        void setupMesh()
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