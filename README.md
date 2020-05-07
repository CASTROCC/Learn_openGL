最近在学习openGL[learn-openGL](https://learnopengl-cn.github.io/)相关的一些知识，整理了一些3D方面的知识点，以后没事的时候要多看看~

## 坐标系统
- **标准化设备坐标 （-1, 1); （引擎坐标-> 标准化坐标 -> 屏幕坐标） （标准化坐标转为屏幕坐标位于 视口阶段， 该阶段位于剪裁空间转屏幕空间之间**

### 局部空间 
### 世界空间
### 观察空间 
    lookAt矩阵
### 剪裁空间
### 屏幕空间 
    一个顶点在渲染成屏幕色彩上所经历的所有不同状态

* 模型矩阵 <br>
    本地坐标 转换到 世界坐标
* 观察矩阵 <br>
    世界坐标 转换到 观察坐标
* 投影矩阵 <br>
    观察坐标 转化到 剪裁坐标

投影矩阵会剪裁掉超出（-1，1）这个范围内的标准化坐标。一旦所有顶点被变换到裁剪空间，最终的操作——透视(Perspective Division)将会执行。

* 透视<br>
    将3D裁剪空间坐标变换为3D标准化设备坐标的过程

> 之所以将顶点变换到各个不同的空间的原因是有些操作在特定的坐标系统中才有意义且更方便。例如，当需要对物体进行修改的时候，在局部空间中来操作会更说得通；如果要对一个物体做出一个相对于其它物体位置的操作时，在世界坐标系中来做这个才更说得通，等等。如果我们愿意，我们也可以定义一个直接从局部空间变换到裁剪空间的变换矩阵，但那样会失去很多灵活性。——<a href = "https://learnopengl-cn.github.io">[LearnOpenGL]



### 平截头体
* 正射投影矩阵 <br>
剪裁掉摄像机所在观察箱的 近平面之前的和 远平面之后的所有坐标， 然后使用透视除法将坐标转为标准化坐标， 如果w分量为0则无法原坐标不被标准化） （适用工程 及 建模， 因为模型场景需要真实还原 ）

使用glm的内部函数创建投影矩阵 
``` c
glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f); // 左右 上下 前后
```

* 透视投影矩阵 <br>
    离你越远的物体看起来越小。由于透视，这两条平行线在很远的地方看起来会相交。这正是透视投影想要模仿的效果，它是使用透视投影矩阵来完成的

    ![透视投影](https://learnopengl-cn.github.io/img/01/08/perspective_frustum.png)

> 投影矩阵将给定的平截头体范围映射到裁剪空间，除此之外还修改了每个顶点坐标的w值，从而使得离观察者越远的顶点坐标w分量越大（因为w坐标为被除数， 顶点坐标的每个分量都会除以它的w分量，距离观察者越远（w越大）顶点坐标就会越小）

使用glm的内部函数创建透视投影矩阵 
``` c
glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f); // 视口 宽高比 近平面 远平面
```

## 摄像机
> OPENGL本身没有摄像机的概念，但是可以将场景中的所有物体沿反方向移动模拟出摄像机的效果。当我们讨论摄像机/观察空间(Camera/View Space)的时候，是在讨论以摄像机的视角作为场景原点时场景中所有模型的顶点坐标。观察矩阵把所有的世界坐标变换为相对于摄像机位置与方向的观察坐标。

![观察空间](https://learnopengl-cn.github.io/img/01/09/camera_axes.png)

### 定义摄像机
需要它在世界空间中的位置、观察的方向（与当前世界坐标的的z轴方向相反）、一个指向它右侧的向量以及一个指向它上方的向量 （实际上创建了一个三个单位轴相互垂直的、以摄像机的位置为原点的坐标系。）
```c
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // 在物体的前方
```
### 摄像机方向
实际上指向从它到目标向量的相反方向（蓝色的方向向量大概指向z轴的正方向，与摄像机实际指向的方向是正好相反的

``` c
glm::vec3 cameraDir;
glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f); // 原点坐标
cameraDir = glm::normalize(cameraPos - target); // 因为此时相机的Z轴与当前原点坐标的z轴方向相反，所以此时应该用相机坐标-原点坐标来表示相机照向原点时的朝向
```

右轴
* 两向量叉乘的结果是 生成的向量垂直于两向量，定义一个向上的向量与摄像机指向的方向进行叉乘，即可得到同时垂直于两向量的向量(右向量)
``` c
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::normalize(glm::cross(cameraDir * up));   // glm::cross(vec1, vec2); 叉乘两个向量
```

上轴
``` c++
glm::vec3 cameraUp = glm::cross(cameraDir, cameraRight);
cameraUp = glm::normalize(cameraUp);
```
生成摄像机的lookAt矩阵
``` c
lookAt = {
Rx, Ry, Rz, 0,
Ux, Uy, Uz, 0,
Dx, Dy, Dz, 0,
0,  0,  0,  1
} * {
1, 0, 0, -Px,
0, 1, 0, -Py,
0, 0, 1, -Pz,
0, 0, 0, 1,
} // R是右向量，U是上向量，D是方向向量P是摄像机位置向量. 位置向量是相反的, 因为我们最终希望把世界系统平移到与我们自身移动的相反方向

glm::mat4 view;
view = lookAt(
cameraPos,  // 摄像机位置
glm::vec3(0.0f, 0.0f, 0.0f), // 世界原点坐标
glm::vec3(0.0f, 1.0f, 0.0f); // 向上坐标
);  // 使用glm库自动生成lookAt矩阵（观察空间）
```
### 欧拉角
* 俯仰角(Pitch)，绕x轴旋转。
* 偏航角(Yaw)，绕y轴旋转。
* 滚转角(Roll)，绕z轴旋转。

对于摄像机系统来说，我们只关心俯仰角和偏航角，不讨论滚转角。使用动态欧拉角在进行旋转的时候会造成[万向锁](https://zh.wikipedia.org/wiki/%E7%92%B0%E6%9E%B6%E9%8E%96%E5%AE%9A)问题，使用[四元数](https://zh.wikipedia.org/wiki/%E5%9B%9B%E5%85%83%E6%95%B8)进行旋转可以解决万向锁问题。
## 光照
### 彭氏光照模型
* 环境光<br>
* 漫反射光
    即便在黑暗的情况下，物体也会有来自其他光源的，所以物体是不会完全黑暗的
* 镜面光 <br>
    物体身上有光泽的的亮点（如金属），镜面反射的颜色相比于物体本身的颜色更倾向与光的颜色

在片段着色器中混合环境光照
``` c
float ambientStrength = 1.0 ; // 常量环境因子
vec3  ambient         = anbientStrength * lightColor; // 环境光照

vec3  result          = ambient * objectColor; // 结果颜色
flagColor             = color;

```
> 漫反射光照模拟光源对物体的方向性影响，物体越是对着光源，光源对该对着的部分影响越大

计算漫反射光照:
1. 法向量: 一个垂直于顶点表面的向量
2. 定向光线: 作为光源向量与物体片段位置之差的方向向量。为了计算这个向量，我们需要光的位置向量和片段的位置向量

在片段着色器中混合漫反射光照
``` c
// 计算法向量(使用叉乘对立方体表面所有的点计算法向量)

// vert
fragPos = vec3(mdoel * vec4(aPos, 1.0)); // 基于世界坐标的顶点位置计算所有光照
Normal = mat3(transpose(inverse(model))) * aNormal; // 法线矩阵 * 法线向量 避免非等比缩放造成的法线方向改变
gl_Position = perspective * view * vec4(fragPos, 1.0);

//fragment

// 环境光照
float ambientStrength = 1.0 ; // 常量环境因子
vec3  ambient         = anbientStrength * lightColor; // 环境光照

// 漫反射
vec3 lightDir = normalize(lightPos - flagPos);
vec3 norm = normalize(Normal);

float diff = max(dot(norm, lightDir), 0);
float diffColor = diff * lightColor;


vec3  result          = ambient * (objectColor + diffColor); // 结果颜色
flagColor             = color;

_______________________________________________________________

// 镜面高光 当我们去看光被物体所反射的那个方向的时候， 我们会看到一个高光

// vert
fragPos = vec3(mdoel * vec4(aPos, 1.0)); // 基于世界坐标的顶点位置计算所有光照
Normal = mat3(transpose(inverse(model))) * aNormal; // 法线矩阵 * 法线向量 避免非等比缩放造成的法线方向改变
gl_Position = perspective * view * vec4(fragPos, 1.0);

//fragment
uniform vec3 viewPos;

// 环境光照
float ambientStrength = 1.0 ; // 常量环境因子
vec3  ambient         = anbientStrength * lightColor; // 环境光照

// 漫反射
vec3 lightDir = normalize(lightPos - flagPos);
vec3 norm = normalize(Normal);

float diff = max(dot(norm, lightDir), 0);
float diffColor = diff * lightColor;

// 镜面高光
vec3 viewDir = normalize(viewPos - fragPos);
vec3 reflectDir = reflect(-lightDir, norm);
float specFlag = 32; // 反光度
float specularStrength = 0.5; // 镜面强度

float spec = pow(max( dot(viewDir, reflectDir), 0.0), specFlag);
vec3 specular = specularStrength * spec * lightColor;

vec3  result          = (ambient + specular + diffColor) * objColor; // 结果颜色
flagColor             = color;
```


### 材质
> 一个物体反射的环境光，漫反射，镜面光颜色。这些东西设定了物体所拥有的颜色

* 光照贴图
* 漫反射贴图<br>
    一个设定了每个片段中漫反射颜色的纹理图片

* 镜反射贴图<br>
    想要让物体的某些部分以不同的强度显示镜面高光(如带钢圈的木头))，一个设定了每一个片段的镜面光强度/颜色的纹理贴图。仅在物体的特定区域显示镜面高光。

* 法线/凹凸贴图

* 反射贴图

### 投光物

* 平行光 <br>
    当光源来自于很远的地方时，来自光源的每条光线都会近似于互相平行。（当我们假设光源处于无限远处的模型时，他就被成为定向光（与光源的位置无关 所有光线近乎平行））

* 点光源 <br>
是处于世界中某一位置的光源，它会朝着所有方向发光，但光线会随着距离逐渐衰减（灯泡或火把）。
点光源会有衰减

* 聚光 <br>
类似手电筒, 同时也会存在光的衰减 / 平滑（软化边缘）=> 定义内外两个圆锥，当在内圆锥之外时开始进行边缘软化

着色器非常灵活，仅使用一些3D向量和可配置的变量就能够创造出惊人的图像，于是乎sharder诞生啦~
