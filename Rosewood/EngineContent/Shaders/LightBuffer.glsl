#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

out vec2 TexCoords;

void main()
{
    vec4 point = u_ViewProjection * u_Model * vec4(aPos, 1.0);
    TexCoords = vec2(0.5*(1+point.x), 0.5*(1 + point.y));
    gl_Position = point;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 gLight;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;

struct Light {
    vec3 Position;
    vec3 Color;
    
    float Intensity;
    
    float Constant;
    float Linear;
    float Quadratic;
};

uniform Light u_Light;

vec3 calculateLight(Light light, vec3 normal, vec3 pos);
//Pos is fragment position from gBuffer

void main()
{
    
    // retrieve data from gbuffer
    vec4 FragPos = texture(gPosition, TexCoords);

    
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    
    
    gLight = vec4(calculateLight(u_Light, Normal, FragPos.rgb), 0.0);
}

vec3 calculateLight(Light light, vec3 normal, vec3 pos)
{
    //normal = vec3(0.0, 0.0, 1.0);
    float dist = length(light.Position - pos);

        // diffuse
    vec3 lightDir = normalize(light.Position - pos);
    vec3 diffuse = max(dot(normal, lightDir), 0.0) * light.Color;

        // attenuation
    float attenuation = 1.0 / (light.Constant + light.Linear * dist + light.Quadratic * dist * dist);
    
    diffuse *= attenuation;
    diffuse *= light.Intensity;
    
    return diffuse;
}
