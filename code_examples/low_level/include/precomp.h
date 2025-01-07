//
// Created by Nils Enric Canut Taugbøl on 07/01/2025.
//

#ifndef PRECOMP_H
#define PRECOMP_H

#include <cmath>
#include <chrono>
#include <iostream>
#include <fstream>
#include <armadillo>
#include "constants.h"

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned short ushort;

struct Timer
{
    Timer() { reset(); }
    float elapsed() const
    {
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - start);
        return (float)time_span.count();
    }
    void reset() { start = std::chrono::high_resolution_clock::now(); }
    std::chrono::high_resolution_clock::time_point start;
};

#include "actor.h"

#endif //PRECOMP_H
