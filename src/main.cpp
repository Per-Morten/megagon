#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include <exception>
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ");\n" << function <<
            " in " << file << "\nat line: " << line << std::endl;
        std::cin.get();
        return false;
    }
    return true;
}

#define ASSERT(glFunc) if (!(glFunc)) std::terminate();

#define GLCall(glFunc) GLClearError();\
    glFunc;\
    ASSERT(GLLogCall(#glFunc, __FILE__, __LINE__))

int
main(int argc, char** argv)
{
    if (!glfwInit())
    {
        glfwTerminate();
        exit(-1); //(Init::logtag, "Failed to init GLFW");
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 640, "megagon", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (window == NULL)
    {
        glfwTerminate();
        exit(-1); // LOG_ERROR(Init::logtag, "Failed to open GLFW window");
    }
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        exit(-1); // LOG_ERROR(Init::logtag, "Failed to init GLEW");
    }

    GLCall(glEnable(GL_PROGRAM_POINT_SIZE));
    GLCall(glClearColor(0.5f, 0.5f, 0.5f, 1.0f));

    GLCall(glEnable(GL_CULL_FACE));
    GLCall(glFrontFace(GL_CCW)); // the direction in which faces are defined (determins back/front): GL_CCW | GL_CW
    GLCall(glCullFace(GL_BACK)); // the face side to cull away: GL_FRONT | GL_BACK | GL_FRONT_AND_BACK

    GLCall(glEnable(GL_BLEND));
    //GLCall(glEnable(GL_DEPTH_TEST)); //enabled to avoid ugly artifacts that depend on the angle of view and drawing order
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwDestroyWindow(window);
    glfwTerminate();

}
