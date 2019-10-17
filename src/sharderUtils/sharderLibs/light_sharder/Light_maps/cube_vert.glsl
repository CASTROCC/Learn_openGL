#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos; // 其实就是cube在世界空间中的坐标
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  // 防止物体进行不等比缩放， 将法线向量*法线矩阵 (较耗费性能，可以优先用CPU算出法线值，然后通过uniform将值传递给参数)

    gl_Position = perspective * view * vec4(FragPos, 1.0);

    TexCoords = aTexCoords;
    // 也可在vert中进行光照模型计算（Gouraud着色）-> 效果相对片段着色起差， 但性能更好
}