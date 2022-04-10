#include "beveller.h"
#include <algorithm>

beveller::beveller(int in_steps, int in_colorStepFactor)
	:
	bevelSteps(4),
	bevelColorStepFactor(2)
{
}

void beveller::drawBevelledBrick(Graphics & gfx, rect brick, Color brickColor)
{
	//looks good, but is expensive due to the way that we draw.
	//if instead of drawing an entire rectangle every brick, we drew an outline, it'd be much cheaper.

	int steppedRed = std::clamp(brickColor.GetR() / (bevelColorStepFactor * bevelSteps), 0, 255);
	int steppedGreen = std::clamp(brickColor.GetG() / (bevelColorStepFactor * bevelSteps), 0, 255);
	int steppedBlue = std::clamp(brickColor.GetB() / (bevelColorStepFactor * bevelSteps), 0, 255);

	float steppedLeft = brick.left;
	float steppedRight = brick.right;
	float steppedTop = brick.top;
	float steppedBot = brick.bottom;


	for (int step = 1; step < bevelSteps + 2; step++) //this actually works, but the color is screwed up. first of all, we end up adding unwanted color, and secondly, on the second step, we reach a color, then stop.
	{
		for (int y = (int)steppedTop; y < steppedBot; ++y)
		{
			for (int x = (int)steppedLeft; x < steppedRight; ++x)
			{
				gfx.PutPixel(x, y, Color(steppedRed, steppedGreen, steppedBlue));
			}
		}

		steppedLeft += step; //step must be 1 first time around for this to work.
		steppedRight -= step;
		steppedTop += step;
		steppedBot -= step;

		steppedRed = std::clamp(steppedRed * bevelColorStepFactor, 0, 255);
		steppedGreen = std::clamp(steppedGreen * bevelColorStepFactor, 0, 255);
		steppedBlue = std::clamp(steppedBlue * bevelColorStepFactor, 0, 255);

	}
}
