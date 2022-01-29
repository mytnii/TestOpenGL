#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callbac(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Константы
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";


int main(void)
{
#ifdef DEBUG
    GLFWwindow* window;


    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        std::cout << "Canot load GLAD!" << std::endl;
        return -1;
    }



    std::cout << "OpenGL " << GLVersion.major << "."
        << GLVersion.minor << std::endl;

    glClearColor(0, 1, 0, 1);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
#endif // DEBUG


    // инициализация glfw
    glfwInit();

    // задаем конфигурацию glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // создаем объект представляющий окно приложения
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello", NULL, NULL);

    // проверка на наличие окна
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // делаем контекст окна основным
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callbac);


    // загрузка указателей на OpenGL функции
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Компелирование шейдерной программы

    // Вершинный шейдер
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Проверка на наличие ошибок компилирования вершинного шейдера
    int success;
    char infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "EROR::SHADERS::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
    }

    // Фрагментный шейдер
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Проверка на наличие ошибок компелирования фрагментного шейдера
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADERS::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
    }

    // Связывание шейдеров
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Проверка на наличие ошибок компелирования связывания шейдеров
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << std::endl;
    }

   // Удаление шейдеров
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Указывание вершин и настройка вершинных атрибутов
    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f, // левая вершина
        0.5f, -0.5f, 0.0f,  // правая вершина
        0.0f, 0.05f, 0.0f   // верхняя вершина
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Связываем объект вершинного массива
    glBindVertexArray(VAO);

    // Связываем и устанавливаем вершинный буфер
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Конфигурируем вершынный атрибут
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Выполняем отвязку VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Выполняем отвязку VAO
    glBindVertexArray(0);

    // Отрисовка полигонов в режиме каркаса
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    //// задаем размер области видимости окна
    //glViewport(0, 0, 800, 600);

    /*glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);*/

    //цикл рендеринга
    while (!glfwWindowShouldClose(window))
    {
        // Обработка ввода
        processInput(window);

        // Выполнение рендеринга
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Рисуем треугольник
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Обмен содержимым front и back буферо
        glfwSwapBuffers(window); 

        // Отслеживание событий
        glfwPollEvents(); 
    }

    // Освобождаем все ресурсы
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // удаление ресурсов выделеных для GLFW
    glfwTerminate();
    return 0;
}

// Обработка всех собыйтий ввода: запрос GLFW о нажатии/отпускании клавиш
//и обработка данных событий
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

// корекция размера области окна просмотра
void framebuffer_size_callbac(GLFWwindow* window, int width, int height)
{
    // Убеждаемся, что окно просмотра соответствует новым размерам окна
    glViewport(0, 0, width, height);
}