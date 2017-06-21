
#version 150 core
out vec4 FragColor;

in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCoord) ;
//    FragColor = vec4(1.f,0.3f, 0.3f, 1.f );
}
