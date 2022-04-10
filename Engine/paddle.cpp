#include "paddle.h"

paddle::paddle(const vec2& in_pos, const float in_halfWidth, const float in_halfHeight, const float in_wingWidth, const Color& in_clr0, const Color& in_clr1)
	:
	pos(in_pos),
	halfWidth(in_halfWidth),
	halfHeight(in_halfHeight),
	wingWidth(in_wingWidth),
	paddleClr(in_clr0),
	paddleWingClr(in_clr1)
{
}

void paddle::update(const Mouse& mou, const float dt)
{
	vec2 vel = vec2(0, 0);

	vel.x = (float)mou.GetPosX() - pos.x;

	if (vel.getLengthSq() < 50.0f) //too low will cause weird stutter-y movement
		return;

	pos.x += vel.normalize().x * speed * dt;
}

void paddle::draw(Graphics & gfx)
{
	rect paddleRect = getRect();
	gfx.DrawRect(paddleRect, paddleWingClr);

	paddleRect.left += wingWidth;
	paddleRect.right -= wingWidth;

	gfx.DrawRect(paddleRect, paddleClr);
}

bool paddle::paddleBall(ball & plyBall)
{
	if (bCooldown)
		return false;

	const rect paddleBB = getRect();
	const vec2 ballPos = plyBall.getPos();

	if (paddleBB.isOverlapping(plyBall.getBoundingBox()))
	{	
		if (std::signbit(plyBall.getVelocity().x) == std::signbit((ballPos - pos).x))
		{
			float distToOrigin = (ballPos.x - pos.x) / varianceFactor;

			plyBall.reboundY(distToOrigin);
		}
		else if (ballPos.x >= paddleBB.left && ballPos.x <= paddleBB.right)
		{
			float distToOrigin = (ballPos.x - pos.x) / varianceFactor;

			plyBall.reboundY(distToOrigin);
		}
		else
		{
			plyBall.reboundX();
		}

		bCooldown = true;
		return true;
	}

	return false;
}

void paddle::clampToScreen(const rect& bounds)
{
	const rect bb = getRect();

	if (bb.left < bounds.left)
		pos.x += bounds.left - bb.left;
	else if (bb.right > bounds.right)
		pos.x -= bb.right - bounds.right;

}

rect paddle::getRect()
{
	return rect::fromCenter(pos, halfWidth, halfHeight);
}

void paddle::resetCooldown()
{
	bCooldown = false;
}

void paddle::startCooldown()
{
	bCooldown = true;
}
