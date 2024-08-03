// ImguiProject.cpp : Defines the entry point for the application.
//

#include "UseImgui.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


using namespace std;




int main()
{
	if (!glfwInit()) {
		return 1;
	}

	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); // Transparent framebuffer
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(1980, 1050, "Dear Imgui - Test", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw("Unable to context to OpenGL");



	int screen_width, screen_height;

	UseImGui myimgui;
	myimgui.Init(window,glsl_version);

	
	
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glfwGetFramebufferSize(window, &screen_width, &screen_height);
		glViewport(0, 0, screen_width, screen_height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
		myimgui.NewFrame();
		
		
		myimgui.Update();
		myimgui.Render();


		glfwSwapBuffers(window);
	}

	myimgui.Shutdown();

	return 0;
}


