#pragma once
#include "Object.h"
#include "PlayerObject.h"
#include "BallObject.h"
#include "TextObject.h"
#include <vector>
#include <playsoundapi.h>


class Scenario
{
public:
	Scenario();

	void reset( float angle = 45 );

	void setBallAngle(float angle);

	float getBallAngle();

	void setPlayerMovement(std::string playerObjName, PlayerObject::MOVE move);

	PlayerObject::MOVE getPlayerMovement(std::string playerName);

	void update(float dt);

	void drawWorld(void);

	~Scenario();

	Scenario(Scenario& other) = delete;

	void operator=(const Scenario&) = delete;

	inline static Scenario* GetInstance() { 
		if (singleton_ == nullptr) {
			singleton_ = new Scenario();
		}
		return singleton_; }

	inline const float dt() { return _delta_time; }

	void resetPlayerScore();

private:
	PlayerObject* getPlayerObj(std::string);

	void computeCollision();

	std::vector<Object*> entities;

	static Scenario* singleton_;
	
	float _delta_time;

	BallObject* ball;
	PlayerObject* player1;
	PlayerObject* player2;
	TextObject* score_p1;
	TextObject* score_p2;

	int score_player1;
	int score_player2;

};