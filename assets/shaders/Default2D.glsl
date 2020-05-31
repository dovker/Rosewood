#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in float aTexIndex;

out vec3 Normal;
out vec3 FragPos;  
out vec2 TexCoords; 
out float TexIndex; 


uniform mat4 model;
uniform mat4 u_ViewProjection;
//uniform mat4 view;
//uniform mat4 projection;


void main()
{
    
    //ppColor = aColor;
    TexCoords = aTexCoords;
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexIndex = aTexIndex;
    gl_Position = u_ViewProjection * vec4(aPos, 1.0);
}


#shader fragment
#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;  
in vec2 TexCoords; 
in float TexIndex; 

uniform vec4 color;

uniform sampler2D Textures[16];

void main()
{
    //check if the If statements are needed because wtf cherno
    
    FragColor = texture(Textures[int(TexIndex)], TexCoords)*color;
    
    
    
    
}