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

uniform float u_Gamma;
uniform float u_Exposure;

uniform float u_Brightness;
uniform float u_Contrast;
uniform float u_Saturation;
uniform float u_BlackPoint;
uniform float u_WhitePoint;


void main()
{
    //FragColor = vec4(1.0f);
    vec3 Light = texture(gLight, TexCoords).rgb;
    vec3 Albedo = texture(gAlbedoSpec, TexCoords).rgb;
    vec3 Color = vec3(Albedo * u_Ambient + Albedo * Light);
    
    vec3 mapped = vec3(1.0) - exp(-Color * u_Exposure);
      // gamma correction
    mapped = pow(mapped, vec3(1.0 / u_Gamma));
    
    //Brightness pass
    mapped += u_Brightness;
    
    //Contrast Pass
    mapped = ((mapped - 0.5f) * max(u_Contrast, 0)) + 0.5f;
    
    //y = ax + b
    //White Point
    //Black Point
    mapped = mapped * u_WhitePoint * (1 - u_BlackPoint) + u_BlackPoint;
    

    //Saturation Pass
    vec3 luminance = vec3( 0.3086, 0.6094, 0.0820 ); //TODO: ADD SLIDER
    float intensity = dot(mapped, luminance);
    mapped = mix(vec3(intensity), mapped, u_Saturation);
    
    FragColor = vec4(mapped, 1.0);
}
