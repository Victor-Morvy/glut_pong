#include "Scenario.h"
#include <iostream>
#include <sstream>

Scenario* Scenario::singleton_ = nullptr;

Scenario::Scenario()
{
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

void Scenario::update( float dt )
{
	_delta_time = dt;

	computeCollision();
	
	std::stringstream ss;
	ss << score_player1;
	score_p1->setText( ss.str() );

	std::stringstream ss2;
	ss2 << score_player2;
	score_p2->setText(ss2.str());

	for (auto& ett : entities)
		ett->update(dt);
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
	
	float tmpAngle = 35;
	if (ball->getPos()[1] > 720 - ball->getRadius() / 2)
	{
		
		if (ball->getAngle() >= 90.f && ball->getAngle() <= 270.f)
		{
			rollBackPos();
			tmpAngle = 180.f + ball->getAngle() - 90.f;
		}
		else
		{
			rollBackPos();
			tmpAngle = 90.f - ball->getAngle();
			tmpAngle += 270.f;
		}
		ball->setAngle(tmpAngle);
		
	}
	else if (ball->getPos()[1] < 0 + ball->getRadius() / 2)
	{	
		if (ball->getAngle() >= 90.f && ball->getAngle() <= 270.f)
		{
			rollBackPos();
			tmpAngle = ball->getAngle() - 180.f;
			tmpAngle = 180.f - tmpAngle;
		}
		else
		{
			rollBackPos();
			tmpAngle = 360.f - ball->getAngle();
		}
		ball->setAngle(tmpAngle);
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
	else if (ball->getPos()[0] - ball->getRadius() / 2 < player1->getPos()[0] + player1->size()[0] / 2)
	{
		if(ball->getPos()[1] - ball->getRadius() / 2 > player1->getPos()[1] - player1->size()[1] / 2
			&& ball->getPos()[1] + ball->getRadius() / 2 < player1->getPos()[1] + player1->size()[1] / 2)
		{
			if (ball->getAngle() >= 0.f && ball->getAngle() <= 180.f) //subindo
			{
				rollBackPos();
				tmpAngle = 180.f - ball->getAngle();
			}
			else //descendo
			{
				rollBackPos();
				tmpAngle = 270.f - ball->getAngle();
				tmpAngle += 270.f;
			}
			if (ball->vel() < 30)
				ball->setVel(ball->vel() + 3);

			ball->setAngle(tmpAngle);
		}

	}
	else if (ball->getPos()[0] + ball->getRadius() / 2 > player2->getPos()[0] - player2->size()[0] / 2)
	{
		if (ball->getPos()[1] - ball->getRadius() / 2 > player2->getPos()[1] - player2->size()[1] / 2
			&& ball->getPos()[1] + ball->getRadius() / 2 < player2->getPos()[1] + player2->size()[1] / 2)
		{
			if (ball->getAngle() >= 0.f && ball->getAngle() <= 180.f) //subindo
			{
				rollBackPos();
				tmpAngle = 180.f - ball->getAngle();
			}
			else //descendo
			{
				rollBackPos();
				tmpAngle = 360.f - ball->getAngle();
				tmpAngle = 180.f + tmpAngle;
			}

			if (ball->vel() < 30)
				ball->setVel(ball->vel() + 3);

			ball->setAngle(tmpAngle);
		}
	}
	

}

void Scenario::drawWorld()
{
	glBegin(GL_LINES);
	glColor3f(0.5f, 0.f, 0.5f);
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
