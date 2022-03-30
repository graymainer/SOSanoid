#include "brick.h"
#include <assert.h>

brick::brick(const rect & in_rect, Color in_clr)
	:
	shape(in_rect),
	color(in_clr),
	bDestroyed(false)
{
}

void brick::draw(Graphics& gfx)
{
	if (bDestroyed)
		return;

	bevel.drawBevelledBrick(gfx, shape, color);
}

bool brick::checkForCollision(const ball & plyBall) const
{
	if (bDestroyed)
		return false;

	return shape.isOverlapping(plyBall.getBoundingBox());
}

void brick::collide(ball & plyBall)
{

	if (bDestroyed)
		return;

	assert(checkForCollision(plyBall));

	rect plyBB = plyBall.getBoundingBox();

	const vec2 ballPos = plyBall.getPos();

	if ( std::signbit(plyBall.getVelocity().x) == std::signbit( (ballPos - getCenter()).x) )
	{
		plyBall.reboundY();
	}
	else if (ballPos.x >= shape.left && ballPos.x <= shape.right)
	{
		plyBall.reboundY();
	}
	else
	{
		plyBall.reboundX();
	}

	bDestroyed = true;

}

vec2 brick::getCenter() const
{
	return shape.getOrigin();
}
