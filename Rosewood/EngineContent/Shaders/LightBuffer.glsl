#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

out vec2 TexCoords;

void main()
{
    vec4 point = u_ViewProjection * u_Model * vec4(aPos, 1.0);
    TexCoords = vec2(0.5*(1+point.x), 0.5*(1 + point.y)); //dunno abt this though
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
    
    float Constant;
    float Linear;
    float Quadratic;
};

uniform Light u_Light;

void main()
{
    
    // retrieve data from gbuffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    
    float dist = length(u_Light.Position - FragPos);

        // diffuse
    vec3 lightDir = normalize(u_Light.Position - FragPos);
    vec3 diffuse = max(dot(Normal, lightDir), 0.0) * u_Light.Color;

        // attenuation
    float attenuation = 1.0 / (u_Light.Constant + u_Light.Linear * dist + u_Light.Quadratic * dist * dist);
    
    diffuse *= attenuation;
    
    gLight = vec4(attenuation);

    
    //gLight = vec4(attenuation);
    //gLight = vec4(TexCoords, 0.0, 1.0);
}
