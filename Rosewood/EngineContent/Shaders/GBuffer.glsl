#shader vertex
#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 0) in vec3 a_Normal;
layout (location = 0) in vec3 a_Tangent;
layout (location = 0) in vec3 a_Bitangent;
layout (location = 0) in vec3 a_TexCoords;


//Use a struct for vertext outputs
out vec4 FragPos;
out vec2 TexCoords;
out mat3 TBN;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main()
{
    vec4 worldPos = u_Model * vec4(aPos, 1.0);
    FragPos = worldPos;
    
    
    TexCoords = vec2(aTexCoords.x, aTexCoords.y);
    
    vec3 T = normalize(vec3(u_Model * vec4(a_Tangent,   0.0)));
    vec3 B = normalize(vec3(u_Model * vec4(a_Bitangent, 0.0)));
    vec3 N = normalize(vec3(u_Model * vec4(a_Normal,    0.0)));
    
    TBN = mat3(T, B, N);
    
    gl_Position = u_ViewProjection * worldPos;
}


#shader fragment
#version 330 core



layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gAlbedo;
layout (location = 2) out vec4 gNormal;
layout (location = 3) out vec4 gMetalicRoughAO;
layout (location = 4) out vec4 gEmissive;


in vec4 FragPos;
in vec2 TexCoords;
in mat3 TBN;

uniform vec4 u_Albedo;
uniform float u_Metalic;
uniform float u_Roughness;
uniform vec4 u_Emissive;

uniform sampler2D u_AlbedoTexture;
uniform sampler2D u_NormalTexture;
uniform sampler2D u_MetalicTexture;
uniform sampler2D u_RoughnessTexture;
uniform sampler2D u_AmbientTexture;
uniform sampler2D u_EmissiveTexture; //MATERIAL STRUCTS


void main()
{
    gPosition = FragPos;
    gAlbedo = texture(u_AlbedoTexture, TexCoords) * u_Albedo;
//    if(gAlbedoSpec.a == 0.0)
//    {
//        discard;
//    }
    
    vec3 TempNormal = texture(u_NormalTexture, TexCoords);
    TempNormal = TempNormal * 2.0 - 1.0;
    TempNormal = normalize(TBN * TempNormal);
    gNormal.rgb = TempNormal;
    
    gMetalicRoughAO.r = texture(u_MetalicTexture, TexCoords) * u_Metalic;
    gMetalicRoughAO.g = texture(u_RoughnessTexture, TexCoords) * u_Roughness;
    gMetalicRoughAO.b = texture(u_AmbientTexture, TexCoords); // Think about if I even need this bc I will be doing ssao
    gEmissive = texture(u_EmissiveTexture, TexCoords) * u_Emissive;

}

