//
// Created by michaelmurashov on 26.10.16.
//

#ifndef OPENGL_BIN_H
#define OPENGL_BIN_H

#include "string"

using std::string;

class Bin {
  public:
    static int X, Y, Z;
    static short array[];

    void readBin(string &path);
};

#endif //OPENGL_BIN_H
