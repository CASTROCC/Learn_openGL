#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;  // 纹理数据自动载入到glsl ? glUniform只会设置纹理的位置值？

void main()
{
   // FragColor = texture(ourTexture, TexCoord);
   FragColor = texture(ourTexture, TexCoord) * vec4( vec3(1.0f, 1.0f, 1.0f ), 1.0);  //把纹理颜色与顶点颜色在片段着色器中相乘来混合二者的颜色：
}