
#version 150 core
in vec3 aPos;
in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4(-aPos, 1.0);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
