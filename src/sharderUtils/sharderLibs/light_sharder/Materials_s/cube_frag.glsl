#version 330 core
struct Material {
    vec3 ambient;    // 环境光
    vec3 diffuse;    // 漫反射
    vec3 specular;   // 镜面强度
    float shininess;  // 反光度
};

struct Light {
    vec3 position;

    vec3 ambient; // 环境光
    vec3 diffuse; // 漫反射
    vec3 specular; // 镜面反射
};

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
uniform vec3 lightColor;  // 此时的lightColor的强度为vec3(1.0) 应该适当缩减lightColor的强度(light_frag)
uniform vec3 objColor;
uniform vec3 viewPos; // 摄像机坐标
uniform Material material;
uniform Light light;

void main()
{
    // 材质光
    vec3 ambient = material.ambient * light.ambient;

    // 漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    // 镜面反射
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    // 镜面反射高光角度
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //GLSL中向量间的*运算符指的是分量之间相乘（和向量间加法类似），不是点乘也不是矩阵乘法。只有与矩阵相关的一些*运算才定义为矩阵乘法。如果要点乘的话可以使用dot(v1,v2)。
    vec3 specular = light.specular * (material.specular * spec);

    vec3 result = ambient + diffuse + specular ;
    FragColor = vec4(result, 1.0);
}