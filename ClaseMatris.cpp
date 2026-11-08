#include "ClaseMatris.h"

Matrix matris::multiplicar(const Matrix& A, const Matrix& B) {
    Matrix resultado;
    std::fill(resultado.matrix.begin(), resultado.matrix.end(), 0.0f);

    for (int col = 0; col < 4; ++col) {
        for (int fila = 0; fila < 4; ++fila) {
            float suma = 0.0f;
            for (int k = 0; k < 4; ++k) {
                suma += A.matrix[k * 4 + fila] * B.matrix[col * 4 + k];
            }
            resultado.matrix[col * 4 + fila] = suma;
        }
    }
    return resultado;
}

Matrix matris::identidad() {
    return Matrix();
}

Matrix matris::traslacion(float tx, float ty, float tz) {
    Matrix M = identidad();
    M.matrix[12] = tx;
    M.matrix[13] = ty;
    M.matrix[14] = tz;
    return M;
}

Matrix matris::escala(float sx, float sy, float sz) {
    Matrix M = identidad();
    M.matrix[0]  = sx;
    M.matrix[5]  = sy;
    M.matrix[10] = sz;
    return M;
}

Matrix matris::rotacionX(float grados) {
    float rad = grados * (M_PI / 180.0f);
    float c = cos(rad);
    float s = sin(rad);

    Matrix M = identidad();
    M.matrix[5]  = c;
    M.matrix[6]  = s;
    M.matrix[9]  = -s;
    M.matrix[10] = c;
    return M;
}

Matrix matris::rotacionY(float grados) {
    float rad = grados * (M_PI / 180.0f);
    float c = cos(rad);
    float s = sin(rad);

    Matrix M = identidad();
    M.matrix[0]  = c;
    M.matrix[2]  = -s;
    M.matrix[8]  = s;
    M.matrix[10] = c;
    return M;
}

Matrix matris::rotacionZ(float grados) {
    float rad = grados * (M_PI / 180.0f);
    float c = cos(rad);
    float s = sin(rad);

    Matrix M = identidad();
    M.matrix[0] = c;
    M.matrix[1] = s;
    M.matrix[4] = -s;
    M.matrix[5] = c;
    return M;
}

Matrix matris::perspectiva(float fovGrados, float aspecto, float nearPlane, float farPlane) {
    float fovRad = fovGrados * (M_PI / 180.0f);
    float tanHalfFov = tan(fovRad / 2.0f);

    Matrix M;
    std::fill(M.matrix.begin(), M.matrix.end(), 0.0f);

    M.matrix[0]  = 1.0f / (aspecto * tanHalfFov);
    M.matrix[5]  = 1.0f / tanHalfFov;
    M.matrix[10] = -(farPlane + nearPlane) / (farPlane - nearPlane);
    M.matrix[11] = -1.0f;
    M.matrix[14] = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);

    return M;
}