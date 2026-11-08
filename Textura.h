#pragma once

#ifndef TEXTURA_H
#define TEXTURA_H

#include <glad/glad.h>
#include <string>

class Textura {
public:
    unsigned int id;
    int ancho, alto, canales;

    Textura();
    ~Textura();

    Textura(const Textura&) = delete;
    Textura& operator=(const Textura&) = delete;

    bool cargar(const std::string& ruta);
    void usar(unsigned int unidad = 0) const;
};

#endif
