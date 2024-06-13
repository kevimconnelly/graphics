#include"Mesh.h"

const unsigned int width = 800;
const unsigned int height = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char *triangleVertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char *triangleFragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);\n"
	"}\0";

float triangleVertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
};

// Vertices coordinates
Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-5.0f, 0.0f,  5.0f), glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(5.0f, 5.0f, 5.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(5.0f, 5.0f, 5.0f), glm::vec2(0.0f, 5.0f)},
	Vertex{glm::vec3(5.0f, 0.0f, -5.0f), glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(5.0f, 5.0f, 5.0f), glm::vec2(5.0f, 5.0f)},
	Vertex{glm::vec3(5.0f, 0.0f,  5.0f), glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(5.0f, 5.0f, 5.0f), glm::vec2(5.0f, 0.0f)}
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




	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), triangleVertices, GL_STATIC_DRAW);

	
	unsigned int triangleVertexShader;
	triangleVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(triangleVertexShader, 1, &triangleVertexShaderSource, NULL);
	glCompileShader(triangleVertexShader);

	unsigned int triangleFragmentShader;
	triangleFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(triangleFragmentShader, 1, &triangleVertexShaderSource, NULL);
	glCompileShader(triangleFragmentShader);


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