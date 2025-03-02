#include"Model.h"
#include"Cube.h"

const unsigned int width = 1920;
const unsigned int height = 1080;
float aspectRatio = (float)width / (float)height;



int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL_Learning", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);



	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	
	glm::vec4 lightColor = glm::vec4(1.0f, 0.5f, 0.5f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 20.0f, 20.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
	unsigned int projLocation = glGetUniformLocation(shaderProgram.ID, "projection");
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f), aspectRatio);

	
	Model model1("models/bunny/scene.gltf");
	Model model2("models/scroll/scene.gltf");
	Model model3("models/sword/scene.gltf");

	Cube cube1;
	cube1.setPosition(glm::vec3(10.0f, 10.0f, 10.0f));
	cube1.loadTexture("stoneTexture.png");
	
	// Original code from the tutorial
	// Model model("models/bunny/scene.gltf");

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.13f, 0.40f, 0.40f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	
		camera.Inputs(window);
		// Camera setings (FOFdeg, nearPlane, View distanse)
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// shaderProgram, camera, scaleFactor(scales the model)
		model1.Draw(shaderProgram, camera, 20.05f);
		model2.Draw(shaderProgram, camera, 0.05f);
		model3.Draw(shaderProgram, camera, 0.1f);

		
		cube1.draw(shaderProgram.ID);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}