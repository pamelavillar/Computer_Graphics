#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "ClaseMatris.h"

class Shaders{
	public:
	unsigned int program_id,vertex_shad_id,fragment_shad_id;
	Shaders();
	void use();
	unsigned int GetProgram();
	void SetColor(const float &r,const float &g,const float &b);
	void SetMatrix(const Matrix& mat);
	void SetView(const Matrix& mat);
	void SetProjection(const Matrix& mat);
	void SetUsarTextura(bool usar);   
	void SetUnidadTextura(int unidad);
};

#endif
