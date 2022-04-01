#pragma once

#include "rect.h"
#include "Graphics.h"
#include "Colors.h"


class beveller {

public:
	beveller(int in_steps, int in_colorStep);

	void drawBevelledBrick(Graphics& gfx, rect brick, Color brickColor);


private:
	int bevelSteps = 2; //how many times to bevel the object.
	int bevelColorStep = 100; //how much the color should be deincremented each step. default works well with 2 steps.
};