/* TRANSFORMARI.
   - utilizarea bibliotecii glm: https://glm.g-truc.net/0.9.9/index.html
   - transformari variate asupra primitivelor, transmise catre shader
   - colorarea primitivelor folosind variabile uniforme si shader-ul de fragment
*/
#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h

#include "loadShaders.h"

#include "glm/glm/glm.hpp"  
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtx/transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

using namespace std;

//////////////////////////////////////

GLuint
VaoId,
VboId,
ColorBufferId,
ProgramId,
myMatrixLocation,
matrScaleLocation,
matrTranslLocation,
matrRotlLocation,
codColLocation;

glm::mat4 myMatrix, resizeMatrix, matrTransl, matrScale, matrRot, mTest, matrDeplasare;



int width = 400, height = 300;
int codCol;
float PI = 3.141592, angle = 0;
float tx = 0; float ty = 0;
float i = 0.0, alpha = 0.0, beta = 0.2;


void miscad(void)
{
	i = i + alpha;
	if (i > 0.0 && i <= 90.0)
		alpha = -10.0;
	else if (i <= 0.0)
		return;

	angle = angle - beta;

	glutPostRedisplay();
}



void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			alpha = 10.0; glutIdleFunc(miscad);
		break;
	default:
		break;
	}
}


void CreateVBO(void)
{
	// varfurile 
	GLfloat Vertices[] = {

		
	  //domino 1
	  -20.0f, 50.0f, 0.0f, 1.0f,
	  30.0f, 30.0f, 0.0f, 1.0f,
	  30.0f, 130.0f, 0.0f, 1.0f,
	  -20.0f, 150.0f, 0.0f, 1.0f,

	  //domino 2

	  60.0f, 40.0f, 0.0f, 1.0f,
	  10.0f, 60.0f, 0.0f, 1.0f,
	  10.0f, 160.0f, 0.0f, 1.0f,
	  60.0f, 140.0f, 0.0f, 1.0f,
	};

	GLfloat Colors[] = {
	  0.0f, 0.0f, 0.0f, 0.0f,
	  0.0f, 0.0f, 0.0f, 0.0f,
	  0.0f, 0.0f, 0.0f, 0.0f,
	  0.0f, 0.0f, 0.0f, 0.0f,

	};


	// se creeaza un buffer nou
	glGenBuffers(1, &VboId);
	// este setat ca buffer curent
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	// punctele sunt "copiate" in bufferul curent
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	// se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	// se activeaza lucrul cu atribute; atributul 0 = pozitie
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// un nou buffer, pentru culoare
	glGenBuffers(1, &ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	// atributul 1 =  culoare
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);


}
void DestroyVBO(void)
{


	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);


}

void CreateShaders(void)
{
	ProgramId = LoadShaders("Proiect1_Domino2D_Shader.vert", "Proiect1_Domino2D_Shader.frag");
	glUseProgram(ProgramId);
}


void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

void Initialize(void)
{

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului
	
}
void RenderFunction(void)
{
	resizeMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.f / width, 1.f / height, 1.0));
	matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(-400.f, -300.f, 0.0));
	matrDeplasare = glm::translate(glm::mat4(1.0f), glm::vec3(i, i, 0.0)); // controleaza translatia de-a lungul lui Ox
	matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));

	CreateVBO();

	glClear(GL_COLOR_BUFFER_BIT);
	myMatrix = resizeMatrix * matrTransl * matrRot;
	CreateShaders();

	glPointSize(5.0);
	glLineWidth(2.0f);

	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	

	codCol = 2;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 4, 4);

	codCol = 1;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 0, 4);

	



	glutPostRedisplay();
	glFlush();
}
void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}

int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Utilizarea glm pentru transformari");
	glewInit();
	Initialize();
	glutDisplayFunc(RenderFunction);
	glutCloseFunc(Cleanup);
	glutMainLoop();


}

