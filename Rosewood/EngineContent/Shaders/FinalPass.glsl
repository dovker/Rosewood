#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;


out vec2 TexCoords;

void main()
{
    //TexCoords = vec2(0.5*(1+aPos.x), 0.5*(1+aPos.y));
    TexCoords = aTexCoords;
    gl_Position = vec4(aPos, 1.0);
}

#shader fragment
#version 330 core


out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gLight;
uniform sampler2D gAlbedoSpec;
uniform vec3 u_Ambient;
uniform float u_Exposure;


void main()
{
    const float gamma = 2.2;

    //FragColor = vec4(1.0f);
    vec3 Light = texture(gLight, TexCoords).rgb;
    vec3 Albedo = texture(gAlbedoSpec, TexCoords).rgb;
    vec3 color = vec3(Albedo * u_Ambient + Albedo * Light);
    
    vec3 mapped = vec3(1.0) - exp(-color * u_Exposure);
      // gamma correction
    mapped = pow(mapped, vec3(1.0 / gamma));
    
    FragColor = vec4(mapped, 1.0);
}
