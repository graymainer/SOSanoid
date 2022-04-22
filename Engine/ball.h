#pragma once


#include "util.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include "Sound.h"
#include <random>

class ball {

public:
	ball(vec2 in_pos, vec2 in_vel);

	void reboundX();
	void reboundY(float variance);
	void draw(Graphics& gfx);
	void update(float dt);
	vec2 getVelocity() const;
	bool checkForBoundsCollision(const rect& wall);
	vec2 getPos();
	bool checkForFailure(const rect& wall);
	int isDead() const; //0 = did not hit, 1 = did hit, but still alive, 2 = rip bozo
	rect getBoundingBox() const;

	//power ups
	bool bGod = false;
	bool bDMGBoost = false;
	bool bInstaKill = false;
	void godMode();
	void boostDamage();
	void instaKill();
	void boostSpeed();
	void addLife();
	bool bPenetrate = false;
	int nPenetrations = 0;
	bool bSpedUp = false;



private:

	static constexpr float radius = 7.0f;

	//rect bb; //our bounding box that represents us physically

	int nLives = 3;

	vec2 pos;
	vec2 vel;
	static constexpr float maxVel = 650.0f;
	static constexpr float baseX = 300.0f;

	float boostPenaltyFactor = 1.2; //how much should we boost the player's speed?

	//power up stuff
	float timeElapsed = 0.0f;

	float godTimer = 10.0f;
	float dmgBoostTimer = 10.0f;
	float instaKillTimer = 5.0f;
	float speedHazardTimer = 5.0f;


	//sound stuff

	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> ricochetSndRange;
	std::uniform_int_distribution<int> lifeLostSndRange;



	Sound lifeLostSnd[2];
	Sound ricochetSnd[5];

	Sound hazSpeedSnd = { L"sounds\\haz_speed.wav" };
	Sound pwupDMGSnd = { L"sounds\\pwup_dmgboost.wav" };
	Sound pwupInstaKillSnd = { L"sounds\\pwup_instakill.wav" };
	Sound pwupLifeSnd = { L"sounds\\pwup_life.wav" };
	Sound pwupGodSnd = { L"sounds\\pwup_god.wav" };
	Sound pwupPenetrationSnd = { L"sounds\\pwup_penetration.wav" };
	



};