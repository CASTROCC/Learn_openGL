#version 330 core

out vec4 FragColor;
struct Material {
    sampler2D diffuse;  // 漫反射贴图
    sampler2D specular;  // 镜面光贴图

    float shininess; // 反光度
};

struct DirLight {
    vec3 direction;

    vec3 ambient;  // 环境光
    vec3 diffuse;  // 漫反色
    vec3 specular; // 镜面反射
};

struct PointLight {
    vec3 position; // 点光源位置

    float constant; // 衰减常量
    float linear; // 衰减一次项
    float quadratic; // 衰减二次项

    vec3 ambient;  // 光源与材质混合的环境光参数
    vec3 diffuse;  // 光源与材质混合的漫反射参数
    vec3 specular; // 光源与材质混合的环境光反射参数

};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define POINT_LIGHT_NUMS 4 // 点光源数量

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform SpotLight spotLight;
uniform PointLight PointLights[POINT_LIGHT_NUMS];

vec3 CreateDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CreatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CreateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos); // 指的是射向viewPos的向量

    // 定向光源
    vec3 dirLight = CreateDirLight(dirLight, norm, viewDir);

    for (int i = 0; i < POINT_LIGHT_NUMS; ++i) {
        dirLight += CreatePointLight(PointLights[i], norm, FragPos, viewDir);
    }
    dirLight += CreateSpotLight(spotLight, norm, FragPos, viewDir);
    FragColor = vec4(dirLight, 1.0);
}

// 生成定向光源
vec3 CreateDirLight(DirLight light, vec3 normal, vec3 viewDir) {

    vec3 lightDir = normalize(-light.direction);
    // 漫反射
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面反射
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 合成结果
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

// 生成点光源
vec3 CreatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // 漫反射
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面反射
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // 弱光值
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // 合并计算结果
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// 生成聚光
vec3 CreateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // 设置光弱化
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}



