#include"Mesh.h"
#include"shaderHeader.h"

const unsigned int width = 800;
const unsigned int height = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char *triangleVertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec3 aColor;\n"
	"out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"   ourColor = aColor;\n"
	"}\0";

const char *triangleFragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
	"in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0);\n"
	"}\0";

float triangleVertices[] = {
	 0.9f,  0.9f, 0.0f,	1.0f, 0.0f, 0.0f, 0.9f, 0.9f,
	 0.9f, -0.9f, 0.0f, 0.0f, 1.0f, 0.0f, 0.9f, 0.0f,
	-0.9f, -0.9f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.9f,  0.9f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 1.0f

};
unsigned int triangleIndices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};


// Vertices coordinates
Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-5.0f, 0.0f,  5.0f), glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(5.0f, 5.0f, 5.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(5.0f, 5.0f, 5.0f), glm::vec2(0.0f, 5.0f)},
	Vertex{glm::vec3(5.0f, 0.0f, -5.0f), glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(5.0f, 5.0f, 5.0f), glm::vec2(5.0f, 5.0f)},
	Vertex{glm::vec3(5.0f, 0.0f,  5.0f), glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(5.0f, 5.0f, 5.0f), glm::vec2(5.0f, 0.0f)},
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

Vertex boxVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint boxIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


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

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "OpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
	
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);


	// Original code from the tutorial
	Texture textures[]
	{
		Texture("Textures/planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("Textures/planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	// Create floor mesh
	Mesh floor(verts, ind, tex);

	Shader boxShader("default.vert", "default.frag");
	std::vector <Vertex> boxVerts(boxVertices, boxVertices + sizeof(boxVertices) / sizeof(Vertex));
	std::vector <GLuint> boxInd(boxIndices, boxIndices + sizeof(boxIndices) / sizeof(GLuint));
	Mesh box(boxVerts, boxInd, tex);

	Shader boxShader2("default.vert", "default.frag");
	//std::vector <Vertex> boxVerts(boxVertices, boxVertices + sizeof(boxVertices) / sizeof(Vertex));
	//std::vector <GLuint> boxInd(boxIndices, boxIndices + sizeof(boxIndices) / sizeof(GLuint));
	Mesh box2(boxVerts, boxInd, tex);


	// Shader for light cube
	Shader lightShader("light.vert", "light.frag");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	// Create light mesh
	Mesh light(lightVerts, lightInd, tex);


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 1.0f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	glm::vec3 boxPos = glm::vec3(0.0f, 0.1f, 0.0f);
	glm::mat4 boxModel = glm::mat4(1.0f);
	boxModel = glm::translate(boxModel, boxPos);

	glm::vec3 boxPos2 = glm::vec3(0.3f, 0.1f, 0.2f);
	glm::mat4 boxModel2 = glm::mat4(1.0f);
	boxModel2 = glm::translate(boxModel2, boxPos2);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	boxShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(boxShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(boxModel));
	glUniform4f(glGetUniformLocation(boxShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(boxShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	boxShader2.Activate();
	glUniformMatrix4fv(glGetUniformLocation(boxShader2.ID, "model"), 1, GL_FALSE, glm::value_ptr(boxModel2));
	glUniform4f(glGetUniformLocation(boxShader2.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(boxShader2.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



	
	/*
	Shader triangleShaderProgram("triangle.vert", "triangle.frag");
	triangleShaderProgram.Activate();
	*/
	
	
	unsigned int triangleVertexShader = glCreateShader(GL_VERTEX_SHADER); //create a vertex shader
	glShaderSource(triangleVertexShader, 1, &triangleVertexShaderSource, NULL); //define the source code of the shader
	glCompileShader(triangleVertexShader); //compile the source code

	unsigned int triangleFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(triangleFragmentShader, 1, &triangleFragmentShaderSource, NULL);
	glCompileShader(triangleFragmentShader);

	unsigned int triangleShaderProgram = glCreateProgram(); //create a shader program
	glAttachShader(triangleShaderProgram, triangleVertexShader);
	glAttachShader(triangleShaderProgram, triangleFragmentShader); //attach both shaders to the program
	glLinkProgram(triangleShaderProgram); //link the program
	

	glDeleteShader(triangleVertexShader);
	glDeleteShader(triangleFragmentShader);
	
	
	/*
	ShaderHeader triangleShader("Shaders/triangle.vert", "Shaders/triangle.frag");
	*/
	

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); //generate one buffer
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //bind the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW); //give the buffer data

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangleIndices), triangleIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //0 is the location layout in the shader
	glEnableVertexAttribArray(0); //same here as above re: 0 value
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//tex attributes
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("Textures/container.jpg", &width, &height, &nrChannels, 0);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue)) / 2.0f + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(triangleShaderProgram, "ourColor"); //Get the location of the uniform in our shaderprogram
		//triangleShader.use();
		//triangleShader.setFloat("ourColor", 1.0f);


		//glUseProgram(triangleShaderProgram); //use the program
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f); // Pass the values we want to the location of the uniformv

		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);



		// Draws different meshes
		floor.Draw(shaderProgram, camera);

		box.Inputs(window, shaderProgram, camera, box);
		box2.Inputs(window, boxShader2, camera, box2);
		light.Inputs(window, lightShader, camera, light);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	//glDeleteProgram(triangleShaderProgram);
	shaderProgram.Delete();
	lightShader.Delete();
	boxShader.Delete();
	boxShader2.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
};

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}