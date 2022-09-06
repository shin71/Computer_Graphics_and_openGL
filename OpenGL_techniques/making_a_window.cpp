#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
void resize_func(GLFWwindow* ptr, int width, int height)
{
	//this tells opengl the size of rendering window
	glViewport(0, 0, 800, 600);
}
void processInput(GLFWwindow* ptr)
{
	if (glfwGetKey(ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(ptr, true);
	}

}
int main()
{
	//this is used to initialize opengl context
	glfwInit();
	//GLFW can make the proper arrangements when creating the OpenGL context if we tell the opengl version and profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//This window object holds all the windowing data and is required by most of GLFW’s other functions.
	GLFWwindow* window_ptr = glfwCreateWindow(800, 600, "THIS IS THE BEGINNING",NULL,NULL);
	if (window_ptr == NULL)
	{
		std::cout << "for some reason window is not formed\n";
		return -1;
	}
	//we tell GLFW to make the context of our window the main context on the current thread.
	glfwMakeContextCurrent(window_ptr);
	//GLAD manages function pointers for OpenGL so we want to initialize GLAD before we call any OpenGL function
	/* We pass GLAD the function to load the address of the OpenGL function pointers which is
	OS-specific. GLFW gives us glfwGetProcAddress that defines the correct function based on
	which OS we’re compiling for.*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}
	//this is the function which is set to be called every time user resizes the window
	glfwSetFramebufferSizeCallback(window_ptr, resize_func);

	//now we create the loop which renders our output
	while (!glfwWindowShouldClose(window_ptr))
	{
		// input
		processInput(window_ptr);
		
		//this is used to swap buffers
		glfwSwapBuffers(window_ptr);
		//this checks if any event has occured
		glfwPollEvents();

		//this is used to set the color of the buffer after we clear the screen
		glClearColor(1.0f,0.0f,0.0f,0.0f);
		//clearing the screen
		glClear(GL_COLOR_BUFFER_BIT);
	}
	/*As soon as we exit the render loop we would like to properly clean/delete all of GLFW’s resources
	that were allocated. We can do this via the glfwTerminate function that we call at the end of
	the main function*/
	glfwTerminate();
	return 0;
}