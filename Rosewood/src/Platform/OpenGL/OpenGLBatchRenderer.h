#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Platform\OpenGL\Shader.h>
#include <Platform\OpenGL\Texture.h>
#include <glad/glad.h>
//#include <Platform\OpenGL\Mesh.h>
#include <Rosewood/Camera.h>

namespace Rosewood
{
    struct QuadVertex {
        glm::vec3 Position;
        // normal
        glm::vec3 Normal;
        // texCoords
        glm::vec2 TexCoords;
        // tex index
        float TexIndex;

        Vertex::Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex, float texInd)
            : Position(pos), Normal(norm), TexCoords(tex), TexIndex(texInd)
        {}
    };
    class BatchRenderer
    {
    public:
        
        Shader defaultShader;

        void BatchRenderer::Begin(OrthographicCamera& camera);
        void BatchRenderer::End();

        void BatchRenderer::SetTexture(Texture* texture);

        void BatchRenderer::DrawQuad(glm::vec2 pos, Texture* texture, glm::vec4 uv, glm::vec4 color);

    private:
        std::vector<QuadVertex> vertices;
        std::vector<unsigned int> indices;
        unsigned int VAO, VBO, EBO;

        unsigned int m_CurrentTexIndex;
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
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(QuadVertex), &vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

            // set the vertex attribute pointers
            // vertex Positions
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)0);
            // vertex normals
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)offsetof(QuadVertex, Normal));
            // vertex texture coords
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)offsetof(QuadVertex, TexCoords));
            //vertex texture index coords
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)offsetof(QuadVertex, TexCoords, TexIndex));

            glBindVertexArray(0);
        }
    };
}