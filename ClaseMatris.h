#pragma once

#ifndef CLASEMATRIS_H
#define CLASEMATRIS_H

#include <vector>
#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif


class Matrix {
public:
    std::vector<float> matrix;

    Matrix() {
        
        matrix = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }
};

class matris {
public:
    matris() {}

    static Matrix multiplicar(const Matrix& A, const Matrix& B);
    static Matrix identidad();
    static Matrix traslacion(float tx, float ty, float tz);
    static Matrix escala(float sx, float sy, float sz);
    static Matrix rotacionX(float grados);
    static Matrix rotacionY(float grados);
    static Matrix rotacionZ(float grados);
    static Matrix perspectiva(float fovGrados, float aspecto, float nearPlane, float farPlane);
};

#endif