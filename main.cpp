#include <GL/glut.h>

#include "Object.h"
#include "Scenario.h"
#include <thread>

void Inicializa();
void Desenha();
void Teclado(unsigned char, int, int);
void Mouse(int, int, int, int);
void mainLoop( int dt );
void tecladoRelease(unsigned char key, int x, int y);

int oldTimeSinceStart = 0;
float _deltaTime;

void mainLoop( int dt )
{
	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	_deltaTime = float(timeSinceStart - oldTimeSinceStart);
	_deltaTime /= 1000.f;
	oldTimeSinceStart = timeSinceStart;
	Scenario* instance = Scenario::GetInstance();
	instance->update(_deltaTime);
	
	glutPostRedisplay();
	//Desenha();

	glutTimerFunc(16, mainLoop, 0);

	
	
}

int main(int argc, char** argv)
{
	Scenario* mainScenario = Scenario::GetInstance();

	//std::thread mainLoopGame(mainLoopThread);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Game flow - OpenGL");
	glutDisplayFunc(Desenha);
	glutKeyboardFunc(Teclado);
	glutTimerFunc(16, mainLoop, 0);
	glutKeyboardUpFunc(tecladoRelease);
	glutMouseFunc(Mouse);
	Inicializa();
	glutMainLoop();

	/*appRunning = false;
	mainLoopGame.join();*/

	return 0;
}
void Inicializa() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(0, 1280, 0, 720);
}
void Desenha() {

	glClear(GL_COLOR_BUFFER_BIT);

	Scenario::GetInstance()->drawWorld();
	
	glFlush();

}

void tecladoRelease(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
	case 'Q':
		if (Scenario::GetInstance()->getPlayerMovement("player_1") == PlayerObject::MOVE::UP)
			Scenario::GetInstance()->setPlayerMovement("player_1", PlayerObject::MOVE::NONE);
		break;
	case 'a':
	case 'A':
		if (Scenario::GetInstance()->getPlayerMovement("player_1") == PlayerObject::MOVE::DOWN)
			Scenario::GetInstance()->setPlayerMovement("player_1", PlayerObject::MOVE::NONE);
		break;
	case 'i':
	case 'I':
		if( Scenario::GetInstance()->getPlayerMovement( "player_2") == PlayerObject::MOVE::UP )
			Scenario::GetInstance()->setPlayerMovement("player_2", PlayerObject::MOVE::NONE);
		break;
	case 'k':
	case 'K':
		if (Scenario::GetInstance()->getPlayerMovement("player_2") == PlayerObject::MOVE::DOWN)
			Scenario::GetInstance()->setPlayerMovement("player_2", PlayerObject::MOVE::NONE);
		break;
	}

}

void Teclado(unsigned char tc, int x, int y) {
	auto* instance = Scenario::GetInstance();
	switch (tc) {
	case 27:
		exit(0);
		break;
	case 'q':
	case 'Q':
		Scenario::GetInstance()->setPlayerMovement("player_1", PlayerObject::MOVE::UP);
		break;
	case 'a':
	case 'A':
		Scenario::GetInstance()->setPlayerMovement("player_1", PlayerObject::MOVE::DOWN);
		break;
	case 'i':
	case 'I':
		Scenario::GetInstance()->setPlayerMovement("player_2", PlayerObject::MOVE::UP);
		break;
	case 'k':
	case 'K':
		Scenario::GetInstance()->setPlayerMovement("player_2", PlayerObject::MOVE::DOWN);
		break;
	/*case 'm':
	case 'M':
		{
			float ballAngle_ = instance->getBallAngle();
			ballAngle_ -= 1;
			instance->setBallAngle(ballAngle_);
			std::cout << "ballAngle " << ballAngle_ << std::endl;
		}
		break;
	case 'n':
	case 'N':
		{
			float ballAngle2 = instance->getBallAngle();
			ballAngle2 += 1;
			instance->setBallAngle(ballAngle2);
			std::cout << "ballAngle " << ballAngle2 << std::endl;
		}
		break;*/
	case 'r':
	case 'R':
		Scenario::GetInstance()->resetPlayerScore();
		Scenario::GetInstance()->reset();
		//TODO: reset
		break;

	}

	
}
void Mouse(int botao, int estado, int x, int y) {
	/*switch (botao) {
	case GLUT_LEFT_BUTTON:
		glScalef(1.10f, 1.10f, 0.0f);
		Desenha();
		break;
	case GLUT_RIGHT_BUTTON:
		glScalef(0.90f, 0.90f, 0.0f);
		Desenha();
		break;
	}*/
}

//
//#include <stdlib.h>
//#include <GL/glew.h>
//#ifdef __APPLE__
//#  include <GLUT/glut.h>
//#else
//#  include <GL/glut.h>
//#endif
//#include <math.h>
//#include <stdio.h>
//
//#define NO_COLLISION_DETECTED 0
//#define BOTTOM_PADDLE_COLLISION 1
//#define TOP_PADDLE_COLLISION 2
//
//#define NOT_OUT_OF_BOUNDS 0
//#define OUT_OF_BOUNDS_TOP 1
//#define OUT_OF_BOUNDS_BOTTOM 2
//#define OUT_OF_BOUNDS_LEFT 3
//#define OUT_OF_BOUNDS_RIGHT 4
//
//struct {
//	struct {
//		GLfloat x;
//		GLint score;
//		char* score_buf;
//	} bottom_paddle;
//
//	struct {
//		GLfloat x;
//		GLint score;
//		char* score_buf;
//	} top_paddle;
//
//	struct {
//		GLfloat x;
//		GLfloat y;
//		GLfloat dx;
//		GLfloat dy;
//	} ball;
//} resources;
//
//void setup(void) {
//	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
//
//	resources.bottom_paddle.x = 0.0f;
//	resources.bottom_paddle.score = 0;
//	resources.bottom_paddle.score_buf = (char*)malloc(sizeof(char) * 5);
//
//	resources.top_paddle.x = 0.0f;
//	resources.top_paddle.score = 0;
//	resources.top_paddle.score_buf = (char*)malloc(sizeof(char) * 5);
//
//	resources.ball.x = 0.0f;
//	resources.ball.y = 0.0f;
//	resources.ball.dx = 0.0f;
//	resources.ball.dy = -0.05f;
//}
//
//void bitmapString(void* font, char* s, GLfloat x, GLfloat y) {
//	glRasterPos2f(x, y);
//	while (*s) glutBitmapCharacter(font, *s++);
//}
//
//void render(void) {
//	glClear(GL_COLOR_BUFFER_BIT);
//	glColor3f(0.0f, 0.0f, 1.0f);
//	glRectf(resources.bottom_paddle.x - 0.2f, -0.8f, resources.bottom_paddle.x + 0.2f, -0.7f);
//
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glRectf(resources.top_paddle.x - 0.2f, 0.7f, resources.top_paddle.x + 0.2f, 0.8f);
//
//	// Draw the ball
//	glColor3f(0.0f, 0.0f, 0.0f);
//	glRectf(resources.ball.x - 0.05f, resources.ball.y, resources.ball.x + 0.05f, resources.ball.y + 0.1f);
//
//	sprintf(resources.top_paddle.score_buf, "%d", resources.top_paddle.score);
//	sprintf(resources.bottom_paddle.score_buf, "%d", resources.bottom_paddle.score);
//
//	// Print scores
//	bitmapString(GLUT_BITMAP_HELVETICA_18, resources.top_paddle.score_buf, -0.8f, 0.8f);
//	bitmapString(GLUT_BITMAP_HELVETICA_18, resources.bottom_paddle.score_buf, -0.8f, -0.8f);
//
//	glutSwapBuffers();
//}
//
//int detect_out_of_bounds() {
//	if (resources.ball.y >= 1.0f) {
//		// Bottom player gets a point
//		resources.bottom_paddle.score++;
//		return OUT_OF_BOUNDS_TOP;
//	}
//	else if (resources.ball.y <= -1.0f) {
//		// Top player gets a point
//		resources.top_paddle.score++;
//		return OUT_OF_BOUNDS_BOTTOM;
//	}
//	else if (resources.ball.x < -1.0f) {
//		return OUT_OF_BOUNDS_LEFT;
//	}
//	else if (resources.ball.x + 0.1f > 1.0f) {
//		return OUT_OF_BOUNDS_RIGHT;
//	}
//	return NOT_OUT_OF_BOUNDS;
//}
//
//int detect_collision() {
//	if (resources.ball.y <= -0.7f && resources.ball.x - 0.05f <= resources.bottom_paddle.x + 0.2f && resources.ball.x + 0.0f >= resources.bottom_paddle.x - 0.2f)
//		return BOTTOM_PADDLE_COLLISION;
//	if (resources.ball.y >= 0.57f && resources.ball.x - 0.05f <= resources.top_paddle.x + 0.2f && resources.ball.x + 0.05f >= resources.top_paddle.x - 0.2f)
//		return TOP_PADDLE_COLLISION;
//	return NO_COLLISION_DETECTED;
//}
//
//void keypress(unsigned char key, int x, int y) {
//	switch (key) {
//	case 97:
//		resources.top_paddle.x -= 0.05f;
//		glutPostRedisplay();
//		break;
//	case 100:
//		resources.top_paddle.x += 0.05f;
//		glutPostRedisplay();
//		break;
//	default:
//		break;
//	}
//}
//
//void special_keypress(int key, int x, int y) {
//	switch (key) {
//	case GLUT_KEY_LEFT:
//		resources.bottom_paddle.x -= 0.05f;
//		glutPostRedisplay();
//		break;
//	case GLUT_KEY_RIGHT:
//		resources.bottom_paddle.x += 0.05f;
//		glutPostRedisplay();
//		break;
//	default:
//		break;
//	}
//}
//
//void update_ball_location(void) {
//	// Check for collisions
//	switch (detect_collision()) {
//	case TOP_PADDLE_COLLISION:
//		resources.ball.dy *= -1;
//		resources.ball.dx += (resources.ball.x - resources.top_paddle.x) / 15.0f;
//		resources.ball.y -= 0.02;
//		break;
//	case BOTTOM_PADDLE_COLLISION:
//		resources.ball.dy *= -1;
//		resources.ball.dx += (resources.ball.x - resources.bottom_paddle.x) / 15.0f;
//		resources.ball.y += 0.02;
//		break;
//	case NO_COLLISION_DETECTED:
//		break;
//	}
//
//	switch (detect_out_of_bounds()) {
//	case OUT_OF_BOUNDS_TOP:
//		// update score
//		resources.top_paddle.x = 0.0f;
//		resources.bottom_paddle.x = 0.0f;
//		resources.ball.dy = 0.05f;
//		resources.ball.dx = 0.0f;
//		resources.ball.x = 0.0f;
//		resources.ball.y = 0.0f;
//		break;
//	case OUT_OF_BOUNDS_BOTTOM:
//		// update score
//		resources.top_paddle.x = 0.0f;
//		resources.bottom_paddle.x = 0.0f;
//		resources.ball.dy = -0.05f;
//		resources.ball.dx = 0.0f;
//		resources.ball.x = 0.0f;
//		resources.ball.y = 0.0f;
//		break;
//	case OUT_OF_BOUNDS_LEFT:
//		resources.ball.dx *= -1;
//		break;
//	case OUT_OF_BOUNDS_RIGHT:
//		resources.ball.dx *= -1;
//		break;
//	case NOT_OUT_OF_BOUNDS:
//		break;
//	}
//
//	resources.ball.x += resources.ball.dx;
//	resources.ball.y += resources.ball.dy;
//}
//
//void update(int n) {
//	update_ball_location();
//	glutPostRedisplay();
//	glutTimerFunc(25, update, 0);
//}
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
//	glutInitWindowSize(600, 600);
//	glutCreateWindow("Pong");
//	setup();
//
//	glutKeyboardFunc(&keypress);
//	glutSpecialFunc(&special_keypress);
//	glutDisplayFunc(&render);
//	glutTimerFunc(25, update, 0);
//
//	glewInit();
//	if (!GLEW_VERSION_2_0) {
//		fprintf(stderr, "OpenGL 2.0 not available\n");
//		return 1;
//	}
//
//	glutMainLoop();
//	return 0;
//}