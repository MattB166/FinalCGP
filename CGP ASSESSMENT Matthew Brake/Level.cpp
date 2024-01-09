#include "Level.h"
#include <string>
#include <ctime>

float Level::WorldX = 800;
float Level::WorldY = 600;

Level::Level()
{
	
}

void Level::PlayGame()
{
	LevelNumber = 1; 
}

void Level::StartTimer()
{
	timeElapsed = 0.0f;
	isTimeRunning = true; 
}

void Level::RenderTimer(float delta,_TTF_Font* font, SDL_Renderer* Renderer)
{
	if (isTimeRunning)
	{
		timeElapsed += (delta/ 25); 

		float RemainingTime = TimeRemaining - timeElapsed; 
		//std::cout << RemainingTime << std::endl; 

		std::string timerText = "TIME LEFT: " + std::to_string(static_cast<int>(RemainingTime)); 
		SDL_Surface* textSurface = TTF_RenderText_Blended(font, timerText.c_str(), { 255,255,255,255 });
		timerTexture = SDL_CreateTextureFromSurface(Renderer, textSurface); 
		timerRect.x = 300;
		timerRect.y = 100;
		timerRect.w = textSurface->w;
		timerRect.h = textSurface->h; 

		SDL_RenderCopy(Renderer, timerTexture, nullptr, &timerRect); 

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(timerTexture); 
		if (RemainingTime <= 0.0f)
		{
			isTimeRunning = false; 
			////game over 
		}

	}
}

float Level::GetRemainingTime()
{
	return TimeRemaining; 
}

void Level::NewLevel()
{
	//once tanks all destroyed. new level loads 
	++LevelNumber; 
	std::cout << "NEW LEVEL. Level is now Level: " << LevelNumber << std::endl;  
}

void Level::CheckPlayerBounds(Tank* tank)
{
	if (tank->Pos.x <= 0)
	{
		tank->Pos.x = 0;
	}
	else if (tank->Pos.x >= WorldX - tank->m_w)
	{
		tank->Pos.x = WorldX - tank->m_w;
	}
	
	if (tank->Pos.x <= 0)
	{
		tank->Pos.y = 0;
	}
	else if (tank->Pos.y >= WorldY - tank->m_h)
	{
		tank->Pos.y = WorldY - tank->m_h;
	}
	
	
	 //compares tank pos to bounds of window and if same the pos 
}

bool Level::CheckBulletBounds(Bullet* bullet)
{
	if (bullet->Pos.x <= 0)
	{
		///mark for deletion 
		return true;
	}
	else if (bullet->Pos.x >= WorldX)
	{
		return true;
	   
	}
	else if (bullet->Pos.y <= 0)
	{
		return true;
	}
	else if (bullet->Pos.y >= WorldY)
	{
		return true; 
	}
	else
	{
		return false;
	}
	return false; 
}

int Level::GetLevel()
{
	return LevelNumber;
}


