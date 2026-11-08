#pragma once

#include "cubo.h"
#include "ClaseMatris.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

enum Camada{
	FRONT, BACK, UP,DOWN, RIGHT,LEFT, CENTERX, CENTERZ, CENTERY
};

class CRubik{
public:
	vector<Cubo*> bloques;
	vector<Cubo*> camada1;
	vector<Cubo*> camada2;
	vector<Cubo*> camada3;
	vector<Cubo*> camada4;
	vector<Cubo*> camada5;
	vector<Cubo*> camada6;
	vector<Cubo*> camada7;
	vector<Cubo*> camada8;
	vector<Cubo*> camada9;

	
	CRubik();  
	void colorearcubos();
	void dibujarcaras(Shaders& shader);
	void dibujarlineas(Shaders& shader);
	void dibujarpuntos(Shaders& shader);
	
	void rotar_Camada(Camada camada, float deltaTime);
	void actualizarCamadas();
	void reiniciar();
};

