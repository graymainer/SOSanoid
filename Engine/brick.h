#pragma once

#include "rect.h"
#include "Colors.h"
#include "Graphics.h"
#include "ball.h"
#include "beveller.h"
#include <random>
#include "Sound.h"

class brick {
public:
	enum class type { //these are the different possible types of bricks.

		EMPTY, //fuck & all
		DEFAULT, //the normal, default, vanilla flavored brick. my favorite
		INDESTRUCTIBLE, //good thing im indestructible
		EXPLODABLE, //when destroyed, it will bring 4 other bricks in a cross pattern down with it.
		DURABLE, //doubles the brick's hp.
		PWUP_LIFE, //gives the player an additional life.
		PWUP_FASTPADDLE, //speeds up the paddle for 10 seconds
		PWUP_GODMODE, //makes the ball invincible for 10 seconds
		PWUP_PENETRATE, //makes the ball penetrate through one brick and then hit the next. lasts for 2 uses.
		PWUP_MOREDMG, //makes you do double the damage for 10 seconds
		PWUP_INSTAKILL, //makes you insta kill every brick for 5 seconds
		HAZ_SPEEDUP, //speeds up the ball
		HAZ_REPAIR //repairs all non broken bricks around it when hit.
	};



public:
	brick() = default;
	brick(const rect& in_rect, Color in_clr, type in_type, int in_hp);
	void draw(Graphics& gfx);
	bool checkForCollision(const ball& plyBall) const;
	type collide(ball& plyBall);
	vec2 getCenter() const;

private:
	static constexpr float padding = 2.0f;
	Color color;
	rect shape;
	bool bDestroyed = true;
	int hp = 2;

	void repairBricks();
	void explode();

	beveller bevel = beveller(2, 2); //for some reason causes weird reference to brick constructor that is deleted errors when init through the member init list. so we do it here, instead.
	type brickType = type::EMPTY; //WHAT ARE YOU


	//sound stuff




	Sound indestructableSnd = { L"Sounds\\brickReflect.wav" };
	Sound explodeSnd[3];
	Sound breakSnd[4];
	Sound repairSnd = { L"Sounds\\haz_repair.wav" };
	Sound penetrateSnd = { L"sounds\\brickPenetrate.wav" };
};