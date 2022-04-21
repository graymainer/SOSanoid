#include "ball.h"
#include <algorithm> //for std::clamp, requires project to use c++ 17!

ball::ball(vec2 in_pos, vec2 in_vel)
	:
	pos(in_pos),
	vel(in_vel),
	//bb(in_pos, radius, radius) //un-init

	lifeLostSnd {
		Sound(L"sounds\\ballDie0.wav"),
		Sound(L"sounds\\ballDie1.wav")
	},

	ricochetSnd{
		Sound(L"sounds\\ballHit0.wav"),
		Sound(L"sounds\\ballHit1.wav"),
		Sound(L"sounds\\ballHit2.wav"),
		Sound(L"sounds\\ballHit3.wav"),
		Sound(L"sounds\\ballHit4.wav")
	},

	ricochetSndRange(0, 4),
	lifeLostSndRange(0, 1)
{
}

void ball::reboundX()
{
	vel.x = -vel.x;
	ricochetSnd[ricochetSndRange(rng)].Play(1.0f, 0.1f);
}

void ball::reboundY(float variance)
{

	vel.y = -vel.y;
	if (variance != 0)
	{
		vel.x = baseX * variance;
	}
	ricochetSnd[ricochetSndRange(rng)].Play(1.0f, 0.1f);
}

void ball::draw(Graphics& gfx)
{
	SpriteCodex::DrawBall(pos, gfx);
}

void ball::update(float dt)
{
	pos += vel * dt;

	vel.x = std::clamp(vel.x, -maxVel, maxVel);
	vel.y = std::clamp(vel.y, -maxVel, maxVel);

	timeElapsed += 1.0f;

	if (!bGod && !bDMGBoost && !bInstaKill && !bSpedUp)
	{
		timeElapsed = 0.0f;
		return;
	}


	if (timeElapsed >= godTimer * 500.0f)
		bGod = false;

	if (timeElapsed >= dmgBoostTimer * 500.0f)
		bDMGBoost = false;

	if (timeElapsed >= instaKillTimer * 500.0f)
		bInstaKill = false;

	if (timeElapsed >= speedHazardTimer * 500.0f)
		bSpedUp = false;


}

vec2 ball::getVelocity() const
{
	return vel;
}



bool ball::checkForBoundsCollision(const rect & wall)
{
	const rect bb = getBoundingBox();

	//check if we're hitting any corners
	if (bb.top < wall.top && bb.left < wall.left)
	{
		pos.y += wall.top - bb.top;
		reboundY(0);
		pos.x += wall.left - bb.left;
		reboundX();

		return true;
	}

	if (bb.top < wall.top && bb.right > wall.right)
	{
		pos.y += wall.top - bb.top;
		reboundY(0);
		pos.x -= wall.right - bb.right;
		reboundX();

		return true;
	}

	if (bb.left < wall.left)
	{
		pos.x += wall.left - bb.left;
		reboundX();
		return true;
	}
	else if (bb.right > wall.right)
	{
		pos.x -= bb.right - wall.right;
		reboundX();
		return true;
	}
	else if (bb.top < wall.top)
	{
		pos.y += wall.top - bb.top;
		reboundY(0);
		return true;
	}

	return false;
}

vec2 ball::getPos()
{
	return pos;
}

bool ball::checkForFailure(const rect & wall)
{
	rect bb = getBoundingBox();

	if (bb.bottom > wall.bottom)
	{
		pos.y -= bb.bottom - wall.bottom;

		if (!bGod)
		{
			nLives -= 1;
			lifeLostSnd[lifeLostSndRange(rng)].Play(1.0f, 0.25f);
		}
			

		reboundY(0);
		return true;
	}

	return false;
}

rect ball::getBoundingBox() const
{
	return rect::fromCenter(pos, radius, radius);
}

void ball::godMode()
{
	bGod = true;


	//do stuff to figure out if the right amount of time has passed here, then set to false.
}

void ball::boostDamage()
{
	bDMGBoost = true;
	//do stuff to figure out if the right amount of time has passed here, then set to false.
}

void ball::instaKill()
{
	bInstaKill = true;
	//do stuff to figure out if the right amount of time has passed here, then set to false.
}

void ball::addLife()
{
	nLives += 1;
}

int ball::isDead() const
{
	return nLives <= 0;
}

void ball::boostSpeed() //boosts the speed by the boostPenaltyFactor and clamps within our speed range.
{
	vel.x = std::clamp(vel.x *= boostPenaltyFactor, -maxVel, maxVel);
	vel.y = std::clamp(vel.y *= boostPenaltyFactor, -maxVel, maxVel);
	bSpedUp = true;
}


