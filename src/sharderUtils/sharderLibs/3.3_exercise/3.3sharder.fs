#version 330 core
out vec4 FragColor;

in vec3 ourColor;
uniform float offsetColor;
void main()
{
    FragColor = vec4(ourColor.x + offsetColor, ourColor.y + offsetColor, ourColor.z + offsetColor, 1.0);

}