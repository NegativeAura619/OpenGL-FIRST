#include <iostream>
#include <glad/glad.h> // glad musi byc zalinkowany przed GLFW	
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

	void framebuffer_size_callback(GLFWwindow * window, int width, int height);
	void processInput(GLFWwindow * window);

	const unsigned int SCR_WIDTH = 800; // CONST WINDOW WIDTH 
	const unsigned int SCR_HEIGHT = 800; // CONST WINDOW HEIGHT 


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
	
	


	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "YoutubeOpenGl", NULL, NULL); // parametry okienka  szerokosc,wysokosc,nazwa,fullscreen i ?
	if (window == NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl; // sprawdza czy okienko sie nie crashuje	
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // wymusza uzywanie okienka ktore zainicjowalismy
	gladLoadGL(); // ladowanie glada by konfigurowac opengl
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //creating shader stored in GLuint
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // reference value,how many strings for shader, source code point
	glCompileShader(vertexShader); // compilating shader into the machine code sow gpu can understand it 



	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //creating shader stored in GLuint
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader); 

	GLuint shaderProgram = glCreateProgram(); //tworzenie shader programu do uzycia shaderow

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader); // dodawanie shaderow do Shader programu 

	glLinkProgram(shaderProgram); // Creating shader program executable and linking it so it can run over Vertexes

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader); // usuwanie shaderow poniewa¿ s¹ juz w programie 

	GLuint VAO,VBO; // przechowuje dane z vertexu

	glGenVertexArrays(1, &VAO);// generowanie danych do VAO

	glGenBuffers(1, &VBO); // generuje 1 obiekt i linkuje go z VBO

	glBindVertexArray(VAO);//to samo co VBO

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // binduje buffer
	//uwaga wazne jest by generowac VAO przed VBO !!! 


	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // static oznacza ze vertices zostanie zmodyfikowany tylk oraz 
	//draw oznacza ze vertices  zostanie zmodyfikowany by utworzyc obraz na ekranie
	// jest jeszcze read oraz copy 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // komunikuje sie z vertex shaderem
	// pozycja atrybutu, ile wartosci mamy w wertexie (3 poniewaz robimy trojkat),data type vortexu , ostatni ma znaczenie gdy mamy koordynaty w intach
	// nastepnie ilosc danych miedzy vortexami mamy 3 floaty wiec wpisujemy 3 * rozmiar floata
	//offset pointer ktory wskazuje gdzie vortex zaczyna array, jako ze nasz zaczyna sie na poczatku tabeli dajemy wartosc void 
	glEnableVertexAttribArray(0); // uruchamia dane vertexu ktore wspialismy wyzej, dajemy 0 poniewaz to jest pozycja naszego atrybutu vortexa

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0); // przypisuje im 0 by nie pomylic sie i nie uzyc ich jako funkcji co zjebie program


	glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // kolor nastepnej klatki 
	glClear(GL_COLOR_BUFFER_BIT); //inicjalizacja koloru
	glfwSwapBuffers(window); // swap klatki 
	

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window); // updatujemy obraz co klatke

		glfwPollEvents(); // procesowanie parametrow okienka
		
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate(); // wylaczenie okienka
	return 0;

}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)

{ // Updating position while resising window

	glViewport(0, 0, width, height);  
}

