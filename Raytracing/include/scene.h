#ifndef RAYTRACING_SCENE_H
#define RAYTRACING_SCENE_H

#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <GLFW/glfw3.h>
#include <OpenGL/glext.h>

#include "shader.h"

namespace Scene {
    void setup();

//    void display();
    void render();

    void init();
    void initVBO();

    static int width, heigth;

    static float g_cameraPosition[3];

    static GLuint g_program;

    static GLuint attribute_vpos;
    static GLuint uniform_campos;
    static GLuint uniform_aspect;

    static GLuint vbo_pos;

};

#endif //RAYTRACING_SCENE_H
