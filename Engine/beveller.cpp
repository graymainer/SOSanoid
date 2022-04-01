#include "beveller.h"
#include <algorithm>

beveller::beveller(int in_steps, int in_colorStep)
	:
	bevelSteps(in_steps),
	bevelColorStep(in_colorStep)
{
}

void beveller::drawBevelledBrick(Graphics & gfx, rect brick, Color brickColor)
{

	
	int steppedRed = std::clamp(brickColor.GetR() - (bevelColorStep * bevelSteps), 0, 255);
	int steppedGreen = std::clamp(brickColor.GetG() - (bevelColorStep * bevelSteps), 0, 255);
	int steppedBlue = std::clamp(brickColor.GetB() - (bevelColorStep * bevelSteps), 0, 255);

	float steppedLeft = brick.left;
	float steppedRight = brick.right;
	float steppedTop = brick.top;
	float steppedBot = brick.bottom;


	for (int step = 1; step < bevelSteps + 1; step++) //this actually works, but the color is screwed up. first of all, we end up adding unwanted color, and secondly, on the second step, we reach a color, then stop.
	{
		for (int y = steppedTop; y < steppedBot; ++y)
		{
			for (int x = steppedLeft; x < steppedRight; ++x)
			{
				gfx.PutPixel(x, y, Color(steppedRed, steppedGreen, steppedBlue));
			}
		}


		steppedLeft += step;
		steppedRight -= step;
		steppedTop += step;
		steppedBot -= step;

		steppedRed += std::clamp(bevelColorStep, 0, 255);
		steppedGreen += std::clamp(bevelColorStep, 0, 255);
		steppedBlue += std::clamp(bevelColorStep, 0, 255);

	}
}
