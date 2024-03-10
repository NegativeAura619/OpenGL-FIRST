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

	gladLoadGL();



	glViewport(0,0, 800,800); //koordynaty obszaru ktory chcemy wyswietlac

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // kolor nastepnej klatki 
	glClear(GL_COLOR_BUFFER_BIT); //inicjalizacja koloru
	glfwSwapBuffers(window); // swap klatki 

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents(); // procesowanie parametrow okienka
	}



	glfwDestroyWindow(window);
	glfwTerminate(); // wylaczenie okienka
	return 0;
}