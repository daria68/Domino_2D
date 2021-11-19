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
viewMatrixLocation,
projectionMatrixLocation,
codColLocation;

glm::mat4 myMatrix, resizeMatrix, matrTransl,matrTrans2,matrTrans3,matrTransl4, matrScale, matrRot, mTest, matrDeplasare, view, projection;



int width = 400, height = 300;
int codCol;
float PI = 3.141592, angle = 0;
float tx = 0; float ty = 0;
float i = 0.0, alpha = 0.0, beta = 0.0005;
GLfloat fov = 70.f, znear = 1.0f;
int k, n = 32, poz = 0, r = 1;



void miscad(void)
{
	i = i + alpha;
	if (i > 0.0 && i <= 90.0)
		alpha = -0.07;
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
	  10.0f, 60.0f, 0.0f, 1.0f,
	  60.0f, 40.0f, 0.0f, 1.0f,
	  60.0f, 140.0f, 0.0f, 1.0f,
	  10.0f, 160.0f, 0.0f, 1.0f,


	  //domino 3
	  90.0f, 50.0f, 0.0f, 1.0f,
	  40.0f, 70.0f, 0.0f, 1.0f,
	  40.0f, 170.0f, 0.0f, 1.0f,
	  90.0f, 150.0f, 0.0f, 1.0f,

	  //domino 4
	 120.0f, 60.0f, 0.0f, 1.0f,
	 70.0f, 80.0f, 0.0f, 1.0f,
	 70.0f, 180.0f, 0.0f, 1.0f,
	 120.0f, 160.0f, 0.0f, 1.0f,

	 //domino 5 
	150.0f, 70.0f, 0.0f, 1.0f,
	 100.0f, 90.0f, 0.0f, 1.0f,
	 100.0f, 190.0f, 0.0f, 1.0f,
	 150.0f, 170.0f, 0.0f, 1.0f,
	 //domino 6
	180.0f, 80.0f, 0.0f, 1.0f,
	 130.0f, 100.0f, 0.0f, 1.0f,
	 130.0f, 200.0f, 0.0f, 1.0f,
	 180.0f, 180.0f, 0.0f, 1.0f,
	//domino 7
	 210.0f, 90.0f, 0.0f, 1.0f,
	 160.0f, 110.0f, 0.0f, 1.0f,
	 160.0f, 210.0f, 0.0f, 1.0f,
	 210.0f, 190.0f, 0.0f, 1.0f,

	 //domino 8
	240.0f, 100.0f, 0.0f, 1.0f,
	 190.0f, 120.0f, 0.0f, 1.0f,
	 190.0f, 220.0f, 0.0f, 1.0f,
	 240.0f, 200.0f, 0.0f, 1.0f,

	 //domino 9
	 270.0f, 110.0f, 0.0f, 1.0f,
	 220.0f, 130.0f, 0.0f, 1.0f,
	 220.0f, 230.0f, 0.0f, 1.0f,
	 270.0f, 210.0f, 0.0f, 1.0f,

	 //domino 10
	 300.0f, 120.0f, 0.0f, 1.0f,
	 250.0f, 140.0f, 0.0f, 1.0f,
	 250.0f, 240.0f, 0.0f, 1.0f,
	 300.0f, 220.0f, 0.0f, 1.0f,

	 //domino 11
	 330.0f, 130.0f, 0.0f, 1.0f,
	 280.0f, 150.0f, 0.0f, 1.0f,
	 280.0f, 250.0f, 0.0f, 1.0f,
	 330.0f, 230.0f, 0.0f, 1.0f,

	 //domino 12
	 360.0f, 140.0f, 0.0f, 1.0f,
	 310.0f, 160.0f, 0.0f, 1.0f,
	 310.0f, 260.0f, 0.0f, 1.0f,
	 360.0f, 240.0f, 0.0f, 1.0f,

	 //domino 13
	 390.0f, 150.0f, 0.0f, 1.0f,
	 340.0f, 170.0f, 0.0f, 1.0f,
	 340.0f, 270.0f, 0.0f, 1.0f,
	 390.0f, 250.0f, 0.0f, 1.0f,

	 //domino 14
	 420.0f, 160.0f, 0.0f, 1.0f,
	 370.0f, 180.0f, 0.0f, 1.0f,
	 370.0f, 280.0f, 0.0f, 1.0f,
	 420.0f, 260.0f, 0.0f, 1.0f,

	 //Elemente decorative
	 //masa
	 718.0f, 204.0f, 0.0f, 1.0f,
	-57.0f, -28.0f, 0.0f, 1.0f,
	 -160.0f, 370.0f, 0.0f, 1.0f,
	 84.0f, 424.0f, 0.0f, 1.0f,
	 
	 //piciorul1 
	 64.0f, 100.0f, 0.0f, 1.0f,
	 104.0f, 100.0f, 0.0f, 1.0f,
	 104.0f, -70.0f, 0.0f, 1.0f,
	 64.0f, -70.0f, 0.0f, 1.0f, 

	 //piciorul2
	 668.0f, 200.0f, 0.0f, 1.0f,
	 708.0f, 204.0f, 0.0f, 1.0f, 
	 708.0f, -70.0f, 0.0f, 1.0f,
	 668.0f, -70.0f, 0.0f, 1.0f,

	 //trigger-ul
	 -370.0f, 102.0f, 0.0f, 1.0f, 
	 -450.0f, 142.0f, 0.0f, 1.0f,
	 -450.0f, 162.0f, 0.0f, 1.0f,
	 -370.0f, 122.0f, 0.0f, 1.0f,

	 //pahar cu apa
	 74.0f, 300.0f, 0.0f, 1.0f,
     94.0f, 300.0f, 0.0f, 1.0f,
	 104.0f, 360.0f, 0.0f, 1.0f,
     64.0f, 360.0f, 0.0f, 1.0f,

	 //geam
	 550.0f,424.0f,0.0f, 1.0f,
	 800.0f,424.0f,0.0f, 1.0f,
     800.0f,584.0f,0.0f, 1.0f,
	 550.0f,584.0f,0.0f, 1.0f,
		// rama jos
	550.0f, 424.0f, 0.0f, 1.0f,
	550.0f, 432.0f, 0.0f, 1.0f,
	800.0f, 432.0f, 0.0f, 1.0f,
	800.0f, 424.0f, 0.0f, 1.0f,
		//rama stanga
	550.0f, 424.0f, 0.0f, 1.0f,
	550.0f, 584.0f, 0.0f, 1.0f,
	558.0f, 584.0f, 0.0f, 1.0f,
	558.0f, 424.0f, 0.0f, 1.0f,
		 //rama dreapa
	750.0f, 424.0f, 0.0f, 1.0f,
	750.0f, 584.0f, 0.0f, 1.0f,
	758.0f, 584.0f, 0.0f, 1.0f,
	758.0f, 424.0f, 0.0f, 1.0f,

		 // fata de masa
	648.0f, 204.0f, 0.0f, 1.0f,
	-107.0f, -28.0f, 0.0f, 1.0f,
	-200.0f, 340.0f, 0.0f, 1.0f,
	74.0f, 404.0f, 0.0f, 1.0f,
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

	glClearColor(1.0f, 1.0f, 0.9f, 0.0f); // culoarea de fond a ecranului
	
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	projection = glm::infinitePerspective(fov, (GLfloat)w / (GLfloat)h, znear);

}
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5.0);
	glLineWidth(2.0f);
	CreateVBO();

	resizeMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.f / width, 1.f / height, 1.0));
	matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(-400.f, -300.f, 0.0));

	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	//fata de masa
	codCol = 7;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 92, 4);
	codCol = 7;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	//masa
	glDrawArrays(GL_POLYGON, 56, 4);
	//picior 1
	glDrawArrays(GL_POLYGON, 60, 4);
	//picior 2
	glDrawArrays(GL_POLYGON, 64, 4);
	codCol = 9;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	//geam
	glDrawArrays(GL_POLYGON, 76, 4);
	//Rame geam
	codCol = 5;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 80, 4);
	glDrawArrays(GL_POLYGON, 84, 4);
	glDrawArrays(GL_POLYGON, 88, 4);
	//fata de masa
	codCol =10;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 92, 4);
	codCol = 9;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	//pahar
	glDrawArrays(GL_POLYGON, 72, 4);
	matrTrans2 = glm::translate(glm::mat4(1.0f), glm::vec3(-395.f, -170.f, 0.0));
	matrTrans3 = glm::translate(glm::mat4(1.0f), glm::vec3(395.f, 170.f, 0.0));
	matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(-2.93, 1.17, 0.0));

	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.6f),
		glm::vec3(0.05f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
 

	myMatrix =  view * resizeMatrix * matrTransl * matrTrans3 * matrRot * matrTrans2;
	CreateShaders();
	

	/*
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	codCol = 4;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	
	glDrawArrays(GL_POLYGON, 52, 4);

	*/

	matrTrans2 = glm::translate(glm::mat4(1.0f), glm::vec3(-365.f, -160.f, 0.0));
	matrTrans3 = glm::translate(glm::mat4(1.0f), glm::vec3(365.f, 160.f, 0.0));
	matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(-2.93, 1.17, 0.0));
	myMatrix = view * resizeMatrix * matrTransl * matrTrans3 * matrRot * matrTrans2;

	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	codCol = 1;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);

	glDrawArrays(GL_POLYGON, 48, 4);

	matrTrans2 = glm::translate(glm::mat4(1.0f), glm::vec3(-335.f, -150.f, 0.0));
	matrTrans3 = glm::translate(glm::mat4(1.0f), glm::vec3(335.f, 150.f, 0.0));
	myMatrix = view * resizeMatrix * matrTransl * matrTrans3 * matrRot * matrTrans2;

	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	codCol = 2;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 44, 4);

	matrTrans2 = glm::translate(glm::mat4(1.0f), glm::vec3(-305.f, -140.f, 0.0));
	matrTrans3 = glm::translate(glm::mat4(1.0f), glm::vec3(305.f, 140.f, 0.0));
	myMatrix = view * resizeMatrix * matrTransl * matrTrans3 * matrRot * matrTrans2;

	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	codCol = 3;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 40, 4);

	matrTrans2 = glm::translate(glm::mat4(1.0f), glm::vec3(-275.f, -130.f, 0.0));
	matrTrans3 = glm::translate(glm::mat4(1.0f), glm::vec3(275.f, 130.f, 0.0));
	myMatrix = view * resizeMatrix * matrTransl * matrTrans3 * matrRot * matrTrans2;

	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	codCol = 4;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 36, 4);

	matrTrans2 = glm::translate(glm::mat4(1.0f), glm::vec3(-245.f, -120.f, 0.0));
	matrTrans3 = glm::translate(glm::mat4(1.0f), glm::vec3(245.f, 123.f, 0.0));
	myMatrix = view * resizeMatrix * matrTransl * matrTrans3 * matrRot * matrTrans2;

	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	codCol = 5;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 32, 4);

	matrTrans2 = glm::translate(glm::mat4(1.0f), glm::vec3(-215.f, -110.f, 0.0));
	matrTrans3 = glm::translate(glm::mat4(1.0f), glm::vec3(215.f, 110.f, 0.0));
	myMatrix = view * resizeMatrix * matrTransl * matrTrans3 * matrRot * matrTrans2;

	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	codCol = 6;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 28, 4);

	matrTrans2 = glm::translate(glm::mat4(1.0f), glm::vec3(-185.f, -100.f, 0.0));
	matrTrans3 = glm::translate(glm::mat4(1.0f), glm::vec3(185.f, 100.f, 0.0));
	myMatrix = view * resizeMatrix * matrTransl * matrTrans3 * matrRot * matrTrans2;

	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	codCol = 5;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 24, 4);

	matrTrans2 = glm::translate(glm::mat4(1.0f), glm::vec3(-155.f, -90.f, 0.0));
	matrTrans3 = glm::translate(glm::mat4(1.0f), glm::vec3(155.f, 90.f, 0.0));
	myMatrix = view * resizeMatrix * matrTransl * matrTrans3 * matrRot * matrTrans2;

	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	codCol = 4;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 20, 4);

	matrTrans2 = glm::translate(glm::mat4(1.0f), glm::vec3(-125.f, -80.f, 0.0));
	matrTrans3 = glm::translate(glm::mat4(1.0f), glm::vec3(125.f, 80.f, 0.0));
	myMatrix = view * resizeMatrix * matrTransl * matrTrans3 * matrRot * matrTrans2;

	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	codCol = 3;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 16, 4);

	matrTrans2 = glm::translate(glm::mat4(1.0f), glm::vec3(-95.f, -70.f, 0.0));
	matrTrans3 = glm::translate(glm::mat4(1.0f), glm::vec3(95.f, 70.f, 0.0));
	myMatrix = view * resizeMatrix * matrTransl * matrTrans3 * matrRot * matrTrans2;

	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	codCol = 2;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 12, 4);

	matrTrans2 = glm::translate(glm::mat4(1.0f), glm::vec3(-65.f, -60.f, 0.0));
	matrTrans3 = glm::translate(glm::mat4(1.0f), glm::vec3(65.f, 60.f, 0.0));
	myMatrix = view * resizeMatrix * matrTransl * matrTrans3 * matrRot * matrTrans2;

	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	codCol = 1;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 8, 4);

	/*
	matrTrans2 = glm::translate(glm::mat4(1.0f), glm::vec3(-35.f, -50.f, 0.0));
	matrTrans3 = glm::translate(glm::mat4(1.0f), glm::vec3(35.f, 50.f, 0.0));
	myMatrix = view * resizeMatrix * matrTransl * matrTrans3 * matrRot * matrTrans2;

	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	codCol = 2;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 4, 4);
	*/
	matrTransl4 = glm::translate(glm::mat4(1.0f), glm::vec3(7*i, -320, 0.0));
	myMatrix = view * resizeMatrix * matrTransl4 ;
	
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	codCol = 8;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	//triger
	glDrawArrays(GL_POLYGON, 68, 4);
	
	/*
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	
	codCol = 1;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 0, 4);
	*/
	myMatrix = resizeMatrix * matrTransl;
	
	DestroyShaders();
	DestroyVBO();

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
	glutCreateWindow("DOMINO 2D");
	glewInit();
	Initialize();
	glutDisplayFunc(RenderFunction);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutCloseFunc(Cleanup);
	glutMainLoop();


}

