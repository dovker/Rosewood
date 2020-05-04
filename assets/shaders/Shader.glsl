#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 Normal;
out vec3 FragPos;  
out vec2 TexCoords; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    //ppColor = aColor;
    TexCoords = aTexCoords;
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
}


#shader fragment
#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;  
in vec2 TexCoords; 


uniform sampler2D meshTexture;

void main()
{
    
    //vec3 norm = normalize(Normal);
    //vec3 viewDir = normalize(viewPos - FragPos);

    // phase 1: Directional lighting
    //vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // phase 2: Point lights
    //for(int i = 0; i < NR_POINT_LIGHTS; i++)
    //    result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
    // phase 3: Spot light
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    
    //vec4 color = texture(meshTexture, TexCoords);
    
    vec4 color = vec4(Normal ,1.0);
    //FragColor = texture(meshTexture, TexCoords);
    FragColor = color;
    
}
