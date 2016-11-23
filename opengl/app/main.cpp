//
// Created by michaelmurashov on 26.10.16.
//

#include "GL/glut.h"
#include "view.h"

int main(int argc, char** argv) {
    View::readBin("../legs.bin");
    int width = 800, height = 600;

    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("open_gl");

    View::setupView(width, height);
    glutDisplayFunc(View::render);

    glutSpecialFunc(View::progressKey);

    glutMainLoop();
    return 0;
}
