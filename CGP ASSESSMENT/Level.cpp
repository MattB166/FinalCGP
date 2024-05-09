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
			Gameover = true; 
			
		}

	}
}

void Level::RenderAmmo(TTF_Font* font, SDL_Renderer* renderer, Tank* Player)
{
	PlayerAmmo = Player->Ammo;

	std::string ammoText = "Ammo: " + std::to_string(PlayerAmmo);
	SDL_Surface* textSurf = TTF_RenderText_Blended(font, ammoText.c_str(), { 0,0,255,255 });
	SDL_Texture* ammoTexture = SDL_CreateTextureFromSurface(renderer, textSurf);

	SDL_Rect AmmoRect;
	AmmoRect.x = 10;
	AmmoRect.y = 10; 
	AmmoRect.w = textSurf->w;
	AmmoRect.h = textSurf->h; 

	SDL_RenderCopy(renderer, ammoTexture, nullptr, &AmmoRect);

	SDL_FreeSurface(textSurf);
	SDL_DestroyTexture(ammoTexture); 
}

void Level::RenderHealth(TTF_Font* font, SDL_Renderer* renderer, Tank* Player)
{
	PlayerHealth = Player->Health; 

	std::string HealthText = "Health: " + std::to_string(PlayerHealth);
	SDL_Surface* textsurf = TTF_RenderText_Blended(font, HealthText.c_str(), { 0,255,255,255 });
	SDL_Texture* HealthTexture = SDL_CreateTextureFromSurface(renderer, textsurf); 

	SDL_Rect HealthRect;
	HealthRect.x = 10;
	HealthRect.y = 50;

	HealthRect.w = textsurf->w;
	HealthRect.h = textsurf->h; 

	SDL_RenderCopy(renderer, HealthTexture, nullptr, &HealthRect);

	SDL_FreeSurface(textsurf);
	SDL_DestroyTexture(HealthTexture); 
}

void Level::RenderPlayerLost(TTF_Font* font, SDL_Renderer* renderer, Tank* Player)
{
	Gameover = Player->bHasLostGame();

	if (Gameover)
	{
		std::string GameOverText = "GAME OVER. YOU LOST ! "; 
		SDL_Surface* Textsurf = TTF_RenderText_Blended(font, GameOverText.c_str(), { 0,0,255,255 });
		SDL_Texture* GameOverTexture = SDL_CreateTextureFromSurface(renderer, Textsurf);

		SDL_Rect EndGameRect;
		EndGameRect.x = 250;
		EndGameRect.y = 400;

		EndGameRect.w = Textsurf->w;
		EndGameRect.h = Textsurf->h; 

		SDL_RenderCopy(renderer, GameOverTexture, nullptr, &EndGameRect); 

		SDL_FreeSurface(Textsurf);
		SDL_DestroyTexture(GameOverTexture); 
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
	
	if (tank->Pos.y <= 0)
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


