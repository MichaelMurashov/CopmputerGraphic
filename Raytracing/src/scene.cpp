#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

#include "scene.h"

struct Vertex {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

void Scene::setup() {
    Scene::init();
    Scene::initVBO();
}

//void Scene::display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    Scene::render();
//
//    glfwSwapBuffers()
//    glutSwapBuffers();
//}

void Scene::init() {
    GLint result;

    /* create program object and attach shaders */
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, (char*)"Couldn't initialize GLEW library.\n");
        exit(EXIT_FAILURE);
    }

    g_program = glCreateProgram();

    Shader::attachFromFile(g_program, GL_VERTEX_SHADER, "../shaders/vertex.glsl");
    Shader::attachFromFile(g_program, GL_FRAGMENT_SHADER, "../shaders/fragment.glsl");

    /* link the program and make sure that there were no errors */
    glLinkProgram(g_program);

    /* make sure the link was successful */
    glGetProgramiv(g_program, GL_LINK_STATUS, &result);
    if(result == GL_FALSE) {
        GLint length;
        char *log;

        glGetProgramiv(g_program, GL_INFO_LOG_LENGTH, &length);
        log = new char [length];
        glGetProgramInfoLog(g_program, length, &result, log);

        fprintf(stderr, "init(): Program linking failed: %s\n", log);
        delete[] log;

        glDeleteProgram(g_program);
        g_program = 0;
    }

    attribute_vpos = (GLuint)(glGetAttribLocation(g_program, "vPosition"));
    uniform_campos = (GLuint)(glGetUniformLocation(g_program, "cameraPosition"));
    uniform_aspect = (GLuint)(glGetUniformLocation(g_program, "aspect"));
}

void Scene::initVBO() {
    Vertex vertdata[] = {
            { -1.f, 1.f, 0.f},
            { 1.f, 1.f, 0.f},
            { 1.f, -1.f, 0.f},
            {-1.f,-1.f, 0.f},
    };

    glGenBuffers(1, &vbo_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertdata), vertdata, GL_STATIC_DRAW);
}

void Scene::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    // ! Устанавливаем шейдерную программу текущей
    glUseProgram(g_program);

    /* setup camera */
    g_cameraPosition[0] = 0.0f;
    g_cameraPosition[1] = 0.0f;
    g_cameraPosition[2] = -4.0f;

    glLoadIdentity();
    glTranslatef(-g_cameraPosition[0], -g_cameraPosition[1], -g_cameraPosition[2]);

    glUniform3fv(uniform_campos, -1, g_cameraPosition);
    glUniform1f(uniform_aspect, 1);

    glEnableVertexAttribArray(attribute_vpos);

    // ! Указывая pointer 0 при подключенном буфере, мы указываем, что данные представлены в VBO
    // ! Отключаем VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);

    // ! Передаем данные на видеокарту (рисуем)
    glVertexAttribPointer(attribute_vpos, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);



    /* disable program */

//  glUseProgram(g_program);
    glDrawArrays(GL_QUADS, 0, sizeof(Vertex));

    // ! Отключаем массив атрибутов
    glDisableVertexAttribArray(attribute_vpos);

    // ! Отключаем шейдерную программу
    glUseProgram(0);
//    glfwSwapBuffers(win);
}
