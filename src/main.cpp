#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <gl_log.h>
#include <logger.h>

int
main(int argc, char** argv)
{
    if (!glfwInit())
    {
        glfwTerminate();
        LOG_ERROR("Failed to init GLFW");
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 640, "megagon", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (window == nullptr)
    {
        glfwTerminate();
        LOG_ERROR("Failed to create window");
    }
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        LOG_ERROR("Failed to init GLEW");
    }

    GLCall(glClearColor(0.5f, 0.5f, 0.5f, 1.0f));

    GLCall(glEnable(GL_CULL_FACE));
    GLCall(glFrontFace(GL_CCW)); // the direction in which faces are defined (determins back/front): GL_CCW | GL_CW
    GLCall(glCullFace(GL_BACK)); // the face side to cull away: GL_FRONT | GL_BACK | GL_FRONT_AND_BACK

    GLCall(glEnable(GL_BLEND));
    GLCall(glEnable(GL_DEPTH_TEST));
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
