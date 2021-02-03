#shader vertex
#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec3 a_Tangent;
layout (location = 3) in vec3 a_Bitangent;
layout (location = 4) in vec2 a_TexCoords;


//Use a struct for vertext outputs
out vec3 FragPos;
out vec2 TexCoords;
out mat3 TBN;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main()
{
    vec4 worldPos = u_Model * vec4(a_Position, 1.0);
    FragPos = worldPos.rgb;
    
    
    TexCoords = a_TexCoords;
    
    vec3 T = normalize(vec3(u_Model * vec4(a_Tangent,   0.0)));
    vec3 B = normalize(vec3(u_Model * vec4(a_Bitangent, 0.0)));
    vec3 N = normalize(vec3(u_Model * vec4(a_Normal,    0.0)));
    
    TBN = mat3(T, B, N);
    
    gl_Position = u_ViewProjection * worldPos;
}


#shader fragment
#version 330 core



layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gAlbedo;
layout (location = 2) out vec3 gNormal;
layout (location = 3) out vec3 gMetalicRoughAO;
layout (location = 4) out vec3 gEmissive;


in vec3 FragPos;
in vec2 TexCoords;
in mat3 TBN;

uniform vec3 u_Albedo;
uniform float u_Metalic;
uniform float u_Roughness;
uniform vec3 u_Emissive;

uniform sampler2D u_AlbedoTexture;
uniform sampler2D u_NormalTexture;
uniform sampler2D u_MetalicTexture;
uniform sampler2D u_RoughnessTexture;
uniform sampler2D u_AmbientTexture;
uniform sampler2D u_EmissiveTexture; //MATERIAL STRUCTS


void main()
{
    gPosition = FragPos;
    gAlbedo = texture(u_AlbedoTexture, TexCoords).rgb * u_Albedo; //CHANGE TO *
    //gAlbedo = vec4(1.0);
//    if(gAlbedoSpec.a == 0.0)
//    {
//        discard;
//    }
    
    vec3 TempNormal = texture(u_NormalTexture, TexCoords).rgb;
    TempNormal = TempNormal * 2.0 - 1.0;
    TempNormal = normalize(TBN * TempNormal);
    gNormal = TempNormal;
    
    gMetalicRoughAO.r = texture(u_MetalicTexture, TexCoords).r * u_Metalic;
    gMetalicRoughAO.g = texture(u_RoughnessTexture, TexCoords).r * u_Roughness;
    gMetalicRoughAO.b = texture(u_AmbientTexture, TexCoords).r; // Think about if I even need this bc I will be doing ssao
    gEmissive = texture(u_EmissiveTexture, TexCoords).rgb * u_Emissive;

}

