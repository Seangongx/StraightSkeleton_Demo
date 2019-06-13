#include "include/glad/glad.h"
#include "include/shader.h"
#include "include/StraightSkeleton.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
//#include <GL/gl.h>

using namespace std;
using namespace glm;

//const GLuint SCR_WIDTH = 1920;
//const GLuint SCR_HEIGHT = 1080;
const GLuint SCR_WIDTH = 800;
const GLuint SCR_HEIGHT = 800;
bool hullDrawn = false;
bool skeletonDrawn = false;
bool mouseClick = false;

vector<vec3> Points;
vector<vec3> Intersections;
vector<vec3> linePoints;
vector<Point<double>> chPoints;
bool inputFlag = false;
bool clearFlag = false;

void adjustOrigin(double *x, double *y) {
	*y = (double)SCR_HEIGHT - *y;
}

void normalize(double *x, double *y) {
	*y = (*y * 2) / ((double)SCR_HEIGHT);
	*y -= 1;
	*x = (*x * 2) / ((double)SCR_WIDTH);
	*x -= 1;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void processKeyboardInput(GLFWwindow *window) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		if (!hullDrawn) {
			for (int i = 0; i < Points.size() - 1; i++) {
				linePoints.push_back(Points[i]);
				linePoints.push_back(Points[i + 1]);
			}
			linePoints.push_back(Points[Points.size() - 1]);
			linePoints.push_back(Points[0]);
			hullDrawn = true;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		if (!skeletonDrawn) {
			vector< Point<double> > SPoints;
			for (int i = 0; i < Points.size(); i++) {
				Point<double> newp(Points[i].x, Points[i].y);
				SPoints.push_back(newp);
			}
			StraightSkeleton SS(SPoints);
			for (int i = 0; i < SS.Arc.size(); i++) {
				linePoints.push_back(vec3(SS.Arc[i].first.x, SS.Arc[i].first.y, 0));
				linePoints.push_back(vec3(SS.Arc[i].second.x, SS.Arc[i].second.y, 0));
			}
			for (int i = 0; i < SS.I_T.size(); i++) {
				Intersections.push_back(vec3(SS.I_T[i].Pos.x, SS.I_T[i].Pos.y, 0));
			}
			skeletonDrawn = true;
		}
	}
	if(glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS) {
		if (!clearFlag)
			clearFlag = true;
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		mouseClick = true;
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		adjustOrigin(&xpos, &ypos);
		Point<double> chp(xpos, ypos);
		chPoints.push_back(chp);
		normalize(&xpos, &ypos);
		Points.push_back(vec3(xpos, ypos, 0));
	}
}

template <typename T>
void newObject(GLuint &_vao, GLuint &_vbo, T &_data) {
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _data.size() * sizeof(vec3), &_data[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), NULL);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


int main() {
	//initialise glfw and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfwCreateWindow: GLFWwindow* glfwCreateWindow(int width,int height, const char * title,GLFWmonitor * monitor,GLFWwindow * share )
	//GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Convex Hull", glfwGetPrimaryMonitor(), NULL);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Convex Hull", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//mouse button callback
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//Use Shader class to read shader files and create shaders
	Shader sh("shaders/vertexShader.vs", "shaders/fragmentShader.fs");

	//define vertex array objects and vertex buffer objects
	//VAO:subsequent vertex attribute calls from that point on will be stored inside the VAO. All the bindings of buffers are stored in the vertex array object.
	//VBO:store a large number of vertices in the GPU's memory. The advantage of using those buffer objects is that we can send large batches of data all at once to the graphics card without having to send data a vertex a time.

	//VAO and VBO for Points
	GLuint VAOP, VBOP;
	//VAO and VBO for lines
	GLuint VAOL, VBOL;
	//VAO and VBO for Intersection
	GLuint VAOI, VBOI;


	//////data1
	//Points.push_back(vec3(-0.8, 0.0, 0.0));
	//Points.push_back(vec3(-0.75, -0.4, 0.0));
	//Points.push_back(vec3(-0.6, -0.7, 0.0));
	//Points.push_back(vec3(-0.3, -0.9, 0.0));
	//Points.push_back(vec3(0.0, -1.0, 0.0));
	//Points.push_back(vec3(0.3, -0.9, 0.0));
	//Points.push_back(vec3(0.6, -0.7, 0.0));
	//Points.push_back(vec3(0.75, -0.4, 0.0));
	//Points.push_back(vec3(0.8, 0.0, 0.0));

	while (!glfwWindowShouldClose(window)) {

		sh.use();
		glPointSize(5);
		glLineWidth(2);

		processKeyboardInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		if (mouseClick) {
			newObject(VAOP, VBOP, Points);

			glBindVertexArray(VAOP);
			sh.setVec3("color", vec3(1.0, 0.0, 0.5));
			glDrawArrays(GL_POINTS, 0, Points.size());
			glBindVertexArray(0);

		}

		if (hullDrawn) {
			//draw Points as and when clicked;
			sh.use();
			glPointSize(5);
			glLineWidth(2);

			newObject(VAOP, VBOP, Points);
			newObject(VAOL, VBOL, linePoints);

			glBindVertexArray(VAOL);
			sh.setVec3("color", vec3(0.0, 1.0, 0.0));
			glDrawArrays(GL_LINES, 0, linePoints.size());
			glBindVertexArray(0);

			glBindVertexArray(VAOP);
			sh.setVec3("color", vec3(1.0, 0.0, 0.5));
			glDrawArrays(GL_POINTS, 0, Points.size());
			glBindVertexArray(0);

		}
		else {


		}


		if (skeletonDrawn) {
			//draw Points as and when clicked;
			sh.use();
			glPointSize(5);
			glLineWidth(2);
			
			newObject(VAOP, VBOP, Points);
			newObject(VAOL, VBOL, linePoints);
			newObject(VAOI, VBOI, Intersections);

			glBindVertexArray(VAOL);
			sh.setVec3("color", vec3(0.0, 1.0, 0.0));
			glDrawArrays(GL_LINES, 0, linePoints.size());
			glBindVertexArray(0);

			glBindVertexArray(VAOP);
			sh.setVec3("color", vec3(1.0, 0.0, 0.5));
			glDrawArrays(GL_POINTS, 0, Points.size());
			glBindVertexArray(0);

			glBindVertexArray(VAOI);
			sh.setVec3("color", vec3(0.0, 5.0, 0.8));
			glDrawArrays(GL_POINTS, 0, Intersections.size());
			glBindVertexArray(0);
		}

		if (clearFlag) {
			Points.empty();
			Intersections.empty();
			linePoints.empty();
			chPoints.empty();

			glDeleteVertexArrays(1, &VAOP);
			glDeleteBuffers(1, &VBOP);
			glDeleteVertexArrays(1, &VAOL);
			glDeleteBuffers(1, &VBOL);
			glDeleteVertexArrays(1, &VAOI);
			glDeleteBuffers(1, &VBOI);

			clearFlag = false;
			skeletonDrawn = false;
			hullDrawn = false;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glDeleteVertexArrays(1, &VAOP);
	glDeleteBuffers(1, &VBOP);
	glDeleteVertexArrays(1, &VAOL);
	glDeleteBuffers(1, &VBOL);
	glDeleteVertexArrays(1, &VAOI);
	glDeleteBuffers(1, &VBOI);


	//clear all perviously allocate GLFW resources.
	glfwTerminate();
	return 0;
}




//for (int i = 0; i < chPoints.size(); i++)
//{
//	cout << "(" << chPoints[i].x << "," << chPoints[i].y << ")" << endl;
//}
//
//for (int i = 0; i < Points.size(); i++)
//{
//	cout << "(" << Points[i].x << "," << Points[i].y << ")" << endl;
//}

////data1
//Points.push_back(vec3(0.0, 0.6, 0.0));
//Points.push_back(vec3(-0.1, 0.3, 0.0));
//Points.push_back(vec3(0.0, 0.0, 0.0));
//Points.push_back(vec3(0 .3, 0.0, 0.0));
//Points.push_back(vec3(0.4, 0.3, 0.0));
//Points.push_back(vec3(0.3, 0.6, 0.0));	

//for (int i = 0; i < Points.size() - 1; i++) {
//	linePoints.push_back(Points[i]);
//	linePoints.push_back(Points[i + 1]);
//}
//linePoints.push_back(Points[Points.size() - 1]);
//linePoints.push_back(Points[0]);

//vector< Point<double> > SPoints;
//for (int i = 0; i < Points.size(); i++) {
//	Point<double> newp(Points[i].x, Points[i].y);
//	SPoints.push_back(newp);
//}

//StraightSkeleton SS(SPoints);
//for (int i = 0; i < SS.Arc.size(); i++) {
//	linePoints.push_back(vec3(SS.Arc[i].first.x, SS.Arc[i].first.y, 0));
//	linePoints.push_back(vec3(SS.Arc[i].second.x, SS.Arc[i].second.y, 0));
//}
//for (int i = 0; i < SS.I_T.size(); i++) {
//	Intersections.push_back(vec3(SS.I_T[i].Pos.x, SS.I_T[i].Pos.y, 0));
//}

//glGenVertexArrays(1, &VAOP);
//glGenBuffers(1, &VBOP);
//glBindVertexArray(VAOP);
//glBindBuffer(GL_ARRAY_BUFFER, VBOP);
//glBufferData(GL_ARRAY_BUFFER, Points.size() * sizeof(vec3), &Points[0], GL_DYNAMIC_DRAW);
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), NULL);
//glEnableVertexAttribArray(0);
//glBindBuffer(GL_ARRAY_BUFFER, 0);
//glBindVertexArray(0);

//glGenVertexArrays(1, &VAOI);
//glGenBuffers(1, &VBOI);
//glBindVertexArray(VAOI);
//glBindBuffer(GL_ARRAY_BUFFER, VBOI);
//glBufferData(GL_ARRAY_BUFFER, Intersections.size() * sizeof(vec3), &Intersections[0], GL_DYNAMIC_DRAW);
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), NULL);
//glEnableVertexAttribArray(0);
//glBindBuffer(GL_ARRAY_BUFFER, 0);
//glBindVertexArray(0);

//glGenVertexArrays(1, &VAOL);
//glGenBuffers(1, &VBOL);
//glBindVertexArray(VAOL);
//glBindBuffer(GL_ARRAY_BUFFER, VBOL);
//glBufferData(GL_ARRAY_BUFFER, linePoints.size() * sizeof(vec3), &linePoints[0], GL_DYNAMIC_DRAW);
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), NULL);
//glEnableVertexAttribArray(0);
//glBindBuffer(GL_ARRAY_BUFFER, 0);
//glBindVertexArray(0);

