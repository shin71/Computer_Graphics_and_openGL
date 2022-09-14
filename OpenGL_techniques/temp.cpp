#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
float* vertices;
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
void framebuffer_size_callback(GLFWwindow* ptr,int width,int height)
{
	glViewport(0, 0, width, height);
}
void process_input(GLFWwindow* ptr)
{
	if (glfwGetKey(ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(ptr, true);
	}
}

void dda(float x1,float y1,float x2,float y2)
{
	float dx = x2 - x1, dy = y2 - y1;
	int steps = 0;
	dy > dx ? steps = int(dy) : steps = int(dx);
	float x_inc = dx / steps;
	float y_inc = dy / steps;
	vertices = new float[steps * 3];
	vertices[0] = int(x1 + 0.5);
	vertices[1] = int(y1 + 0.5);
	vertices[2] = 0.0;
	for (int i = 1; i <= steps-1; i++)
	{
		x1 += x_inc;
		y1 += y_inc;
		vertices[3 * i] = int(x1 + 0.5);
		vertices[3 * i + 1] = int(y1 + 0.5);
		vertices[3 * i + 2] = 0.0;

	}
}
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window_ptr = glfwCreateWindow(800, 600, "this is dda algorithm",NULL,NULL);
	if (window_ptr == NULL)
	{
		std::cout << "there seems to be a error\n";
		return -1;
	}
	glfwMakeContextCurrent(window_ptr);
	glfwSetFramebufferSizeCallback(window_ptr, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "function pointers not set\n";
		return -1;
	}
	dda(0.0,0.0, 4.0, 4.0);
	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// link shaders
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int vao, vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	while (!glfwWindowShouldClose(window_ptr))
	{
		process_input(window_ptr);
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
	}
	delete vertices;
	glDeleteBuffers(1,&vbo);
	glDeleteVertexArrays(1, &vao);
	glfwTerminate();
}
