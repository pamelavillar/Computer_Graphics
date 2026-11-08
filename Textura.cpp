#include "Textura.h"
#include <iostream>


#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

Textura::Textura() : id(0), ancho(0), alto(0), canales(0) {}

Textura::~Textura() {
    if (id != 0) glDeleteTextures(1, &id);
}

bool Textura::cargar(const std::string& ruta) {
    stbi_set_flip_vertically_on_load(true); 

    unsigned char* data = stbi_load(ruta.c_str(), &ancho, &alto, &canales, 0);
    if (!data) {
        std::cout << "ERROR: no se pudo cargar la textura -> " << ruta << std::endl;
        return false;
    }

    GLenum formato = GL_RGB;
    if (canales == 1)      formato = GL_RED;
    else if (canales == 3) formato = GL_RGB;
    else if (canales == 4) formato = GL_RGBA;

    if (id == 0) glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, formato, ancho, alto, 0, formato, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    return true;
}

void Textura::usar(unsigned int unidad) const {
    glActiveTexture(GL_TEXTURE0 + unidad);
    glBindTexture(GL_TEXTURE_2D, id);
}
