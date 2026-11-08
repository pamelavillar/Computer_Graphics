#include "CRubik.h"

#include <vector>

vector<vector<float>> coloresRubik = {

    { 1.0f,  1.0f,  1.0f  }, // Blanco  

    { 1.0f,  1.0f,  0.0f  }, // Amarillo

    { 0.0f,  0.8f,  0.0f  }, // Verde   

    { 0.0f,  0.2f,  1.0f  }, // Azul    

    { 0.9f,  0.0f,  0.0f  }, // Rojo    

    { 1.0f,  0.5f,  0.0f  }  // Naranja 

};

vector<float> Cnegro={0.0f,0.0f,0.0f};

vector<float> Cblanco={1.0f,  1.0f,  1.0f};

vector<float> Camarillo={1.0f,  1.0f,  0.0f};

vector<float> Cverde={0.0f,  0.8f,  0.0f};

vector<float> Cazul={0.0f,  0.2f,  1.0f};

vector<float> Crojo={0.9f,  0.0f,  0.0f};

vector<float> Cnaranja={1.0f,  0.5f,  0.0f};

CRubik::CRubik(){
	bloques.resize(26);
	for(int i=0;i<bloques.size();i++){
		bloques[i]=new Cubo();
		bloques[i]->escalar(0.96f, 0.96f, 0.96f);
	}


	bloques[0]->trasladar(-1.0f,1.0f,1.0f);//bloque 1 
	bloques[1]->trasladar(0.0f,1.0f,1.0f);//bloque 2
	bloques[2]->trasladar(1.0f,1.0f,1.0f);//bloque 3 
	bloques[3]->trasladar(-1.0f,0.0f,1.0f);//bloque 4 
	bloques[4]->trasladar(0.0f,0.0f,1.0f);//bloque 5 
	bloques[5]->trasladar(1.0f,0.0f,1.0f);//bloque 6 
	bloques[6]->trasladar(-1.0f,-1.0f,1.0f);//bloque 7 
	bloques[7]->trasladar(0.0f,-1.0f,1.0f);//bloque 8 
	bloques[8]->trasladar(1.0f,-1.0f,1.0f);//bloque 9 

	bloques[9]->trasladar(-1.0f,1.0f,0.0f);//bloque 10 
	bloques[10]->trasladar(0.0f,1.0f,0.0f);//bloque 11
	bloques[11]->trasladar(1.0f,1.0f,0.0f);//bloque 12
	bloques[12]->trasladar(-1.0f,0.0f,0.0f);//bloque 13
	bloques[13]->trasladar(1.0f,0.0f,0.0f);//bloque 14
	bloques[14]->trasladar(-1.0f,-1.0f,0.0f);//bloque 15
	bloques[15]->trasladar(0.0f,-1.0f,0.0f);//bloque 16 
	bloques[16]->trasladar(1.0f,-1.0f,0.0f);//bloque 17
	bloques[17]->trasladar(-1.0f,1.0f,-1.0f);//bloque 18 

	bloques[18]->trasladar(0.0f,1.0f,-1.0f);//bloque 19 
	bloques[19]->trasladar(1.0f,1.0f,-1.0f);//bloque 20 
	bloques[20]->trasladar(-1.0f,0.0f,-1.0f);//bloque 21 
	bloques[21]->trasladar(0.0f,0.0f,-1.0f);//bloque 22 
	bloques[22]->trasladar(1.0f,0.0f,-1.0f);//bloque 23 
	bloques[23]->trasladar(-1.0f,-1.0f,-1.0f);//bloque 24 
	bloques[24]->trasladar(0.0f,-1.0f,-1.0f);//bloque 25 
	bloques[25]->trasladar(1.0f,-1.0f,-1.0f);//bloque 26	 
	
	for(int i = 0; i < 9; i ++){
		camada1.push_back(bloques[0+i]);
	}

	camada2.push_back(bloques[0]);
	camada2.push_back(bloques[1]);
	camada2.push_back(bloques[2]);
	camada2.push_back(bloques[9]);
	camada2.push_back(bloques[10]);
	camada2.push_back(bloques[11]);
	camada2.push_back(bloques[18]);
	camada2.push_back(bloques[19]);
	camada2.push_back(bloques[17]);

	for(int i = 0; i < 9; i ++){
		camada3.push_back(bloques[17+i]);
	}

	camada4.push_back(bloques[6]);
	camada4.push_back(bloques[7]);
	camada4.push_back(bloques[8]);
	camada4.push_back(bloques[14]);
	camada4.push_back(bloques[15]);
	camada4.push_back(bloques[16]);
	camada4.push_back(bloques[24]);
	camada4.push_back(bloques[25]);
	camada4.push_back(bloques[23]);


	camada5.push_back(bloques[0]);
	camada5.push_back(bloques[3]);
	camada5.push_back(bloques[6]);
	camada5.push_back(bloques[9]);
	camada5.push_back(bloques[12]);
	camada5.push_back(bloques[14]);
	camada5.push_back(bloques[17]);
	camada5.push_back(bloques[20]);
	camada5.push_back(bloques[23]);

	camada6.push_back(bloques[2]);
	camada6.push_back(bloques[5]);
	camada6.push_back(bloques[8]);
	camada6.push_back(bloques[11]);
	camada6.push_back(bloques[13]);
	camada6.push_back(bloques[16]);
	camada6.push_back(bloques[19]);
	camada6.push_back(bloques[22]);
	camada6.push_back(bloques[25]);


	for(int i = 0; i < 8; i ++){
		camada7.push_back(bloques[9+i]);
	}

	camada8.push_back(bloques[1]);
	camada8.push_back(bloques[4]);
	camada8.push_back(bloques[7]);
	camada8.push_back(bloques[10]);
	camada8.push_back(bloques[15]);
	camada8.push_back(bloques[18]);
	camada8.push_back(bloques[21]);
	camada8.push_back(bloques[24]);

	camada9.push_back(bloques[3]);
	camada9.push_back(bloques[4]);
	camada9.push_back(bloques[5]);
	camada9.push_back(bloques[12]);
	camada9.push_back(bloques[13]);
	camada9.push_back(bloques[20]);
	camada9.push_back(bloques[21]);
	camada9.push_back(bloques[22]);
	

	colorearcubos();

	for (Cubo* bloque : bloques) {
		bloque->transformadorInicial = bloque->transformador;
	}
}

void CRubik::reiniciar() {
	for (Cubo* bloque : bloques) {
		bloque->transformador = bloque->transformadorInicial;
	}
	actualizarCamadas();
}


void CRubik::colorearcubos(){
	
    bloques[0]->mandarColores({Cnegro, Cblanco, Cverde, Cnegro, Cnegro, Cnaranja}); // bloque 1
    bloques[1]->mandarColores({Cnegro, Cblanco, Cnegro, Cnegro, Cnegro, Cnaranja}); // bloque 2
    bloques[2]->mandarColores({Cnegro, Cblanco, Cnegro, Cazul, Cnegro, Cnaranja}); // bloque 3
    bloques[3]->mandarColores({Cnegro, Cblanco, Cverde, Cnegro, Cnegro, Cnegro}); // bloque 4
    bloques[4]->mandarColores({Cnegro, Cblanco, Cnegro, Cnegro, Cnegro, Cnegro}); // bloque 5
    bloques[5]->mandarColores({Cnegro, Cblanco, Cnegro, Cazul, Cnegro, Cnegro}); // bloque 6
    bloques[6]->mandarColores({Cnegro, Cblanco, Cverde, Cnegro, Crojo, Cnegro}); // bloque 7
    bloques[7]->mandarColores({Cnegro, Cblanco, Cnegro, Cnegro, Crojo, Cnegro}); // bloque 8
    bloques[8]->mandarColores({Cnegro, Cblanco, Cnegro, Cazul, Crojo, Cnegro}); // bloque 9

    bloques[9]->mandarColores({Cnegro, Cnegro, Cverde, Cnegro, Cnegro, Cnaranja}); // bloque 10
    bloques[10]->mandarColores({Cnegro, Cnegro, Cnegro, Cnegro, Cnegro, Cnaranja}); // bloque 11
    bloques[11]->mandarColores({Cnegro, Cnegro, Cnegro, Cazul, Cnegro, Cnaranja}); // bloque 12
    bloques[12]->mandarColores({Cnegro, Cnegro, Cverde, Cnegro, Cnegro, Cnegro}); // bloque 13
    bloques[13]->mandarColores({Cnegro, Cnegro, Cnegro, Cazul, Cnegro, Cnegro}); // bloque 14
    bloques[14]->mandarColores({Cnegro, Cnegro, Cverde, Cnegro, Crojo, Cnegro}); // bloque 15
    bloques[15]->mandarColores({Cnegro, Cnegro, Cnegro, Cnegro, Crojo, Cnegro}); // bloque 16
    bloques[16]->mandarColores({Cnegro, Cnegro, Cnegro, Cazul, Crojo, Cnegro}); // bloque 17

    bloques[17]->mandarColores({Camarillo, Cnegro, Cverde, Cnegro, Cnegro, Cnaranja}); // bloque 18
    bloques[18]->mandarColores({Camarillo, Cnegro, Cnegro, Cnegro, Cnegro, Cnaranja}); // bloque 19
    bloques[19]->mandarColores({Camarillo, Cnegro, Cnegro, Cazul, Cnegro, Cnaranja}); // bloque 20
    bloques[20]->mandarColores({Camarillo, Cnegro, Cverde, Cnegro, Cnegro, Cnegro}); // bloque 21
    bloques[21]->mandarColores({Camarillo, Cnegro, Cnegro, Cnegro, Cnegro, Cnegro}); // bloque 22
    bloques[22]->mandarColores({Camarillo, Cnegro, Cnegro, Cazul, Cnegro, Cnegro}); // bloque 23
    bloques[23]->mandarColores({Camarillo, Cnegro, Cverde, Cnegro, Crojo, Cnegro}); // bloque 24
    bloques[24]->mandarColores({Camarillo, Cnegro, Cnegro, Cnegro, Crojo, Cnegro}); // bloque 25
    bloques[25]->mandarColores({Camarillo, Cnegro, Cnegro, Cazul, Crojo, Cnegro}); // bloque 26

		
	
	for(int i = 0; i < 9; i++){
		string ruta = "src/cubo_textura/images/" + to_string(i + 1) + ".jpg";

		bloques[i]->asignarTexturaCara(CARA_FRENTE, ruta);
	}

	for(int i = 0; i < 9; i++){
		string ruta = "src/cubo_textura/images/c/" + to_string(i + 1) + ".png";
		camada6[i]->asignarTexturaCara(CARA_DERECHA, ruta);
	}

	for(int i = 0; i < 9; i++){
		string ruta = "src/cubo_textura/images/s/" + to_string(i + 1) + ".jpg";
		camada3[i]->asignarTexturaCara(CARA_ATRAS, ruta);
	}

	for(int i = 0; i < 9; i++){
		string ruta = "src/cubo_textura/images/p/" + to_string(i + 1) + ".jpg";
		camada5[i]->asignarTexturaCara(CARA_IZQUIERDA, ruta);
	}

	for(int i = 0; i < 3; i++){
		string ruta = "src/cubo_textura/images/c/" + to_string((i + 1)*3) + ".png";
		camada2[i]->asignarTexturaCara(CARA_ARRIBA, ruta);

	}

	camada2[3]->asignarTexturaCara(CARA_ARRIBA, "src/cubo_textura/images/c/2.png");
	camada2[4]->asignarTexturaCara(CARA_ARRIBA, "src/cubo_textura/images/c/5.png");
	camada2[5]->asignarTexturaCara(CARA_ARRIBA, "src/cubo_textura/images/c/8.png");
	camada2[6]->asignarTexturaCara(CARA_ARRIBA, "src/cubo_textura/images/c/4.png");
	camada2[7]->asignarTexturaCara(CARA_ARRIBA, "src/cubo_textura/images/c/7.png");
	camada2[8]->asignarTexturaCara(CARA_ARRIBA, "src/cubo_textura/images/c/1.png");

	for(int i = 0; i < 9; i++){
		string ruta = "src/cubo_textura/images/g/" + to_string(i + 1) + ".jpg";
		camada4[i]->asignarTexturaCara(CARA_ABAJO, ruta);
	}
	

}

void CRubik::dibujarcaras(Shaders& shader){
	for(int i=0;i<26;i++){
		bloques[i]->dibujar(shader);
		bloques[i]->dibujarLineas(shader);
	}
}

void CRubik::dibujarlineas(Shaders& shader){
	for(int i=0;i<26;i++){
		bloques[i]->dibujarLineas(shader);
	}
}

void CRubik::dibujarpuntos(Shaders& shader){

	for(int i=0;i<26;i++){
		bloques[i]->dibujarConModo(shader);
	}
}

void CRubik::rotar_Camada(Camada camada, float deltaTime){
	if(camada == FRONT){
		for(int i = 0; i < 9; i++){
			camada1[i]->rotarZ(deltaTime);
		}
	}

	else if(camada == UP){
		for(int i = 0; i < 9; i++){
			camada2[i]->rotarY(deltaTime);
		}
	}

	else if(camada == BACK){
		for(int i = 0; i < 9; i++){
			camada3[i]->rotarZ(deltaTime);
		}
	}

	else if(camada == DOWN){
		for(int i = 0; i < 9; i++){
			camada4[i]->rotarY(deltaTime);
		}
	}

	else if(camada == LEFT){
		for(int i = 0; i < 9; i++){
			camada5[i]->rotarX(deltaTime);
		}
	}

	else if(camada == RIGHT){
		for(int i = 0; i < 9; i++){
			camada6[i]->rotarX(deltaTime);
		}
	}

	else if(camada == CENTERX){
		for(int i = 0; i < 8; i++){
			camada7[i]->rotarZ(deltaTime);
		}
	}
	else if(camada == CENTERZ){
		for(int i = 0; i < 8; i++){
			camada8[i]->rotarX(deltaTime);
		}
	}
	else if(camada == CENTERY){
		for(int i = 0; i < 8; i++){
			camada9[i]->rotarY(deltaTime);
		}
	}
	actualizarCamadas();
}

void CRubik::actualizarCamadas() {
    camada1.clear();
    camada2.clear();
	camada3.clear();
	camada4.clear();
	camada5.clear();
	camada6.clear();
	camada7.clear();
	camada8.clear();
	camada9.clear();

    for (Cubo* cubo : bloques) {
        Matrix& M = cubo->transformador;
        float x = M.matrix[12];
        float y = M.matrix[13];
        float z = M.matrix[14];

        if (abs(z - 1.0f) < 0.1f) {
            camada1.push_back(cubo);
        }

        if (abs(y - 1.0f) < 0.1f) {
            camada2.push_back(cubo);
        }
		if (abs(z + 1.0f) < 0.1f) {
            camada3.push_back(cubo);
        }
		if (abs(y + 1.0f) < 0.1f) {
            camada4.push_back(cubo);
        }
		if (abs(x + 1.0f) < 0.1f) {
            camada5.push_back(cubo);
        }
		if (abs(x - 1.0f) < 0.1f) {
            camada6.push_back(cubo);
        }
		if (abs(z) < 0.1f) {
            camada7.push_back(cubo);
        }

		if (abs(x) < 0.1f) {
            camada8.push_back(cubo);
        }

		if (abs(y) < 0.1f) {
            camada9.push_back(cubo);
        }
    }
}
