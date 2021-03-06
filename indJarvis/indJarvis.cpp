// indJarvis.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
//расширения
GLuint screenWidth = 800, screenHeight = 600;
//проттотипы функции
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();
//глобальные переменные
bool keys[1024];
GLfloat lastX = screenWidth / 2, lastY = screenHeight / 2;
bool firstMouse = true;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
//камера
Camera camera(glm::vec3(0.0f, 0.0f, 30.0f));
// Light attributes
glm::vec3 lightPos(0.0f, 15.0f, 15.0f);

int main()
{
	// Инициализация GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	float verticesOfCube[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		system("pause");
		return -1;
	}
	glViewport(0, 0, screenWidth, screenHeight);
	glEnable(GL_DEPTH_TEST);
	Shader Scene("Shaders/scene.vert", "Shaders/scene.frag");
	Shader lampShader("Shaders/lamp.vert", "Shaders/lamp.frag");
	Shader Line("Shaders/line.vert", "Shaders/line.frag");
	
	//генерация вершин
	vector<vector2> source(15);
	vector<vector2> result;
	ranGen(-10, 10, source);
	jarvis(source, result);
	result.push_back(result[0]);
	//заполнение буферов
	GLuint VBO_CUBE, VAO_CUBE, VBO_LINE,  VAO_LINE, VAO_LIGHT;
	glGenBuffers(1, &VBO_CUBE);
	glGenBuffers(1, &VBO_LINE);
	glGenVertexArrays(1, &VAO_CUBE);
	glGenVertexArrays(1, &VAO_LINE);
	glGenVertexArrays(1, &VAO_LIGHT);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_CUBE);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesOfCube), verticesOfCube, GL_STATIC_DRAW);
	//кубики
	glBindVertexArray(VAO_CUBE);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(sizeof(3 * sizeof(GLfloat))));
		glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	//свет
	glBindVertexArray(VAO_LIGHT);
		// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
		glBindBuffer(GL_ARRAY_BUFFER, VBO_CUBE);
		// Set the vertex attributes (only position data for the lamp))
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	//линия
	glBindBuffer(GL_ARRAY_BUFFER, VBO_LINE);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vector2)*result.size(), result.data(), GL_STATIC_DRAW);

	glBindVertexArray(VAO_LINE);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vector2), (void*)0);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window))
	{
		//Вычисляем время между кадрами
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		Do_Movement();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Scene.Use();
		GLint objectColorLoc = glGetUniformLocation(Scene.Program, "objectColor");
		GLint lightColorLoc = glGetUniformLocation(Scene.Program, "lightColor");
		GLint lightPosLoc = glGetUniformLocation(Scene.Program, "lightPos");
		glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
		glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
		// Трансформации камеры
		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection;
		projection = glm::perspective(camera.Zoom, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		// Gполучаем локации глобальных переменных в шейдерах
		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(Scene.Program, "model");
		GLint viewLoc = glGetUniformLocation(Scene.Program, "view");
		GLint projLoc = glGetUniformLocation(Scene.Program, "projection");
		GLint viewPosLoc = glGetUniformLocation(Scene.Program, "viewPos");
		// Передаем матрицы в шейдера
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
		glBindVertexArray(VAO_CUBE);
			for (int i = 0; i < source.size(); i++)
			{
				glm::mat4 model;
				model = glm::translate(model, glm::vec3(source[i].x, source[i].y, 0.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}			
		glBindVertexArray(0);

		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");
		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glm::mat4 model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(VAO_LIGHT);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		Line.Use();
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4();
		//model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(10.0f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_LINE);
			glDrawArrays(GL_LINE_STRIP, 0, result.size());
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO_CUBE);
	glDeleteVertexArrays(1, &VAO_LINE);
	glDeleteVertexArrays(1, &VAO_LIGHT);
	glDeleteBuffers(1, &VBO_CUBE);
	glDeleteBuffers(1, &VBO_LINE);
	
	glfwTerminate();
	return 0;
}
void Do_Movement()
{
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}
//Функция вызывается всякий раз, когда клавиша нажимается/отпускается
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Действие обратное, поскольку y-координаты идут снизу влево

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

