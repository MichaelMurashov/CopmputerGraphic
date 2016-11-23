//
// Created by michaelmurashov on 26.10.16.
//

#include "fstream"
#include "GL/glut.h"
#include "view.h"

void View::readBin (string path) {
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open())
        throw std::invalid_argument("File error!");

    file.read((char*)&X, sizeof(X));
    file.read((char*)&Y, sizeof(Y));
    file.read((char*)&Z, sizeof(Z));

    unsigned long size = static_cast<unsigned long>(X * Y * Z);

    array.reserve(size);
    file.read((char*)&array[0], size * sizeof(short));
}

void View::setupView(int width, int height) {
    currentLayer = 0;
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, X, 0, Y, -1, 1);
    glViewport(0, 0, width, height);
}

float View::clamp(float value, float min, float max) {
    if (value < min)
        return min;
    else if (value > max)
        return max;
    else
        return value;
}

float View::transferFunction(short value) {
    float newValue = 255.f * (value - min) / (max - min);
    return clamp(newValue, 0.f, 255.f);
}

void View::drawQuads(int layerNumber) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_QUADS);

    for (int x_coord = 0; x_coord < X - 1; x_coord++)
        for (int y_coord = 0; y_coord < Y - 1; y_coord++) {
            short value;
            float color;

            // 1st top
            value = array[x_coord + y_coord * X
                               + layerNumber * X * Y];
            color = transferFunction(value) / 255.f;
            glColor3f(color, color, color);
            glVertex2f(x_coord, y_coord);

            // 2nd top
            value = array[x_coord + (y_coord + 1) * X
                               + layerNumber * X * Y];
            color = transferFunction(value) / 255.f;
            glColor3f(color, color, color);
            glVertex2f(x_coord, y_coord + 1);

            // 3th top
            value = array[x_coord + 1 + (y_coord + 1) * X
                               + layerNumber * X * Y];
            color = transferFunction(value) / 255.f;
            glColor3f(color, color, color);
            glVertex2f(x_coord + 1, y_coord + 1);

            // 4th top
            value = array[x_coord + 1 + y_coord * X
                               + layerNumber * X * Y];
            color = transferFunction(value) / 255.f;
            glColor3f(color, color, color);
            glVertex2f(x_coord + 1, y_coord);
        }

    glEnd();
}

void ::View::progressKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            currentLayer = static_cast<int>( clamp(currentLayer + 1, 0, Z - 1) );
            break;

        case GLUT_KEY_LEFT:
            currentLayer = static_cast<int>( clamp(currentLayer - 1, 0, Z - 1) );
            break;
    }

    glutPostRedisplay();
}

void ::View::render() {
    drawQuads(currentLayer);
    glutSwapBuffers();
}
