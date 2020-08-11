#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec4 FragPos;
out vec2 TexCoords; 

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main()
{
    vec4 worldPos = u_Model * vec4(aPos, 1.0);
    FragPos = worldPos;
    
    TexCoords = aTexCoords;
    
    gl_Position = u_ViewProjection * worldPos;
    //gl_Position = worldPos;

}


#shader fragment
#version 330 core

#define M_PI 3.1415926535897932384626433832795


mat4 rotationMatrix(vec3 axis, float angle) {
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    
    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

vec3 rotate(vec3 v, vec3 axis, float angle) {
    mat4 m = rotationMatrix(axis, angle);
    return (m * vec4(v, 1.0)).xyz;
}

layout (location = 0) out vec4 gAlbedoSpec;
layout (location = 1) out vec4 gPosition;
layout (location = 2) out vec4 gNormal;

in vec4 FragPos;
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
    gNormal = texture(u_NormalTexture, TexCoords);
}
