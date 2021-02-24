#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in float aTexIndex;

out vec4 Color;
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
    FragPos = aPos;
    //Normal = mat3(transpose(inverse(model))) * aNormal;
    Color = aColor;
    TexIndex = aTexIndex;
    gl_Position = u_ViewProjection * vec4(aPos, 1.0);
    //gl_Position = vec4(aPos, 1.0);
}


#shader fragment
#version 330 core

out vec4 FragColor;

in vec4 Color;
in vec3 FragPos;  
in vec2 TexCoords; 
in float TexIndex; 

uniform sampler2D u_Textures[16];

void main()
{
    //check if the If statements are needed because wtf cherno
    
    //FragColor = texture(u_Textures[int(TexIndex)], TexCoords)*Color;
    if (TexIndex == 0.0)
    {
        FragColor = Color;
    } else
    {
        vec4 color = texture(u_Textures[int(TexIndex)], TexCoords) * Color;
        if (color.a == 0.0)
        {discard;}
        FragColor = color;
        //FragColor = texture(u_Textures[0], TexCoords) * Color;
        //FragColor = vec4(TexCoords.x, TexCoords.y, 0.0, 1.0);
    }
    
}
