#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<GL\glew.h> 
#include <glm/glm.hpp>

#include"Shader.h"



using namespace std;

//vertex shader coding part
//fragment shader coding part

void main()
{
	GLint wid = 800; //*window variable
	GLint height = 800; //*window variable
	GLFWwindow* window; //pointer var as window that will hold address only 
	glfwInit();

	if (!glfwInit())
	{
		cout << "glfw lib error"<<endl;
	}
	else
		cout << "glfw success"<<endl;
	window = glfwCreateWindow(wid, height, "Window with background color", NULL, NULL); //*assigned window variable 

	// make the window context current
	glfwMakeContextCurrent(window);

	// 2.   **************** here must add glew function use*********
	if (glewInit() != GLEW_OK)
	{
		cout << "fail to open glew\n";

	}
	else
		cout << "glew works success\n";
	// till here glew stuff		//vertex shader			//fragment shader		//Shader linking of vertex and fragment shader

	//Attaching shader Files 
	Shader shaders("Test.vs","Test.frag");

	// generate a list of 100 quad locations/translation-vectors

	glm::vec2 translations[100];
	int index = 0;
	float offset = 0.1f;
	for (int y = -10; y < 10; y += 2)
	{
		for (int x = -10; x < 10; x += 2)
		{
			glm::vec2 translation;
			translation.x = (float)x / 10.0f + offset;
			translation.y = (float)y / 10.0f + offset;
			translations[index++] = translation;
		}
	}

	//buffer for instance
	unsigned int instanceVBO;
	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	GLfloat vertices[] =
	{
		//-0.5f, -0.5f, 0.0f,
		// 0.5f, -0.5f, 0.0f,
		// 0.0f,  0.5f, 0.0f

		// for Triangle
		////position(x,y) color(rgb)
		//-0.05f,  0.05f, 1.0f, 0.0f, 0.0f,
		// 0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
		//-0.05f, -0.05f, 0.0f, 0.0f, 1.0f

		//for quad
		//position(x,y) color(rgb)
		-0.05f,  0.05f, 1.0f, 0.0f, 0.0f,
		 0.05f,  0.05f, 1.0f, 0.0f, 1.0f,
		 0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
		-0.05f, -0.05f, 0.0f, 0.0f, 1.0f
		 


	};

	GLuint VBO, VAO;//vertex buffer obj//vert array obj
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 *sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// also set instance data
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//gameloop
	while (!glfwWindowShouldClose(window))
	{
		//for the bg color
		glClearColor(0, 0, 0, 0); //for rgb color change
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//to clear the buffer

		//linking the shader / calling the shader
		shaders.Use();

		//6 must pass parameter vao to see visibility of drawing 
		glBindVertexArray(VAO);

		//drawing
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 100);
		glDrawArraysInstanced(GL_QUADS, 0, 4, 100);

		//glBindVertexArray();

		glfwSwapBuffers(window);//to swap the new color for window
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
}