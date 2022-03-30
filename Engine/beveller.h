#pragma once

#include "rect.h"
#include "Graphics.h"
#include "Colors.h"


class beveller {

public:
	beveller(float in_shadeSteps, int in_stepintensity);

	void drawBevelledBrick(Graphics& gfx, rect brick, const Color brickColor);


private:
	Color bevelShade;

	int shadeStepIntensity = 1;
	float shadeSteps = 2.0f;
};