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

uniform sampler2D uBuffer;


void main()
{
    FragColor = vec4(texture(uBuffer, TexCoords), 1.0);
}
