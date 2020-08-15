#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;


out vec4 FragPos;
out vec3 Normal;
out vec2 TexCoords; 

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main()
{
    vec4 worldPos = u_Model * vec4(aPos, 1.0);
    FragPos = worldPos;
    
    Normal = mat3(transpose(inverse(u_Model))) * aNormal;
    
    TexCoords = aTexCoords;
    
    gl_Position = u_ViewProjection * worldPos;
    //gl_Position = worldPos;

}


#shader fragment
#version 330 core

#define M_PI 3.1415926535897932384626433832795


layout (location = 0) out vec4 gAlbedoSpec;
layout (location = 1) out vec4 gPosition;
layout (location = 2) out vec4 gNormal;

in vec4 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D u_AlbedoTexture;
uniform sampler2D u_NormalTexture;
uniform sampler2D u_SpecularTexture;


void main()
{
    gAlbedoSpec = texture(u_AlbedoTexture, TexCoords);
    if(gAlbedoSpec.a == 0.0)
    {
        discard;
    }
    gAlbedoSpec.a = texture(u_SpecularTexture, TexCoords).r;
    gPosition = FragPos;
    
    vec4 TempNormal = texture(u_NormalTexture, TexCoords);
    TempNormal = normalize(TempNormal * 2.0 - 1.0);
    gNormal = TempNormal;
    //gNormal = vec4(Normal, 1.0);
}
