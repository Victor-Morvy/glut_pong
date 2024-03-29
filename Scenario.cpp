#include "Scenario.h"
#include <iostream>
#include <sstream>
#include <time.h>
#include <gl/GL.h>
#include <gl/freeglut.h>

Scenario* Scenario::singleton_ = nullptr;

Scenario::Scenario()
{
	TextObject* txtAlunos = new TextObject("\
		Grupo:\n\
		RA 2004526 � Victor Hugo Martins de Oliveira\n\
		RA 1902879 - Paula Akemi Tanaka\n\
		RA 1800935 � Luiz Almeida\n\
		RA 1902918 - Caio Bueno");
	txtAlunos->setPos(10, 690);
	entities.push_back(txtAlunos);

	TextObject* txtInfo = new TextObject("'Q' and 'A' to control left player\n'I' and 'K' to control right player\n'ESC' to close.");
	txtInfo->setPos(10, 80);
	entities.push_back(txtInfo);

	float playerSize[2] = { 25, 200 };

	score_p1 = new TextObject("1000");
	score_p1->setPos(320, 360);
	entities.push_back(score_p1);

	score_p2 = new TextObject("200");
	score_p2->setPos(960, 360);
	entities.push_back(score_p2);

	player1 = new PlayerObject (playerSize);
	entities.push_back(player1);
	player1->setName("player_1");
	player1->setPos(30, 300);

	player2 = new PlayerObject(playerSize);
	entities.push_back(player2);
	player2->setName("player_2");
	player2->setPos(1250, 300);

	ball = new BallObject( 15);
	entities.push_back(ball);
	ball->setPos(640, 450);
	ball->setAngle(45);
	ball->setVel(5);

	

	score_player1 = 0;
	score_player2 = 0;

}

void Scenario::reset( float angle )
{
	player1->setPos(30, 300);
	player2->setPos(1250, 300);
	ball->setPos(640, 450);
	ball->setAngle(angle);
	ball->setVel(5);
}

void Scenario::setBallAngle(float angle)
{
	ball->setAngle(angle);
}

float Scenario::getBallAngle()
{
	if( ball )
		return ball->getAngle();

	return 0.f;
}

void Scenario::setPlayerMovement(std::string playerObjName, PlayerObject::MOVE move)
{
	PlayerObject* p = getPlayerObj(playerObjName);

	if (!p)
		return;

	p->setMove(move);
	p->setVel(1000);
}

PlayerObject::MOVE Scenario::getPlayerMovement(std::string playerName)
{
	PlayerObject* p = getPlayerObj(playerName);

	if (!p)
		return PlayerObject::MOVE::NONE;

	return p->getMove();
}

void Scenario::resetPlayerScore()
{
	score_player1 = 0;
	score_player2 = 0;
}

PlayerObject* Scenario::getPlayerObj(const std::string name)
{

	for (auto& ett : entities)
		if (ett->getType() == PlayerObject::Type::RECTANGLE &&
			ett->getName() == name)
			return dynamic_cast<PlayerObject*>(ett);

	return nullptr;

}

float Scenario::remap(float value, float istart, float istop, float ostart, float ostop) 
{
	return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

void Scenario::update( float dt )
{
	_delta_time = dt;
	
	std::stringstream ss;
	ss << score_player1;
	score_p1->setText( ss.str() );

	std::stringstream ss2;
	ss2 << score_player2;
	score_p2->setText(ss2.str());

	for (auto& ett : entities)
		ett->update(dt);

	computeCollision();
}

void Scenario::computeCollision()
{
	
	auto rollBackPos = [this]()
	{
		float* lastPos = ball->getLastPos();
		float* pos = ball->getPos();

		pos[0] = lastPos[0];
		pos[1] = lastPos[1];

	};
	
	bool playAudio = false;
	bool playAudioSide = false;

	float tmpAngle = ball->getAngle();
	if (ball->getPos()[1] > 720 - ball->getRadius() / 2) //TOP
	{
		float newY = 720 - ball->getRadius() / 2;
		ball->setY(newY);

		if (ball->getAngle() >= 90.f && ball->getAngle() <= 270.f)
		{
			//rollBackPos();
			tmpAngle = 180.f + ball->getAngle() - 90.f;
		}
		else
		{
			//rollBackPos();
			tmpAngle = 90.f - ball->getAngle();
			tmpAngle += 270.f;
		}
		ball->setAngle(tmpAngle);

		playAudioSide = true;
		
	}
	else if (ball->getPos()[1] < 0 + ball->getRadius() / 2) //BOT
	{	

		float newY = ball->getRadius() / 2;
		ball->setY(newY);

		if (ball->getAngle() >= 90.f && ball->getAngle() <= 270.f)
		{
			//rollBackPos();
			tmpAngle = ball->getAngle() - 180.f;
			tmpAngle = 180.f - tmpAngle;
		}
		else
		{
			//rollBackPos();
			tmpAngle = 360.f - ball->getAngle();
		}
		ball->setAngle(tmpAngle);

		playAudioSide = true;
	}
	else if (ball->getPos()[0] - ball->getRadius() / 2 < player1->getPos()[0] + player1->size()[0] / 2 &&
		ball->getPos()[1] - ball->getRadius() / 2 > player1->getPos()[1] - player1->size()[1] / 2
		&& ball->getPos()[1] + ball->getRadius() / 2 < player1->getPos()[1] + player1->size()[1] / 2) //player 1
	{
		if(1)
		{
			float newX = player1->getPos()[0] + player1->size()[0] / 2 + ball->getRadius() / 2;
			ball->setX(newX);
			
			/*float kickPosTop = player1->getPos()[1] + player1->size()[1] / 2;
			float kickPosBot = player1->getPos()[1] - player1->size()[1] / 2;
			float ballPos = ball->getPos()[1];

			float hitAngle = remap(ballPos, kickPosTop, kickPosBot, 10, -10);

			tmpAngle += hitAngle + 180*/;
			if (ball->getAngle() >= 0.f && ball->getAngle() <= 180.f) //subindo
			{
				//rollBackPos();
				tmpAngle = 180.f - ball->getAngle();
			}
			else //descendo
			{
				//rollBackPos();
				tmpAngle = 270.f - ball->getAngle();
				tmpAngle += 270.f;
			}
			if (ball->vel() < 24)
				ball->setVel(ball->vel() + 3);

			/*if (tmpAngle > 45)
				tmpAngle = 45;
			else if (tmpAngle < -45)
				tmpAngle = -45;*/

			ball->setAngle(tmpAngle);

			playAudio = true;
		}

	}
	else if (ball->getPos()[0] + ball->getRadius() / 2 > player2->getPos()[0] - player2->size()[0] / 2 && 
		ball->getPos()[1] - ball->getRadius() / 2 > player2->getPos()[1] - player2->size()[1] / 2
		&& ball->getPos()[1] + ball->getRadius() / 2 < player2->getPos()[1] + player2->size()[1] / 2) //player2
	{
		if (1)
		{
			float newX = player2->getPos()[0] - player2->size()[0] / 2 - ball->getRadius() / 2;
			ball->setX(newX);

			//float kickPosTop = player2->getPos()[1] + player2->size()[1] / 2;
			//float kickPosBot = player2->getPos()[1] - player2->size()[1] / 2;
			//float ballPos = ball->getPos()[1];

			//float hitAngle = remap(ballPos, kickPosTop, kickPosBot, -10, 10);
			////std::cout << "tmpAngle " << tmpAngle << std::endl;
			//std::cout << "hitAngle " << tmpAngle << std::endl;
			//tmpAngle += hitAngle + 180.f;

			if (ball->getAngle() >= 0.f && ball->getAngle() <= 180.f) //subindo
			{
				//rollBackPos();
				tmpAngle = 180.f - ball->getAngle();
			}
			else //descendo
			{
				//rollBackPos();
				tmpAngle = 360.f - ball->getAngle();
				tmpAngle = 180.f + tmpAngle;
			}

			if (ball->vel() < 24)
				ball->setVel(ball->vel() + 3);

			//if (tmpAngle > 45)
			//	tmpAngle = 45;
			//else if (tmpAngle < -45)
			//	tmpAngle = -45;

			ball->setAngle(tmpAngle);

			playAudio = true;
		}
	}
	else if (ball->getPos()[0] - ball->getRadius() / 2 < 0)
	{
		score_player2 += 1;
		reset(90 + 45);
	}
	else if (ball->getPos()[0] + ball->getRadius() / 2 > 1280)
	{
		score_player1 += 1;
		reset();
	}

	if (playAudio)
	{
#if defined(WIN32)
		PlaySound(TEXT("./resources/hit1.wav"), NULL, SND_ASYNC | SND_FILENAME);
#endif
	}
	if (playAudioSide)
	{
#if defined(WIN32)
		PlaySound(TEXT("./resources/hit2.wav"), NULL, SND_ASYNC | SND_FILENAME);
#endif
	}

}

void Scenario::drawWorld()
{
	//float vertices[] = {
	//	// positions          // colors           // texture coords
	//	 1280, 720, 0,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
	//	 1280, 0, 0.f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
	//		0, 0, 0.f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	//		0, 720, 0,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // top left 
	//};


	glBegin(GL_POLYGON);
	glColor3f(27.f/255.f, 120.f / 255.f, 56.f / 255.f);
	glVertex3f(1280, 720, 0);
	glVertex3f(1280, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 720, 0);
	glEnd();

	glBegin(GL_LINES);
	glLineWidth(24.f);
	glColor3f(1.f, 1.f, 1.f);
	glVertex3f(640, 0, 0);
	glVertex3f(640, 720, 0);
	glEnd();

	for (auto etts : entities)
		etts->draw();
}

Scenario::~Scenario()
{
	for (auto etts : entities)
		delete etts;
	entities.clear();
}
