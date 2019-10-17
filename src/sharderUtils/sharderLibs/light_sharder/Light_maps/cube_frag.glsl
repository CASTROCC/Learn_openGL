#version 330 core
struct Material {
    vec3 ambient;    // 环境光
    vec3 diffuse;    // 漫反射
    vec3 specular;   // 镜面强度
    float shininess;  // 反光度

    sampler2D lightMap; // 漫反射贴图 使用texure像素颜色替换自定义mateial.color
    sampler2D specMap; // 镜面光贴图
    sampler2D rayMap; // 放射光贴图
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
in vec2 TexCoords;

uniform vec3 lightColor;  // 此时的lightColor的强度为vec3(1.0) 应该适当缩减lightColor的强度(light_frag)
uniform vec3 objColor;
uniform vec3 viewPos; // 摄像机坐标
uniform Material material;
uniform Light light;


void main()
{
    // 材质光
    vec3 ambient = vec3(texture(material.lightMap, TexCoords)) * light.ambient;

    // 漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.lightMap, TexCoords));

    // 镜面反射
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    // 镜面反射高光角度
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //GLSL中向量间的*运算符指的是分量之间相乘（和向量间加法类似），不是点乘也不是矩阵乘法。只有与矩阵相关的一些*运算才定义为矩阵乘法。如果要点乘的话可以使用dot(v1,v2)。
    vec3 specular = light.specular * (vec3(texture(material.specMap, TexCoords)) * spec);  // 使用镜面光贴图达到想要的像素颜色
    //vec3 specular = light.specular * spec * (vec3(1.0) - vec3(texture(material.specMap, TexCoords)));

    // vec3 rayLight = texture(material.rayMap, TexCoords).rgb;  // 放射贴图，可不依赖光源自行发光的贴图

    vec3 result = ambient + diffuse + specular ;
    FragColor = vec4(result, 1.0);
}