
#ifdef __APPLE__
#include <glad/glad.h>
#else
#include <glad/gl.h>
#endif
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

#include "Shader.h"
#include "ClaseMatris.h"
#include "cubo.h"

#include "CRubik.h"

const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;

float camPosX      = 0.0f;
float camPosY      = 4.0f;
float camPosZ      = 10.0f;
float velCamara    = 0.015f;

bool autoRotarCamara = false;
bool autoRotarCamaraX = false;
float anguloCamara   = 0.0f;
float velRotacionCam = 0.15f;//0.015f
float anguloCamaraX   = 0.0f;


float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void processInput_Camada(GLFWwindow* window, CRubik& cubo, float deltaTime);
void processInput_Camada2(GLFWwindow* window, CRubik& cubo, float deltaTime);

Matrix obtenerMatrizVista();

void actualizarPatronMovimiento();

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cubo Rubik", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

#ifdef __APPLE__
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
#else
    if (!gladLoadGL(glfwGetProcAddress))
#endif
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);


    Shaders misShaders;
    misShaders.use();
    float aspecto = float(SCR_WIDTH) / float(SCR_HEIGHT);
    Matrix proj = matris::perspectiva(45.0f, aspecto, 0.1f, 150.0f);
    misShaders.SetProjection(proj);


    // Unico objeto: Cuborubik
	CRubik ola;

    std::cout << "===== CONTROLES =====" << std::endl;
    std::cout << "autorotar cubo en Y          -> R" << std::endl;
    std::cout << "detener autorotacion en Y    -> T" << std::endl;
    std::cout << "autorotar cubo en X          -> A" << std::endl;
    std::cout << "detener autorotacion en X    -> S" << std::endl;
    std::cout << "mover camara arriba / abajo  -> I / K" << std::endl;
    std::cout << "mover camara izq / der       -> J / L" << std::endl;
    std::cout << "acercar / alejar camara      -> U / O" << std::endl;
    std::cout << "elegir camada                -> 1 a 9" << std::endl;
    std::cout << "girar camada                 -> flecha izq / der" << std::endl;
    std::cout << "reiniciar cubo               -> Q" << std::endl;
    std::cout << "salir                        -> ESC" << std::endl;


    while (!glfwWindowShouldClose(window))
    {   
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 

        processInput(window);
        processInput_Camada(window,ola,deltaTime);
        //processInput_Camada2(window,ola,deltaTime);
        
        if (autoRotarCamara) {
            anguloCamara += velRotacionCam;
            if (anguloCamara >= 360.0f) anguloCamara -= 360.0f;
        }

        if (autoRotarCamaraX) {
            anguloCamaraX += velRotacionCam;
            if (anguloCamaraX >= 360.0f) anguloCamaraX -= 360.0f;
        }
        
        glClearColor(0.02f, 0.02f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Matrix view = obtenerMatrizVista();
        misShaders.SetView(view);
        // RENDERIZADO DEL CUBO
        ola.dibujarcaras(misShaders);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

Matrix obtenerMatrizVista() {
    Matrix T = matris::traslacion(-camPosX, -camPosY, -camPosZ);
    Matrix R_Inclinacion = matris::rotacionX(25.0f);

    Matrix R_OrbitarY = matris::rotacionY(anguloCamara);
    Matrix R_OrbitarX = matris::rotacionX(anguloCamaraX);
    Matrix R_Orbitar = matris::multiplicar(R_OrbitarY, R_OrbitarX);

    Matrix vistaBase = matris::multiplicar(R_Inclinacion, T);

    return matris::multiplicar(vistaBase, R_Orbitar);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Controles de Camara (R/T)
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) autoRotarCamara = true;  
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) autoRotarCamara = false; 
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) autoRotarCamaraX = true;  
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) autoRotarCamaraX= false; 
    // Movimiento libre de la camara (I, K, J, L, U, O)
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) camPosY += velCamara;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) camPosY -= velCamara;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) camPosX -= velCamara;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) camPosX += velCamara;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) camPosZ -= velCamara;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) camPosZ += velCamara;   


}
 
void processInput_Camada(GLFWwindow* window, CRubik& cubo, float deltaTime) {
    static bool upAnterior = false;
    static bool frontAnterior = false;
    static bool backAnterior = false;
    static bool downAnterior = false;
    static bool rightAnterior = false;
    static bool leftAnterior = false;
    static bool centerXAnterior = false;
    static bool centerZAnterior = false;
    static bool centerYAnterior = false;

    static bool flechaIzquierdaAnterior = false;
    static bool flechaDerechaAnterior = false;
    static bool reiniciarAnterior = false;

    static bool camadaSeleccionada = false;
    static bool rotando = false;
    static float anguloAcumulado = 0.0f;
    static float sentidoRotacion = 1.0f;
    static Camada ejeRotacion = FRONT;

    const float velocidad = 120.0f;

    bool upActual = glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS;
    bool frontActual = glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS;
    bool backActual = glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS;
    bool downActual = glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS;
    bool leftActual = glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS;
    bool rightActual = glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS;
    bool centerXActual = glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS;
    bool centerZActual = glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS;
    bool centerYActual = glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS;

    bool flechaIzquierdaActual = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
    bool flechaDerechaActual = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
    bool reiniciarActual = glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS;

    if (!rotando) {
        if (reiniciarActual && !reiniciarAnterior) {
            cubo.reiniciar();
            camadaSeleccionada = false;
        }

        if (upActual && !upAnterior) {
            ejeRotacion = FRONT;
            camadaSeleccionada = true;
        }
        else if (frontActual && !frontAnterior) {
            ejeRotacion = UP;
            camadaSeleccionada = true;
        }
        else if (backActual && !backAnterior) {
            ejeRotacion = BACK;
            camadaSeleccionada = true;
        }
        else if (downActual && !downAnterior) {
            ejeRotacion = DOWN;
            camadaSeleccionada = true;
        }
        else if (leftActual && !leftAnterior) {
            ejeRotacion = LEFT;
            camadaSeleccionada = true;
        }
        else if (rightActual && !rightAnterior) {
            ejeRotacion = RIGHT;
            camadaSeleccionada = true;
        }
        else if (centerXActual && !centerXAnterior) {
            ejeRotacion = CENTERX;
            camadaSeleccionada = true;
        }
        else if (centerZActual && !centerZAnterior) {
            ejeRotacion = CENTERZ;
            camadaSeleccionada = true;
        }
        else if (centerYActual && !centerYAnterior) {
            ejeRotacion = CENTERY;
            camadaSeleccionada = true;
        }

        if (camadaSeleccionada) {
            if (flechaDerechaActual && !flechaDerechaAnterior) {
                sentidoRotacion = 1.0f;
                anguloAcumulado = 0.0f;
                rotando = true;
            }
            else if (flechaIzquierdaActual && !flechaIzquierdaAnterior) {
                sentidoRotacion = -1.0f;
                anguloAcumulado = 0.0f;
                rotando = true;
            }
        }
    }

    if (rotando) {
        float paso = velocidad * deltaTime;
        if (anguloAcumulado + paso >= 90.0f) {
            paso = 90.0f-anguloAcumulado;
        }

        cubo.rotar_Camada(ejeRotacion, sentidoRotacion*paso);
        anguloAcumulado += paso;

        if (anguloAcumulado >= 90.0f) {
            anguloAcumulado = 0.0f;
            rotando = false;
        }
    }

    upAnterior = upActual;
    frontAnterior = frontActual;
    backAnterior = backActual;
    downAnterior = downActual;
    leftAnterior = leftActual;
    rightAnterior = rightActual;
    centerXAnterior = centerXActual;
    centerZAnterior = centerZActual;
    centerYAnterior = centerYActual;
    flechaIzquierdaAnterior = flechaIzquierdaActual;
    flechaDerechaAnterior = flechaDerechaActual;
    reiniciarAnterior = reiniciarActual;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}