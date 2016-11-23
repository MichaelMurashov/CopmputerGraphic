//
// Created by michaelmurashov on 26.10.16.
//

#ifndef OPENGL_VIEW_H
#define OPENGL_VIEW_H

#include "vector"
#include "string"

using std::string;

namespace View {
    void setupView(int width, int height);
    void readBin(string path);

    float clamp(float value, float min, float max);
    float transferFunction(short value);

    void drawQuads(int layerNumber);

    void progressKey(int key, int x, int y);

    void render();

    static int X, Y, Z;
    static std::vector<short> array;
    static float min = 0, max = 2000;
    static int currentLayer;
};


#endif //OPENGL_VIEW_H
