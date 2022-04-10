#include "ball.h"
#include <algorithm> //for std::clamp

ball::ball(vec2 in_pos, vec2 in_vel)
	:
	pos(in_pos),
	vel(in_vel)
	//bb(in_pos, radius, radius) //un-init
{
}

void ball::reboundX()
{
	vel.x = -vel.x;
}

void ball::reboundY(float variance)
{

	vel.y = -vel.y;
	if (variance != 0)
	{
		vel.x = baseX * variance;
	}
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
		return true;
	}

	return false;
}

rect ball::getBoundingBox() const
{
	return rect::fromCenter(pos, radius, radius);
}


