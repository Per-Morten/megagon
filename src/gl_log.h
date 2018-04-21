#include <exception>
#include <iostream>
#include <GL/glew.h>

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
