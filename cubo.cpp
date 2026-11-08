#include "cubo.h"

Cubo::Cubo() {
    color[0] = 1.0f; color[1] = 0.8f; color[2] = 0.4f;

    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 3; ++j)
            colorescara[i][j] = 0.7f;

    vertices = {
        -0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 
        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f, 
        -0.5f,  0.5f, -0.5f
    };

    verticesCaras = {
     
        -0.5f,-0.5f,-0.5f, 0.0f,0.0f,  0.5f,-0.5f,-0.5f, 1.0f,0.0f,  0.5f,0.5f,-0.5f, 1.0f,1.0f, // atras
         0.5f,0.5f,-0.5f, 1.0f,1.0f, -0.5f,0.5f,-0.5f, 0.0f,1.0f, -0.5f,-0.5f,-0.5f, 0.0f,0.0f,

        // esquina izquierda infe   // esquina derecha infe       // esquina derecha sup
        -0.5f,-0.5f,0.5f, 0.0f,0.0f,  0.5f,-0.5f,0.5f, 1.0f,0.0f,  0.5f,0.5f,0.5f, 1.0f,1.0f, //  frente
        // esquina derecha sup      // esquina izquierda sup    // esquina izquierda infe 
         0.5f,0.5f,0.5f, 1.0f,1.0f, -0.5f,0.5f,0.5f, 0.0f,1.0f, -0.5f,-0.5f,0.5f, 0.0f,0.0f,


        //esquina sup der           //esquina sup izq           //esquina infe izq  
        -0.5f,0.5f,0.5f, 1.0f,1.0f, -0.5f,0.5f,-0.5f, 0.0f,1.0f, -0.5f,-0.5f,-0.5f, 0.0f,0.0f, // izquierda
        //esquina  infe izq         ///esquina  infe der            //esquina sup der    
        -0.5f,-0.5f,-0.5f, 0.0f,0.0f, -0.5f,-0.5f,0.5f, 1.0f,0.0f, -0.5f,0.5f,0.5f, 1.0f,1.0f,


         // esquina izquierda sup   // esquina derech sup       // esquina derech infe 
         0.5f,0.5f,0.5f, 0.0f,1.0f,  0.5f,0.5f,-0.5f, 1.0f,1.0f,  0.5f,-0.5f,-0.5f, 1.0f,0.0f, //derecha
          // esquina derech infe       //esquina izq infe             // esquina izquierda sup  
         0.5f,-0.5f,-0.5f, 1.0f,0.0f,  0.5f,-0.5f,0.5f, 0.0f,0.0f,  0.5f,0.5f,0.5f, 0.0f,1.0f,
       
        -0.5f,-0.5f,-0.5f, 0.0f,1.0f,  0.5f,-0.5f,-0.5f, 1.0f,1.0f,  0.5f,-0.5f,0.5f, 1.0f,0.0f, //abajo
         0.5f,-0.5f,0.5f, 1.0f,0.0f, -0.5f,-0.5f,0.5f, 0.0f,0.0f, -0.5f,-0.5f,-0.5f, 0.0f,1.0f,
        
        // esquina izquierda sup        // esquina derech sup       // esquina derech infe 
        -0.5f,0.5f,-0.5f, 0.0f,1.0f,  0.5f,0.5f,-0.5f, 1.0f,1.0f,  0.5f,0.5f,0.5f, 1.0f,0.0f, //arriba
        // esquina derech infe //esquina izq infe  // esquina izquierda sup 
         0.5f,0.5f,0.5f, 1.0f,0.0f, -0.5f,0.5f,0.5f, 0.0f,0.0f, -0.5f,0.5f,-0.5f, 0.0f,1.0f
    };

    indicesLineas = { 
        0, 1,  1, 2,  2, 3,  3, 0,
        4, 5,  5, 6,  6, 7,  7, 4,
        0, 4,  1, 5,  2, 6,  3, 7
    };

    resetTransformaciones();
    inicializarGPU();
}

Cubo::~Cubo() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO_esquinas);
    glDeleteBuffers(1, &VBO_esquinas);
    glDeleteBuffers(1, &EBO_lineas);
}

void Cubo::inicializarGPU() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesCaras.size() * sizeof(float), verticesCaras.data(), GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glGenVertexArrays(1, &VAO_esquinas);
    glGenBuffers(1, &VBO_esquinas);
    glBindVertexArray(VAO_esquinas);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_esquinas);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &EBO_lineas);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_lineas);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLineas.size() * sizeof(unsigned int), indicesLineas.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glBindVertexArray(0);
}

void Cubo::resetTransformaciones() {
    transformador = matris::identidad();
}

void Cubo::mandarColores(vector<vector<float>> Ccolores){
    for (size_t i = 0; i < Ccolores.size() && i < 6; i++) {
        for (size_t j = 0; j < Ccolores[i].size() && j < 3; j++) {
            colorescara[i][j] = Ccolores[i][j];
        }
    }
}


bool Cubo::asignarTexturaCara(int cara, const std::string& ruta) {

    textura[cara].cargar(ruta);
    //for (int i = 0; i < 6; i++) texturas[i] = false;
    texturas[cara] =true;
    
    return true;
}


void Cubo::trasladar(float tx, float ty, float tz) {
    Matrix T = matris::traslacion(tx, ty, tz);
    transformador = matris::multiplicar(T, transformador);
}

void Cubo::escalar(float sx, float sy, float sz) {
    Matrix S = matris::escala(sx, sy, sz);
    transformador = matris::multiplicar(S, transformador);
}

void Cubo::rotarX(float grados) {
    Matrix R = matris::rotacionX(grados);
    transformador = matris::multiplicar(R, transformador);
}

void Cubo::rotarY(float grados) {
    Matrix R = matris::rotacionY(grados);
    transformador = matris::multiplicar(R, transformador);
}

void Cubo::rotarZ(float grados) {
    Matrix R = matris::rotacionZ(grados);
    transformador = matris::multiplicar(R, transformador);
}

void Cubo::setColor(float r, float g, float b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}


void Cubo::dibujarLineas(Shaders& shader) {
    shader.use();
    shader.SetUsarTextura(false);
    shader.SetColor(0.0f, 0.0f, 0.0f);
    shader.SetMatrix(this->transformador);
	glLineWidth(5.5f);

    glBindVertexArray(VAO_esquinas);
    glDrawElements(GL_LINES, static_cast<GLsizei>(indicesLineas.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Cubo::dibujarConModo(Shaders& shader) {
    shader.use();
    shader.SetUsarTextura(false);
    shader.SetColor(color[0], color[1], color[2]);
    shader.SetMatrix(this->transformador);

    glBindVertexArray(VAO_esquinas);
    glDrawArrays(GL_POINTS, 0, 8);
    
    glBindVertexArray(0);
}

void Cubo::dibujar(Shaders& shader) {
    shader.use();
    shader.SetMatrix(this->transformador);

    glBindVertexArray(VAO);

    for (int i = 0; i < 6; ++i) {
        if (texturas[i]) {
            textura[i].usar(0);         
            shader.SetUnidadTextura(0);
            shader.SetUsarTextura(true);
        } else {
            shader.SetUsarTextura(false);
        }
        shader.SetColor(colorescara[i][0], colorescara[i][1], colorescara[i][2]);
        glDrawArrays(GL_TRIANGLES, i * 6, 6);
    }

    glBindVertexArray(0);
}

