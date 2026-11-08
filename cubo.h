#pragma once

#ifndef CUBO_H
#define CUBO_H

#include "Shader.h"
#include "Textura.h"
#include "ClaseMatris.h"
#include <vector>
#include <memory>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;

enum CaraCubo {
    CARA_ATRAS = 0,
    CARA_FRENTE,
    CARA_IZQUIERDA,
    CARA_DERECHA,
    CARA_ABAJO,
    CARA_ARRIBA
};

class Cubo {
public:
    std::vector<float> vertices;

    std::vector<float> verticesCaras;
    std::vector<unsigned int> indicesLineas;

    unsigned int VAO, VBO;
    unsigned int VAO_esquinas, VBO_esquinas;
    unsigned int EBO_lineas;
    Matrix transformador;
    Matrix transformadorInicial;
    float color[3];
	float colorescara[6][3];

	
	bool texturas[6] = {false,false,false,false,false,false};

    Textura textura[6];

    Cubo();
    ~Cubo();

    void inicializarGPU();

    void rotarX(float grados);
    void rotarY(float grados);
    void rotarZ(float grados);
    void trasladar(float tx, float ty, float tz);
    void escalar(float sx, float sy, float sz);
    void resetTransformaciones();

	void mandarColores(vector<vector<float>> Ccolores);
    void setColor(float r, float g, float b);

	bool asignarTexturaCara(int cara, const std::string& ruta); 
	bool asignarTexturaTodas(const std::string& ruta);         
	void quitarTexturaCara(int cara);
	void quitarTexturas();

    void dibujar(Shaders& shader);
    void dibujarConModo(Shaders& shader);
	void dibujarLineas(Shaders& shader); 
    void dibujarCaras(Shaders& shader);
    size_t getNumIndicesLineas() const { return indicesLineas.size(); }

    const Matrix& getMatrizModelo() const { return transformador; }
    size_t getNumIndices() const { return verticesCaras.size() / 5; }
};

#endif
