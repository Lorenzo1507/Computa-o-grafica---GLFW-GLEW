//Biblioteca principal onde podemos dar printf e fazer todo o b�sico
#include <iostream>
//administra as extens�es do opengl
#include "GL/glew.h"
//glfw cria janelas 
#include "GLFW/glfw3.h"

GLuint VAO, VBO, programa;

//Vertex Shader. usar espa�os depois apertar o bot�o insert para deixar todas as quebras de linha ajeitadas, apenas mais uma quest�o visual
static const char* vShader = "                                       \n\
#version 330                                                         \n\
                                                                     \n\
layout(location=0) in vec2 pos;                                      \n\
                                                                     \n\
                                                                     \n\
void main(){                                                         \n\
    gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);                      \n\
}                                                                    \n\
																	";

static const char* fShader = "                                       \n\
#version 330                                                         \n\
                                                                     \n\
layout(location=0) in vec2 pos;                                      \n\
                                                                     \n\
                                                                     \n\
void main(){                                                         \n\
    gl_Position = vec4(1.0, 0.0, 0.0, 1.0);                          \n\
}                                                                    \n\
																	";


void criarTriangulos()
{
	GLfloat vertices[] = {
		//x, y
		0.0f, 1.0f,
		-1.0f, -1.0f,
		1.0f, -1.0f
	};

	//Cria o VAO (s�o todas as propriedades de um vertice como cores, transforma��o, etc... s� tem um VAO por programa)
	glGenVertexArrays(1, &VAO);
	//Coloca o VAO em contexto
	glBindVertexArray(VAO);
		//O tab � apenas visual, mas � s� para sabermos que o VBO surge atrav�s do VAO
		//No VBO guarda os dados reais do vertice (como posi��o, cores, etc. pode ter mais de um VBO)
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			//Explica os valores de x e y (mostra onde come�a, pula dois itens para ler apenas o x e y e n�o o z e o rgba)
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); //remover do contexto o VAO
}

void CompilaShader() {
	//Cria um programa
	programa = glCreateProgram();
	GLuint _vShader = glCreateShader(GL_VERTEX_SHADER); //Cria um shader
	GLuint _fShader = glCreateShader(GL_FRAGMENT_SHADER); //Cria um shader

	//Cria um valor tipo char com 1 dado apenas dentro do array. Um tipo de gambiarra para converter chaar em GLChar
	const GLchar* vCode[1];
	const GLchar* fCode[1];

	vCode[0] = vShader; //Codigo do vShader
	fCode[0] = fShader; //Codigo do fShader

	glShaderSource(_vShader, 1, vCode, NULL); //associa o shader ao c�digo
	glCompileShader(_vShader); //Compila o shader

	glShaderSource(_fShader, 1, fCode, NULL); //associa o shader ao c�digo
	glCompileShader(_fShader); //Compila o shader

	glAttachShader(programa, _vShader);
	glAttachShader(programa, _fShader);
}

int main() {
	//Se n�o conseguir incializar
	if (!glfwInit())
	{
		printf("GLFW: N�o pode ser inicializado");
		return 1;
	}

	//Classe para criar o objeto da janela
	GLFWwindow *mainWindow = glfwCreateWindow(800, 600, "Sekai wo hakai koto ni shita no da", NULL, NULL);

	if (!mainWindow)
	{
		printf("GLFW: erro ao criar a janela.");
		//Usa terminate para n�o ficar ocupando espa�o atoa na mem�ria
		glfwTerminate();
		return 1;
	}

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//Fun��o para definir uma janela com principal
	glfwMakeContextCurrent(mainWindow);

	//Se o glew (gerenciador de exten��es) n�o conseguir inicializar
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW: N�o pode ser inicializado");

		//Essas duas fun��es s�o usadas para limpar o espa�o de mem�ria por completo
		glfwDestroyWindow(mainWindow);
		glfwTerminate();

		return 1;
	}

	glViewport(0, 0, bufferWidth, bufferHeight);

	criarTriangulos();
	CompilaShader();

	//Enquanto a janela n�o deveria fechar
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Habilita os eventos de usuario
		glfwPollEvents();

		glClearColor(1.0f, 0.75f, 0.79f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		//Desenha o triangulo
		glUseProgram(programa);
			glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();

	return 0;
}
