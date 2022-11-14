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