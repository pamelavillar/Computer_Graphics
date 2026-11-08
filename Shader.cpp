#include "Shader.h"


const char* vertex_shader="#version 330 core\n"
"layout (location=0) in vec3 inVec;\n"
"layout (location=1) in vec2 inTexCoord;\n"
"out vec2 TexCoord;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main(){\n"
"	gl_Position=projection*view*model*vec4(inVec.xyz,1.0f);\n"
"	TexCoord=inTexCoord;\n"
"}\n";

const char* fragment_shader="#version 330 core\n"
"in vec2 TexCoord;\n"
"uniform vec3 ouCol;\n"
"uniform sampler2D textura;\n"
"uniform int usarTextura;\n"
"out vec4 outColor;\n"
"void main(){\n"
"	if(usarTextura==1)\n"
"		outColor = mix(texture(textura, TexCoord), vec4(ouCol.rgb, 1.0f), 0.7);\n" 

"	else\n"
"		outColor=vec4(ouCol.rgb,1.0f);\n"
"}\n";

Shaders::Shaders(){
	int sucess;
	char infoLog[512];
	
	vertex_shad_id=glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shad_id,1,&vertex_shader,NULL);
	glCompileShader(vertex_shad_id);
	
	glGetShaderiv(vertex_shad_id,GL_COMPILE_STATUS,&sucess);
	if(!sucess){
		glGetShaderInfoLog(vertex_shad_id,512,NULL,infoLog);
		std::cout << "ERROR IN VERTEX SHADER ->" << infoLog << std::endl;
	}
	
	fragment_shad_id=glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shad_id,1,&fragment_shader,NULL);
	glCompileShader(fragment_shad_id);
	
	glGetShaderiv(fragment_shad_id,GL_COMPILE_STATUS,&sucess);
	if(!sucess){
		glGetShaderInfoLog(fragment_shad_id,512,NULL,infoLog);
		std::cout << "ERROR IN FRAGMENT SHADER -> " << infoLog << std::endl;
	}
	
	program_id=glCreateProgram();
	glAttachShader(program_id,vertex_shad_id);
	glAttachShader(program_id,fragment_shad_id);
	glLinkProgram(program_id);
	
	glGetProgramiv(program_id,GL_LINK_STATUS,&sucess);
	if(!sucess){
		glGetProgramInfoLog(program_id,512,NULL,infoLog);
		std::cout << "ERROR IN LINKING SHADERS -> " << infoLog << std::endl;
	}
	
	glDeleteShader(vertex_shad_id);
	glDeleteShader(fragment_shad_id);

	// El sampler usa la unidad 0 por defecto
	glUseProgram(program_id);
	glUniform1i(glGetUniformLocation(program_id,"textura"),0);
}

void Shaders::use(){
	glUseProgram(program_id);
}

unsigned int Shaders::GetProgram(){
	return this->program_id;
}

void Shaders::SetColor(const float &r,const float &g,const float &b){
	int Color_loc=glGetUniformLocation(this->program_id,"ouCol");
	
	if(Color_loc <= -1){
		std::cout << "ERROR or couldn't find the location :( " << std::endl;
		return;
	}
	
	glUniform3f(Color_loc,r,g,b);
}

void Shaders::SetMatrix(const Matrix& mat){
	int Model_loc=glGetUniformLocation(this->program_id,"model");
	
	if(Model_loc <= -1){
		std::cout << "ERROR or couldn't find the model :( " << std::endl;
		return;
	}
	glUniformMatrix4fv(Model_loc,1,GL_FALSE,mat.matrix.data());
}

void Shaders::SetView(const Matrix& mat){
	int Model_loc=glGetUniformLocation(this->program_id,"view");
	
	if(Model_loc <= -1){
		std::cout << "ERROR or couldn't find the view :( " << std::endl;
		return;
	}
	glUniformMatrix4fv(Model_loc,1,GL_FALSE,mat.matrix.data());
}

void Shaders::SetProjection(const Matrix& mat){
	int Model_loc=glGetUniformLocation(this->program_id,"projection");
	
	if(Model_loc <= -1){
		std::cout << "ERROR or couldn't find the projection :( " << std::endl;
		return;
	}
	glUniformMatrix4fv(Model_loc,1,GL_FALSE,mat.matrix.data());
}

void Shaders::SetUsarTextura(bool usar){
	int loc=glGetUniformLocation(this->program_id,"usarTextura");
	
	if(loc <= -1){
		std::cout << "ERROR or couldn't find usarTextura :( " << std::endl;
		return;
	}
	glUniform1i(loc,usar ? 1 : 0);
}

void Shaders::SetUnidadTextura(int unidad){
	int loc=glGetUniformLocation(this->program_id,"textura");
	
	if(loc <= -1){
		std::cout << "ERROR or couldn't find textura :( " << std::endl;
		return;
	}
	glUniform1i(loc,unidad);
}
