//
// Created by michaelmurashov on 26.10.16.
//

#include <fstream>

#include "bin.h"

void Bin::readBin(string &path) {
    std::fstream file(path, std::ios::binary);

    if (!file.is_open())
        throw std::invalid_argument("File error!");

    file.read((char*)&X, sizeof(X));
    file.read((char*)&Y, sizeof(Y));
    file.read((char*)&Z, sizeof(Z));

    int size = X * Y * Z;

    file.read((char*)&array[0], size * sizeof(short));
}
