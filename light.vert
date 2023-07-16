#version 330 core

layout (location = 0) in vec3 aPos;

uniform float scale;

uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
    gl_Position = camMatrix * model * vec4(scale * aPos.x, scale * aPos.y, scale * aPos.z, 1.0);

}
