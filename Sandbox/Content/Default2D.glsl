#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 0) in vec2 aTex;



void main()
{
    
    //ppColor = aColor;
    //Normal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = vec4(aPos, 1.0);
    //gl_Position = vec4(aPos, 1.0);
}


#shader fragment
#version 330 core

out vec4 FragColor;


void main()
{
    //check if the If statements are needed because wtf cherno
    
    FragColor = vec4(1.0, 1.0, 0.0, 1.0);

}
