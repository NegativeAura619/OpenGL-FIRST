#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{

	glfwInit(); // inicjalizacja okienka


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //wybor wersji
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // wybor profilu openGL

	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGl", NULL, NULL); // parametry okienka  szerokosc,wysokosc,nazwa,fullscreen i ?
	if (window == NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl; // sprawdza czy okienko sie nie crashuje	
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // wymusza uzywanie okienka ktore zainicjowalismy

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents(); // procesowanie parametrow okienka
	}



	glfwDestroyWindow(window);
	glfwTerminate(); // wylaczenie okienka
	return 0;
}