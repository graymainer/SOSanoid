#include "ball.h"

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

void ball::reboundY()
{
	vel.y = -vel.y;
}

void ball::draw(Graphics& gfx)
{
	SpriteCodex::DrawBall(pos, gfx);
}

void ball::update(float dt)
{
	pos += vel * dt;
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
		reboundY();
		pos.x += wall.left - bb.left;
		reboundX();

		return true;
	}

	if (bb.top < wall.top && bb.right > wall.right)
	{
		pos.y += wall.top - bb.top;
		reboundY();
		pos.x -= wall.right - bb.right;
		reboundX();

		return true;
	}

	if (bb.bottom > wall.bottom && bb.left < wall.left)
	{
		pos.y -= bb.bottom - wall.bottom;
		reboundY();
		pos.x += wall.left - bb.left;
		reboundX();

		return true;
	}

	if (bb.bottom > wall.bottom && bb.right > wall.right)
	{
		pos.y -= bb.bottom - wall.bottom;
		reboundY();
		pos.x -= bb.right - wall.right;
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
		reboundY();
		return true;
	}
	else if (bb.bottom > wall.bottom)
	{
		pos.y -= bb.bottom - wall.bottom;
		reboundY();
		return true;
	}

	return false;
}

vec2 ball::getPos()
{
	return pos;
}

rect ball::getBoundingBox() const
{
	return rect::fromCenter(pos, radius, radius);
}


