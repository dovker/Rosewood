#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec4 PositionCS;
out vec4 PositionVS;


void main()
{
    PositionVS = u_View * u_Model * vec4(aPos, 1.0);
    PositionCS = u_Projection * PositionVS;
    gl_Position = PositionCS;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 gLight;

in vec4 PositionCS;
in vec4 PositionVS;

uniform sampler2D gNormal;
uniform sampler2D gDepth;
uniform vec3 u_Size;

struct Decal {
    sampler2D Texture;
    
    vec3 Color;
};

uniform Decal u_Decal;

//Pos is fragment position from gBuffer
uniform mat4 u_InvView;
uniform mat4 u_InvProj;
uniform mat4 u_InvModel;


void main()
{
    
    vec3 ndcPos = PositionCS.xyz / PositionCS.w;

    vec2 texCoord = ndcPos.xy * 0.5 + 0.5;

    float sampledDepth = texture(gDepth, texCoord).r;
    
    float sampleNdcZ = sampledDepth * 2.0 - 1.0;
    
    //if(sampleNdcZ > gl_FragDepth * 2.0 - 1.0) discard;
    
    vec3 ndcSample = vec3(ndcPos.xy, sampleNdcZ);

    
    vec4 hViewPos     = u_InvProj * vec4(ndcSample, 1.0);
    vec3 viewPosition = hViewPos.xyz / hViewPos.w;

    // Transformation from view-space to world-space
    vec3 WorldPos       = (u_InvView * vec4(viewPosition, 1.0)).xyz;
    vec3 objectPosition = (u_InvModel * vec4(WorldPos, 1.0)).xyz;

    // Bounds check, discard pixels outside the wall in object-space
    if (abs(objectPosition.x) > 0.5) discard;
    else if (abs(objectPosition.y) > 0.5) discard;
    else if (abs(objectPosition.z) > 0.5) discard;
    
    //objectPosition.y = 1 - objectPosition.y;
    
    gLight = vec4(texture(u_Decal.Texture, objectPosition.xy + 0.5).xyz * u_Decal.Color, 1.0);
}


