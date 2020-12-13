#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 offset;
uniform vec4 color;

out vec4 particleColor;

void main()
{
    float scale = 10.0f;
    particleColor = color;
//    gl_Position = projection * vec4((vertex * scale) + offset, 0.0, 1.0);
//    gl_Position = projection * view * model * vec4((position * scale) + offset, 0.0, 1.0);
    gl_Position = projection * view * model * vec4(offset,1.0);
//    gl_Position = projection * view * vec4(offset,1.0);
}
