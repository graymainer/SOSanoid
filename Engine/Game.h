/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "brick.h"
#include "rect.h"
#include "ball.h"
#include "paddle.h"
#include "FrameTimer.h"
#include "Sound.h"
#include <random>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(float dt);
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	/********************************/

	bool bStarted = false;
	bool bGameWon = false;
	bool bGameOver = false;
	bool playedOverSound = false;

	static constexpr float brickWidth = 40.0f;
	static constexpr float brickHeight = 24.0f;
	static constexpr int nBricksAcross = 18;
	static constexpr int nBricksDown = 4;
	static constexpr int nBricks = nBricksAcross * nBricksDown;

	FrameTimer ft;

	brick bricks[nBricks];

	rect bounds;

	ball playerBall;

	paddle playerPaddle;

	//sound stuff

	//for our random sound
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> impactSFXRand;
	std::uniform_int_distribution<int> deathSFXRand;
	std::uniform_int_distribution<int> breakSFXRand;

	Sound paddleSound;

	Sound impactSFX[5];

	Sound deathSFX[2];

	Sound breakSFX[3];

	Sound wonSound;
	Sound failSound;
	
};