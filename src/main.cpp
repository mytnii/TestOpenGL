#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void processInput(GLFWwindow* window);
//void framebuffer_size_callbac(GLFWwindow* window, int width, int height);

// ���������
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

    // ������������� glfw
    glfwInit();

    // ������ ������������ glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ������� ������ �������������� ���� ����������
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello", NULL, NULL);

    // �������� �� ������� ����
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // ������ �������� ���� ��������
    glfwMakeContextCurrent(window);
  /*  glfwSetFramebufferSizeCallback(window, framebuffer_size_callbac);*/


    // �������� ���������� �� OpenGL �������
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //// ������ ������ ������� ��������� ����
    //glViewport(0, 0, 800, 600);

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    //���� ����������
    while (!glfwWindowShouldClose(window))
    {
        // ��������� �����
        processInput(window);

        // ���������� ����������
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ����� ���������� front � back ������
        glfwSwapBuffers(window); 

        // ������������ �������
        glfwPollEvents(); 
    }

    // �������� �������� ��������� ��� GLFW
    glfwTerminate();
    return 0;
}

// ��������� ���� �������� �����: ������ GLFW � �������/���������� ������
//� ��������� ������ �������
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

// �������� ������� ������� ���� ���������
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // ����������, ��� ���� ��������� ������������� ����� �������� ����
    glViewport(0, 0, width, height);
}