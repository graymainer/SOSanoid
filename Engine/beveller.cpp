#include "beveller.h"

beveller::beveller(float in_shadeSteps, int in_stepintensity)
	:
	shadeStepIntensity(in_stepintensity),
	shadeSteps(in_shadeSteps)
{
}

void beveller::drawBevelledBrick(Graphics & gfx, rect brick, const Color brickColor)
{

	
	Color bevelColor(brickColor);
	rect bevelBrick(brick.left + shadeSteps, brick.right - shadeSteps, brick.top + shadeSteps, brick.bottom - shadeSteps);

	for (int i = 0; i < shadeSteps; ++i)
	{
		gfx.DrawRect(bevelBrick, bevelColor);

		bevelColor = Color(bevelColor.GetR() - (shadeStepIntensity * (i + 1)), bevelColor.GetG() - (shadeStepIntensity * (i + 1)), bevelColor.GetB() - (shadeStepIntensity * (i + 1)));
		bevelBrick = rect(bevelBrick.left - (i + 1), bevelBrick.right + (i + 1), bevelBrick.top - (i + 1), bevelBrick.bottom + (i + 1));

	}
}
