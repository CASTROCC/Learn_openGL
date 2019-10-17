//
//  lession_2.hpp
//  Learn_OpenGL
//
//  Created by Superman on 2019/10/2.
//  Copyright © 2019 Superman. All rights reserved.
//

#ifndef lession_2_hpp
#define lession_2_hpp


using namespace std;

void lession_02();


const char* vertSharderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.1f, 0.2f, 0.1f, 0.8f);\n"
    "}\n\0";


float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};

void lession_02() {
    
    GLFWwindow *window;
    window = createWindow();  // source from lession1
    
    // 顶点着色器
    unsigned int vertSharder;
    vertSharder = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertSharder, 1, &vertSharderSource, NULL);  // 第二个参数为glsls字符串数量
    glCompileShader(vertSharder);
    
   
    
    // 检测顶点着色器是否编译成功
    int  success;
    char infoLog[512];
    glGetShaderiv(vertSharder, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertSharder, 512, NULL, infoLog);
        std::cout << "vertSharder compile failed. \n" << infoLog << std::endl;
    }
    
    // 片段着色器 （上颜色）
    unsigned int fragmentSharder;
    fragmentSharder = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentSharder, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentSharder);
    
    // 将顶点着色器与片段着色器连接成一个着色器（LinK）然后在渲染的时候激活这个着色器片段
    
    // 当链接着色器至一个程序的时候，它会把每个着色器的输出链接到下个着色器的输入
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertSharder);
    glAttachShader(shaderProgram, fragmentSharder);
    glLinkProgram(shaderProgram); // 链接着色器
    
    // 检测连接器是否链接成功
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "program link failed. \n" << infoLog << std::endl;
    }
    
    
    // 激活链接程序
    glUseProgram(shaderProgram);
    //在glUseProgram函数调用之后，每个着色器调用和渲染调用都会使用这个程序对象（也就是之前写的着色器)了。

    //对了，在把着色器对象链接到程序对象以后，记得删除着色器对象，我们不再需要它们了：
    glDeleteShader(vertSharder);
    glDeleteShader(fragmentSharder);
    
    // ###############  glsl程序告诉gpu该如何在顶点和片段着色器中处理顶点数据 #############
    
    
    
    
    // 绑定VAO 这样使用VAO记住所有缓冲顶点数据的值和属性，方便下次绘制时调用， 上面使用VAB设置的所有状态都将储存在VAO中。
    // 通常 一个VAO（顶点数组对象）会储存以下这些内容：
        // glEnableVertexAttribArraay() / glDisableVertexAttribArray();
        // 通过glVertexAttribPointer()设置的顶点属性配置
        // 通过glVertexAttribPointer调用与顶点属性关联的顶点缓冲对象
    
    
    unsigned int VAO; // 类似一个数组 里面储存了所有顶点缓冲对象的数据配置
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); //  VAO的使用仅仅是绑定到希望使用的设定上
    
    // ######将需要处理的d顶点数据传入gpu
    // 新建了一个顶点数组对象 并将其绑定至openGL的GL_ARRAY_BUFFER上
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
  //从这一刻起，我们使用的任何（在GL_ARRAY_BUFFER目标上的）缓冲调用都会用来配置当前绑定的缓冲(VBO)。然后我们可以调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中：
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 静态三角形 绘制时图形不会发生变化
    // 现在我们已经把顶点数据储存在显卡的内存中，用VBO这个顶点缓冲对象管理
    
    
    // （VAO的使用就是为了储存以下数据）
    // 使用glVertexAttribPointer函数告诉OpenGL该如何解析顶点数据（应用到逐个顶点属性上）了：
    /**
              一个参数指定我们要配置的顶点属性 对应glsl中的position值
              第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
              第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec*都是由浮点数值组成的)。
              第四个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。我们把它设置为GL_FALSE。 （此时我们定义定点数据已经是标准化数据，不需要重复告诉opengld标准化）
            第五个参数叫做步长 即连续的顶点属性组之间的间隔 （由于下个顶点属性位于3个float之后 所以可以将步长设置为 3 * sizeof(float)）
            第六个参数的类型是void*，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0。
     */
    
    // 该指令必须放在VAO初始化之后 （opengl底层自动将该数据存入已初始化的VAO中？）
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // 定的。由于在调用glVertexAttribPointer之前绑定的是先前定义的VBO对象，顶点属性0现在会链接到它的顶点数据。    
    
    while (!glfwWindowShouldClose(window))
   {
       processInput(window);

       // 窗口颜色
       glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
       glClear(GL_COLOR_BUFFER_BIT);

       // 激活我们为GPU编写的渲染指令
       glUseProgram(shaderProgram);
       
       // 在每次渲染循环中绑定VAO数据， 方便下次直接使用顶点数据配置
       glBindVertexArray(VAO);
       
       // 绘制三角形 1.类型 2.顶点索引开始位置 3.指定需要绘制的顶点个数（顶点数为3）
       glDrawArrays(GL_TRIANGLES, 0, 3);
       glfwSwapBuffers(window);
       glfwPollEvents();
   }

   // 程序结束后删除所有顶点数据
   glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);

   // glfw: terminate, clearing all previously allocated GLFW resources.
   // ------------------------------------------------------------------
   glfwTerminate();
    
    cout << "hellow lession_02" << endl;
}

#endif /* lession_2_hpp */
