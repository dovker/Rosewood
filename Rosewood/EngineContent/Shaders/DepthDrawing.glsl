#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

out vec2 TexCoords;

void main()
{
    TexCoords = vec2(aTexCoords.x, 1-aTexCoords.y);
    gl_Position = u_ViewProjection * u_Model * vec4(aPos, 1.0);
    
}

#shader fragment
#version 330 core

in vec2 TexCoords;

uniform sampler2D u_AlbedoTexture;

void main()
{
    gAlbedoSpec = texture(u_AlbedoTexture, TexCoords);
    if(gAlbedoSpec.a == 0.0)
    {
        discard;
    }
    
}


