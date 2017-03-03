#include <fstream>
#include <stdlib.h>
#include <string.h>

#include "shader.h"


static char* Shader::loadSource(const char *filePath) {
    {
        const size_t blockSize = 512;
        FILE *fp;
        char buf[blockSize];
        char *source = nullptr;
        size_t tmp, sourceLength = 0;

        fp = fopen(filePath, "r");
        if(!fp) {
            fprintf(stderr, "shaderLoadSource(): Unable to open %s for reading\n", filePath);
            return nullptr;
        }

        /* read the entire file into a string */
        while((tmp = fread(buf, 1, blockSize, fp)) > 0) {
            char *newSource = new char[sourceLength + tmp + 1];
//            if( !newSource) {
//                fprintf(stderr, "shaderLoadSource(): malloc failed\n");
//                if(source)
//                    delete[] source;
//                return nullptr;
//            }

            if(source) {
                memcpy(newSource, source, sourceLength);
                delete[] source;
            }
            memcpy(newSource + sourceLength, buf, tmp);

            source = newSource;
            sourceLength += tmp;
        }

        if(source)
            source[sourceLength] = '\0';

        fclose(fp);
        return source;
    }
}

GLuint Shader::compileFromFile(GLenum type, const char *filePath){
    char *source;
    GLuint shader;
    GLint length, result;

    source = Shader::loadSource(filePath);
//    if(!source)
//        return 0;

    /* create shader object, set the source, and compile */
    shader = glCreateShader(type);
    length = (GLint)(strlen(source));
    glShaderSource(shader, 1, (const char **)&source, &length);
    glCompileShader(shader);

    delete[] source;

    /* make sure the compilation was successful */
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE) {
        char *log;

        /* get the shader info log */
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        log = new char [length];
        glGetShaderInfoLog(shader, length, &result, log);

        /* print an error message and the info log */
        fprintf(stderr, "shaderCompileFromFile(): Unable to compile %s: %s\n", filePath, log);
        delete[] log;

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

void ::Shader::attachFromFile(GLuint program, GLenum type, const char *filePath) {
    GLuint shader = Shader::compileFromFile(type, filePath);

    if(shader != 0) {
        glAttachShader(program, shader);
        glDeleteShader(shader);
    }
}
