#include "brick.h"
#include <assert.h>

brick::brick(const rect & in_rect, Color in_clr, type in_type, int in_hp)
	:
	shape(in_rect),
	color(in_clr),
	bDestroyed(false),
	brickType(in_type),
	hp(in_hp),

	explodeSnd{
		Sound(L"sounds\\brickExplode0.wav"),
		Sound(L"sounds\\brickExplode1.wav"),
		Sound(L"sounds\\brickExplode2.wav")
	},

	breakSnd{
		Sound(L"sounds\\brickBreak0.wav"),
		Sound(L"sounds\\brickBreak1.wav"),
		Sound(L"sounds\\brickBreak2.wav"),
		Sound(L"sounds\\brickBreak3.wav")
	}
{
	if (brickType == type::DURABLE)
		hp *= 2;
}

void brick::draw(Graphics& gfx)
{
	if (bDestroyed || brickType == type::EMPTY)
		return;

	Color clr;

	switch (brickType)
	{
	default: //we now need to assume that 'default:' goes for all normal ass vanilla bricks
		clr = color;
		break;

	case type::DURABLE:
		clr = Colors::Yellow;
		break;

	case type::EXPLODABLE:
		clr = Color(252, 127, 3);
		break;

	case type::HAZ_REPAIR:
		clr = Color(79, 118, 189);
		break;

	case type::HAZ_SPEEDUP:
		clr = Colors::Cyan;
		break;

	case type::INDESTRUCTIBLE:
		clr = Colors::Gray;
		break;

	case type::PWUP_FASTPADDLE:
		clr = Colors::Magenta;
		break;

	case type::PWUP_GODMODE:
		clr = Colors::White;
		break;

	case type::PWUP_INSTAKILL:
		clr = Colors::Red;
		break;

	case type::PWUP_LIFE:
		clr = Colors::Blue;
		break;

	case type::PWUP_MOREDMG:
		clr = Color(252, 73, 3);
		break;

	case type::PWUP_PENETRATE:
		clr = Colors::Green;
		break;
	}


	bevel.drawBevelledBrick(gfx, shape, clr);
}

bool brick::checkForCollision(const ball & plyBall) const
{
	if (bDestroyed)
		return false;

	return shape.isOverlapping(plyBall.getBoundingBox());
}

bool brick::collide(ball & plyBall, paddle & plyPaddle, const int nBrickCount)
{

	if (bDestroyed || brickType == type::EMPTY)
		return false;

	assert(checkForCollision(plyBall));

	rect plyBB = plyBall.getBoundingBox();

	const vec2 ballPos = plyBall.getPos();

	if (plyBall.nPenetrations >= 2)
	{
		plyBall.bPenetrate = false;
		plyBall.nPenetrations = 0;
	}
		

	if (!plyBall.bPenetrate || brickType == type::INDESTRUCTIBLE)
	{
		if (std::signbit(plyBall.getVelocity().x) == std::signbit((ballPos - getCenter()).x))
		{
			plyBall.reboundY(0);
		}
		else if (ballPos.x >= shape.left && ballPos.x <= shape.right)
		{
			plyBall.reboundY(0);
		}
		else
		{
			plyBall.reboundX();
		}
	}
	else
		plyBall.nPenetrations += 1;

		if (brickType != type::INDESTRUCTIBLE)
		{
			if (plyBall.bDMGBoost)
				hp -= 2;
			else
				hp -= 1;

			std::random_device rd;
			std::mt19937 rng(rd());
			std::uniform_int_distribution<int> breakSndRange(0, 3);

			if (plyBall.bInstaKill || hp <= 0)
			{
				bDestroyed = true;

				

				breakSnd[breakSndRange(rng)].Play(1.0f, 0.15f);

				switch (brickType)
				{

					case type::PWUP_GODMODE:
					{
						plyBall.godMode();
						break;
					}

					case type::PWUP_MOREDMG:
					{
						plyBall.boostDamage();
						break;
					}

					case type::PWUP_INSTAKILL:
					{
						plyBall.instaKill();
						break;
					}

					case type::PWUP_LIFE:
					{
						plyBall.addLife();
						break;
					}

					case type::PWUP_PENETRATE:
					{
						plyBall.bPenetrate = true;
						break;
					}

					case type::PWUP_FASTPADDLE:
					{
						plyPaddle.boostSpeed();
						break;
					}

					case type::HAZ_SPEEDUP:
					{
						plyBall.boostSpeed();
						break;
					}

					case type::HAZ_REPAIR:
					{
						repairBricks();
						break;
					}

					case type::EXPLODABLE:
					{
						explode();
						break;
					}

					default:
					{
						break;
					}

				}

				brickType = type::EMPTY; //rip bozo, we've been destroyed so tell the engine that we're now empty space.
				
				return true;
			}
			else
				breakSnd[breakSndRange(rng)].Play(1.5f, 0.15f); //temp, need hit sounds


		}
		else
			indestructableSnd.Play(1.0f, 0.05f);

	return false;
}

vec2 brick::getCenter() const
{
	return shape.getOrigin();
}

void brick::repairBricks()
{
	repairSnd.Play(1.0f, 0.1f);
}

void brick::explode()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> explodeSndRange(0, 2);

	explodeSnd[explodeSndRange(rng)].Play(1.0f, 0.15f); //for now... need method of finding nearby bricks
}
