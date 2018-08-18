#version 330 core
out vec4 outColor;

in vec3 textureCoords;

uniform samplerCube sampler;

void main()
{
    outColor = texture(sampler, textureCoords);
}
