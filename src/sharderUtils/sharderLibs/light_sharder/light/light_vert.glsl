#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;

void main()
{
    // 矩阵乘法需要从右往左
    gl_Position = perspective * view * model * vec4(aPos, 1.0f);
}