#ifndef RAYTRACING_SHADER_H
#define RAYTRACING_SHADER_H

#include <GL/glew.h>
#include <OpenGL/gl.h>

namespace Shader {
    static char* loadSource(const char *filePath);
    static GLuint compileFromFile(GLenum type, const char *filePath);
    void attachFromFile(GLuint program, GLenum type, const char *filePath);
}

#endif //RAYTRACING_SHADER_H
