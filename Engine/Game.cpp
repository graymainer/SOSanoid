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
	playerBall(vec2(gfx.ScreenWidth / 2, gfx.ScreenHeight / 2), vec2(300.0f, 300.0f)),
	playerPaddle(vec2(gfx.ScreenWidth / 2, gfx.ScreenHeight * 0.9), 60.0f, 15.0f, 20.0f, Colors::Gray, Colors::Blue),

	wonSound(L"sounds\\gameWon.wav"),
	failSound(L"sounds\\gameOver.wav"),
	deathSound(L"sounds\\death.wav")

{
	int i = 0;

	for (int y = 0; y < nBricksDown; y++)
	{
		const Color c = gridColors[y];

		for (int x = 0; x < nBricksAcross; x++)
		{
			bricks[i] = brick(rect(gridPos + vec2(x * brickWidth, y * brickHeight), brickWidth, brickHeight), c, brick::type::PWUP_INSTAKILL, 1);
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
		bReady = false;

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


		playerPaddle.paddleBall(playerBall);


		bool bHasCollided = false;
		float closestCollideDistSq;
		int closestCollideIndex = 0;

		for (int i = 0; i < brickEdict; i++)
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
			if (bricks[closestCollideIndex].collide(playerBall) == brick::type::PWUP_FASTPADDLE)
				playerPaddle.boostSpeed();


			//breakSFX[breakSFXRand(rng)].Play(1.0f, 0.05f);
			playerPaddle.resetCooldown();
			nBricks -= 1;
		}

		if (nBricks <= 0)
		{
			bGameWon = true;
			return;
		}
			

		//checks if we hit the fail boundary, and if so; if we are now dead.
		if (playerBall.checkForFailure(bounds))
		{
			playerPaddle.startCooldown();

			if (bGodMode)
				return;

			if (playerBall.isDead())
			{
				deathSound.Play(1.0f, 0.25f);
				bGameOver = true;
				return;
			}
		}




		if (playerBall.checkForBoundsCollision(bounds))
		{
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
		if (wnd.kbd.KeyIsPressed(VK_RETURN) && !bReady)
		{
			bReady = true;

		}

		if (bReady)
		{
			if (readyElapsed >= readyTime * 500.0f)
			{
				bStarted = true;
			}
			else
			{
				readyElapsed += 1.0f;
				SpriteCodex::DrawReady(vec2(gfx.ScreenWidth / 2, gfx.ScreenHeight / 2), gfx);
			}

		}
			
	}

}

void Game::drawBorders()
{
	gfx.DrawRect(borderLeft, borderColor);
	gfx.DrawRect(borderRight, borderColor);
	gfx.DrawRect(borderTop, borderColor);
}

void Game::ComposeFrame()
{
	if (bStarted && !(bGameOver || bGameWon)) //main game stuff
	{
		
		drawBorders();
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
		SpriteCodex::DrawGameOver(vec2 (gfx.ScreenWidth / 2, gfx.ScreenHeight / 2), gfx);
	}
	else //sitting on main menu
	{
		if (bReady)
			return;

		SpriteCodex::DrawTitle(vec2(gfx.ScreenWidth / 2, gfx.ScreenHeight / 2), gfx);
	}



}
