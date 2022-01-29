#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void processInput(GLFWwindow* window);
//void framebuffer_size_callbac(GLFWwindow* window, int width, int height);

// Константы
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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
  /*  glfwSetFramebufferSizeCallback(window, framebuffer_size_callbac);*/


    // загрузка указателей на OpenGL функции
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //// задаем размер области видимости окна
    //glViewport(0, 0, 800, 600);

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    //цикл рендеринга
    while (!glfwWindowShouldClose(window))
    {
        // Обработка ввода
        processInput(window);

        // Выполнение рендеринга
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Обмен содержимым front и back буферо
        glfwSwapBuffers(window); 

        // Отслеживание событий
        glfwPollEvents(); 
    }

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
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Убеждаемся, что окно просмотра соответствует новым размерам окна
    glViewport(0, 0, width, height);
}