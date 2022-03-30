/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	//testBrick(rect(450.0f, 550.0f, 485.0f, 515.0f), Colors::Blue),
	bounds(0.0f, (float)gfx.ScreenWidth, 40.0f, (float)gfx.ScreenHeight),
	playerBall(vec2(gfx.ScreenWidth / 2, gfx.ScreenHeight / 2), vec2(300.0f, 300.0f)),
	playerPaddle(vec2(gfx.ScreenWidth / 2, gfx.ScreenHeight * 0.9), 60.0f, 15.0f, 20.0f, Colors::Gray, Colors::Blue),
	rng(rd()),
	impactSFXRand(0, 4),
	deathSFXRand(0, 1),
	breakSFXRand(0, 2),
	paddleSound(L"sounds\\arkpad.wav"),
	impactSFX{ 
		Sound(L"sounds\\ballHit0.wav"), 
		Sound(L"sounds\\ballHit1.wav"), 
		Sound(L"sounds\\ballHit2.wav"), 
		Sound(L"sounds\\ballHit3.wav"), 
		Sound(L"sounds\\ballHit4.wav")
	},
	deathSFX{ 
		Sound(L"sounds\\ballDie0.wav"), 
		Sound(L"sounds\\ballDie1.wav")
	},
	breakSFX{
	Sound(L"sounds\\brickBreak0.wav"),
	Sound(L"sounds\\brickBreak1.wav"),
	Sound(L"sounds\\brickBreak2.wav")
	},
	wonSound(L"sounds\\gameWon.wav"),
	failSound(L"sounds\\gameOver.wav")
{
	const Color Colors[4] = { Colors::Red, Colors::Green, Colors::Blue, Colors::Cyan };

	const vec2 topLeft(40.0f, 40.0f);

	int i = 0;

	for (int y = 0; y < nBricksDown; y++)
	{
		const Color c = Colors[y];
		for (int x = 0; x < nBricksAcross; x++)
		{
			bricks[i] = brick(rect(topLeft + vec2(x * brickWidth, y * brickHeight), brickWidth, brickHeight), c);
			i++;
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	float elapsedTime = ft.Mark();
	while (elapsedTime > 0.0f)
	{
		const float dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{

	if (bStarted && !(bGameOver || bGameWon)) //main game stuff
	{
		if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
			bStarted = false;

		//debug
		if (wnd.kbd.KeyIsPressed('W'))
			bGameWon = true;
		if (wnd.kbd.KeyIsPressed('F'))
			bGameOver = true;

		playerPaddle.update(wnd.mouse, dt);
		playerPaddle.clampToScreen(bounds);

		playerBall.update(dt);


		if (playerPaddle.paddleBall(playerBall))
			paddleSound.Play(1.0f, 0.2f);


		bool bHasCollided = false;
		float closestCollideDistSq;
		int closestCollideIndex = 0;

		for (int i = 0; i < nBricks; i++)
		{
			if (bricks[i].checkForCollision(playerBall))
			{
				const float newCollideDistSq = (playerBall.getPos() - bricks[i].getCenter()).getLengthSq();

				if (bHasCollided)
				{
					if (newCollideDistSq < closestCollideDistSq)
					{
						closestCollideDistSq = newCollideDistSq;
						closestCollideIndex = i;
					}
				}
				else
				{
					closestCollideDistSq = newCollideDistSq;
					closestCollideIndex = i;
					bHasCollided = true;
				}
			}
		}

		if (bHasCollided)
		{
			bricks[closestCollideIndex].collide(playerBall);
			breakSFX[breakSFXRand(rng)].Play(1.0f, 0.05f);
			playerPaddle.resetCooldown();
		}

		if (playerBall.checkForFailure(bounds))
		{
			bGameOver = true;
			return;
		}


		if (playerBall.checkForBoundsCollision(bounds))
		{
			impactSFX[impactSFXRand(rng)].Play(1.0f, 0.1f);
			playerPaddle.resetCooldown();
		}
	}
	else if (bGameWon)
	{
		if (!playedOverSound) //protects your ears.
		{
			wonSound.Play(1.0f, 0.1f);
			playedOverSound = true;
		}
	}
	else if (bGameOver)
	{
		if (!playedOverSound)
		{
			failSound.Play(1.0f, 0.1f);
			playedOverSound = true;
		}
	}
	else //do main menu stuff
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
			bStarted = true;
	}

}

void Game::ComposeFrame()
{
	if (bStarted && !(bGameOver || bGameWon)) //main game stuff
	{
		playerPaddle.draw(gfx);
		playerBall.draw(gfx);
		for (brick& b : bricks)
		{
			b.draw(gfx);
		}
	}
	else if (bGameWon)
	{
		SpriteCodex::drawGameWon(vec2(gfx.ScreenWidth / 2, gfx.ScreenHeight / 2), gfx);
	}
	else if (bGameOver)
	{
		SpriteCodex::drawGameOver(vec2 (gfx.ScreenWidth / 2, gfx.ScreenHeight / 2), gfx);
	}
	else //sitting on main menu
	{
		SpriteCodex::drawTitle(vec2(gfx.ScreenWidth / 2, gfx.ScreenHeight / 2), gfx);
	}



}
