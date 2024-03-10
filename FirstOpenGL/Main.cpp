#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{

	glfwInit(); // inicjalizacja okienka


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //wybor wersji
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // wybor profilu openGL


	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // left corner
		 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // right corner 
		 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // top corner
	};



	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGl", NULL, NULL); // parametry okienka  szerokosc,wysokosc,nazwa,fullscreen i ?
	if (window == NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl; // sprawdza czy okienko sie nie crashuje	
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // wymusza uzywanie okienka ktore zainicjowalismy

	gladLoadGL(); // ladowanie glada by konfigurowac opengl



	glViewport(0,0, 800,800); //koordynaty obszaru ktory chcemy wyswietlac

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //tworzymy shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // przypisujemy parametry
	glCompileShader(vertexShader); // kompilacja shadera


	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // To samo co wy¿ej tylko z fragmentami
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader); 

	GLuint shaderProgram = glCreateProgram(); //tworzenie shader programu do uzycia shaderow

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader); // dodawanie shaderow do Shader programu 

	glLinkProgram(shaderProgram); // wrapowanie shader programu

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader); // usuwanie shaderow poniewa¿ s¹ juz w programie 


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