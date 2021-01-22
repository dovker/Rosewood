#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 a_TexCoords;

out vec4 FragPos;

void main()
{
    FragPos = vec4(aPos, 1.0);
    gl_Position =  FragPos;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 gLight;

in vec4 FragPos;

uniform sampler2D gDepth;

uniform sampler2D decalDepth;

uniform vec3 u_Size;

struct Decal {
    sampler2D Texture;
    
    vec3 Color;
};

uniform Decal u_Decal;

uniform mat4 u_InvView;
uniform mat4 u_InvProj;

uniform mat4 u_DecalViewProj;

void main()
{
    vec3 ndcPos = FragPos.xyz / FragPos.w;
    
    vec2 texCoord = ndcPos.xy * 0.5 + 0.5;

    float sampledDepth = texture(gDepth, texCoord).r;
    
    float sampleNdcZ = sampledDepth * 2.0 - 1.0;


    vec3 ndcSample = vec3(ndcPos.xy, sampleNdcZ);

    
    vec4 hViewPos     = u_InvProj * vec4(ndcSample, 1.0);
    vec3 viewPosition = hViewPos.xyz / hViewPos.w;

    // Transformation from view-space to world-space
    vec3 WorldPos       = (u_InvView * vec4(viewPosition, 1.0)).xyz;
    //vec3 objectPosition = (u_InvModel * vec4(WorldPos, 1.0)).xyz;
    
    
    vec4 texPosition = u_DecalViewProj * vec4(WorldPos, 1.0);
    
    vec3 projectTexCoord;
    projectTexCoord = texPosition.xyz * 0.5 + 0.5;
    
    float closestDepth = texture(decalDepth, projectTexCoord.xy).r;
    
    float bias = 0.00005;
    float shadow = projectTexCoord.z - bias > closestDepth  ? 0.0 : 1.0;

    
    if((clamp(projectTexCoord.x, 0.0, 1.0) == projectTexCoord.x) && (clamp(projectTexCoord.y, 0.0, 1.0) == projectTexCoord.y))
    {
        gLight = vec4(texture(u_Decal.Texture, projectTexCoord.xy).xyz * u_Decal.Color * shadow, 1.0);
    }

}


