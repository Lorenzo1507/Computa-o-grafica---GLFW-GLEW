//Biblioteca principal onde podemos dar printf e fazer todo o b�sico
#include <iostream>
//administra as extens�es do opengl
#include "GL/glew.h"
//glfw cria janelas 
#include "GLFW/glfw3.h"

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

	//Enquanto a janela n�o deveria fechar
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Habilita os eventos de usuario
		glfwPollEvents();

		glClearColor(1.0f, 0.75f, 0.79f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow);
	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();

	return 0;
}
