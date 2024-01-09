#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Tank.h"
#include "EnemyTankSpawner.h"
#include "Collision.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "TimeMaths.h"
#include "Input_Manager.h"
#include "Obstacle.h"
#include "Level.h"



SDL_Window* g_sdlWindow;
SDL_Renderer* g_sdlRenderer;
const Uint8* keystate;
TTF_Font* g_font; 
float g_cameraX = 0;
float g_cameraY = 0; 
Level Game;

SDL_Texture* LoadTexture(const char* filename)
{
	//load door bmp as a surface		
	SDL_Surface* image = IMG_Load(filename);
	if (image == nullptr)
	{
		std::cout << "Failed to load " << filename << ". SDL ERROR: " << IMG_GetError() << std::endl;
	}

	//convert surface of loaded bmp into a texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(g_sdlRenderer, image);
	if (texture == nullptr)
	{
		std::cout << "Failed to create texture from surface" << std::endl;
	}

	//free surface
	SDL_FreeSurface(image);


	return texture;
}


bool initialise()
{
	//initialise all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialise SDL. SDL error: " << SDL_GetError() << std::endl;
		return true;
	}
	
	

	//create a window with specified name, anywhere on screen, 800x600 pixel size and no SDL_windowflags.	

	//flag testing 
	int iwindowflag = SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_FULLSCREEN_DESKTOP;
	g_sdlWindow = SDL_CreateWindow("TANK GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, NULL);

	//error checking
	if (g_sdlWindow == nullptr)
	{
		std::cout << "Failed to create window. SDL error: " << SDL_GetError() << std::endl;
		return true;
	}

	//Create a rendering context for our window. Enable Hardware acceleration with the SLD_RENDERER_ACCELERATED FLAG

	g_sdlRenderer = SDL_CreateRenderer(g_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	if (g_sdlRenderer == nullptr)
	{
		std::cout << "Failed to create renderer. SDL error: " << SDL_GetError() << std::endl;
		return true;

	}


	//store a bitmask for which file types we want to initialise
	//int flags = IMG_INIT_JPG | IMG_INIT_PNG
	int flags = IMG_INIT_PNG;
	//initialise SDL_Image with provided flags 
	int initted = IMG_Init(flags);

	//error checking - if the returned bitmask of initialised flags doesn't match the flags we provided then
	// we can assume there was an error for one or more file types 

	if (initted != flags)
	{
		std::cout << "Failed to initialise SDL_IMAGE. SDL ERROR: " << IMG_GetError() << std::endl;
		return true;
	}
	//store a bitmask for which file types we want to initialise 

	flags = MIX_INIT_MP3;
	initted = Mix_Init(flags);
	if (initted != flags)
	{
		std::cout << "Failed to initialise SDL_micer. SDL_mixer error: " << Mix_GetError() << std::endl;
		return true;
	}
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0)
	{
		std::cout << "Failed to open audio device. SDL MIXER ERROR: " << Mix_GetError() << std::endl;
		return true; 
	}
	
	
	

	//initialing and loading font
	if (TTF_Init() < 0)
	{
		std::cout << "Failed to initialise TTF. SDL_ERROR: " << TTF_GetError() << std::endl;
		return true;
	}
	g_font = TTF_OpenFont("Assets/8bitOperatorPlus8-Regular.ttf", 32);
	if (g_font == nullptr)
	{
		std::cout << "TTF failed to load font. SDL ERROR: " << TTF_GetError() << std::endl;
		return true;
	}

	
	

	


	return false;



}

void cleanup()
{
	SDL_DestroyRenderer(g_sdlRenderer);
	SDL_DestroyWindow(g_sdlWindow);
	IMG_Quit();
	Mix_CloseAudio();
	TTF_CloseFont(g_font);
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();

}





int main(int argc, char* argv[])
{

	
	if (initialise())
	{
		std::cout << "Application failed to initialise. Quitting... " << std::endl; 
		return -1; 
	}
	
	Input_Manager::Init();
	
	
	
	SDL_Surface* textSurface = TTF_RenderText_Blended(g_font, "TANK GAME", { 255,255,255,255 });
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g_sdlRenderer, textSurface);
	if (textTexture == nullptr)
	{
		std::cout << "TTF failed to create text texture. SDL ERROR: " << TTF_GetError() << std::endl;
	}
	SDL_FreeSurface(textSurface);
	

	///loading background SDL_Texture* Background = LoadTexture();
	

	SDL_Texture* TankTexture = LoadTexture("Assets/PNG/Tanks/tankGreen.png");
	SDL_Texture* BarrelTexture = LoadTexture("Assets/PNG/Tanks/barrelGreen.png");

	SDL_Texture* EnemyTankTexture = LoadTexture("Assets/PNG/Tanks/tankRed.png");
	SDL_Texture* enemyBarrelTexture = LoadTexture("Assets/PNG/Tanks/barrelRed.png");

	SDL_Texture* BulletTexture = LoadTexture("Assets/PNG/Bullets/bulletYellow.png");

	SDL_Texture* sonicTexture = LoadTexture("Assets/sonic.png"); 
	GameObject sonic (sonicTexture);
	//sonic.m_x = 30;
	//sonic.m_y = 30;
	sonic.isAnimated = true;
	sonic.animationSpeed = 5;
	sonic.animPixelWidth = 48;
	sonic.animPixelHeight = 48;
	sonic.animState = 1;
	sonic.animFrames = 7;


	

	
	



	////load wall texture for wall obstacles 

	/*int tankWidth = 40;
	int tankHeight = 35;

	int barrelWidth = 8;
	int barrelHeight = 25;

	int TankX = 200;
	int TankY = 200;*/
	SDL_Texture* explosion = LoadTexture("Assets/explosion.png");
	SDL_Texture* Trees = LoadTexture("Assets/tree_12.png");

	Tank PlayerTank(TankTexture,BarrelTexture, explosion, Player, "Player");
	
	

	//PlayerTank.SetPlayerPosition(300, 300);
	//PlayerTank.SetColliderPos(PlayerTank.Pos.x, PlayerTank.Pos.y);  ////testing setting in main 

	EnemyTankSpawner* enemyTanks = new EnemyTankSpawner(EnemyTankTexture, enemyBarrelTexture, explosion);

	enemyTanks->SpawnTank(3);
	
	Obstacle* Obstacles = new Obstacle(Trees);

	Obstacles->SpawnObstacles(10, *enemyTanks);
	
	
	Tank* firstTank = enemyTanks->getTankByIndex(0);
	Tank* secondTank = enemyTanks->getTankByIndex(1);
	Tank* thirdTank = enemyTanks->getTankByIndex(2);
	//firstTank->SetColliderPos(firstTank->m_x, firstTank->m_y);
	
	//if (Collision::CircleCollision(2, 3, 1, 3, 2, 0.5f))   //testing circle collision 
	//{
	//	std::cout << "overlap detected" << std::endl; 
	//}

	
	
	/*GameObject OBJexplosion(explosion);
	OBJexplosion.isAnimated = true; 
	OBJexplosion.animationSpeed = 5;
	OBJexplosion.animPixelWidth = 48;
	OBJexplosion.animPixelHeight = 48;
	OBJexplosion.animState = 0;
	OBJexplosion.animFrames = 7;*/

	
	//SDL_Texture* penguinTexture = LoadTexture("Assets/door.png");
	



//load sound effect file
	Mix_Chunk* coinsSFX = Mix_LoadWAV("Assets/Coin01.wav");

	Mix_Music* music = Mix_LoadMUS("Assets/battle-mus.mp3");
	//play the music with infinte looping
	Mix_PlayMusic(music, -1);


	//SDL_Texture* MagicTexture = SDL_CreateTexture(g_sdlRenderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_TARGET, 64, 64); //creating own texture 

	//SDL_SetRenderTarget(g_sdlRenderer, MagicTexture); //MAGIC TEXTURE COULD BE USEFUL AS LANDMINES  

	//SDL_SetRenderDrawColor(g_sdlRenderer, 0, 255, 0, 0);
	SDL_Rect BoxDST = { 16,16,32,32 };
	SDL_RenderFillRect(g_sdlRenderer, &BoxDST); //renders texture to the display 

	SDL_SetRenderTarget(g_sdlRenderer, NULL);

	bool keepRunning = true;

	int MagicX = 80, MagicY = 80;
	int MagicWidth, MagicHeight;

	//SDL_QueryTexture(MagicTexture, NULL, NULL, &MagicWidth, &MagicHeight);

	

	std::cout << "Player box collider at: " << PlayerTank.boxCollider.x << " , " << PlayerTank.boxCollider.y << std::endl; 
	std::cout << "Enemy Box Collider is at: " << firstTank->boxCollider.x << " , " << firstTank->boxCollider.y << std::endl; 
	
	int MouseX = 0;
	int MouseY = 0;
	Game.StartTimer();
	
	while (keepRunning)
	{
		TimeMaths& TimeMathInstance = TimeMaths::getInstance();
		float deltaTime = TimeMathInstance.getDeltaTime();
		
		
		SDL_Event sdlEvent;   //logs event queue  
		Input_Manager::UpdateKeyStates();
		int prevPlayerX = PlayerTank.GetXValue();
		int prevPlayerY = PlayerTank.GetYValue();

		while (SDL_PollEvent(&sdlEvent))
		{
			for (auto& Tank : enemyTanks->spawnedTanks)
			{
				if (Collision::SquareCollision(PlayerTank.boxCollider, Tank->boxCollider))
				{
					std::cout << PlayerTank.boxCollider.x << " , " << PlayerTank.boxCollider.y << std::endl;
					std::cout << firstTank->boxCollider.x << " , " << firstTank->boxCollider.y << std::endl;
					PlayerTank.SetPlayerPosition(prevPlayerX, prevPlayerY);
					PlayerTank.TakeDamage(1);
				}
			}
			
			//if (Collision::SquareCollision(PlayerTank.boxCollider, firstTank->boxCollider))
			//{
			//	std::cout << "Clash With First Tank" << std::endl;
			//	std::cout << PlayerTank.boxCollider.x << " , " << PlayerTank.boxCollider.y << std::endl;
			//	std::cout << firstTank->boxCollider.x << " , " << firstTank->boxCollider.y << std::endl;
			//	PlayerTank.SetPlayerPosition(prevPlayerX, prevPlayerY);
			//	PlayerTank.TakeDamage(1);

			//}
			//else if(Collision::SquareCollision(PlayerTank.boxCollider, secondTank->boxCollider))
			//{
			//	std::cout << "Clash With Second Tank" << std::endl;
			//	PlayerTank.SetPlayerPosition(prevPlayerX, prevPlayerY);
			//	PlayerTank.TakeDamage(1);

			//}
			//else if (Collision::SquareCollision(PlayerTank.boxCollider, thirdTank->boxCollider))
			//{
			//	std::cout << "Clash With Third Tank" << std::endl;
			//	PlayerTank.SetPlayerPosition(prevPlayerX, prevPlayerY);
			//	PlayerTank.TakeDamage(1); 
			//}
			//else
			//{
			//	//std::cout << "No Clash" << std::endl; 
			//}

			

			switch (sdlEvent.type)
			{
				
			case SDL_QUIT:
				keepRunning = false;
				break;
			case SDL_KEYDOWN:
				if (Input_Manager::GetKeyDown(SDL_SCANCODE_ESCAPE))
				{
					std::cout << "Escape Pressed" << std::endl; 
					keepRunning = false;
				}
				else if (Input_Manager::GetKey(SDL_SCANCODE_A) || Input_Manager::GetKey(SDL_SCANCODE_LEFT))
				{
					PlayerTank.MoveLeft(deltaTime);	
					
				}
				else if (Input_Manager::GetKey(SDL_SCANCODE_D) || Input_Manager::GetKey(SDL_SCANCODE_RIGHT))
				{
					
					PlayerTank.MoveRight(deltaTime);
					//sonic.m_x++;
					if (sonic.animState != 9)
					{
						
						sonic.animState = 9;
						sonic.animFrames = 4;
						sonic.animPixelHeight = 64;
						sonic.animPixelWidth = 64;
						sonic.animationSpeed = 20;

					}
					
				}
				else if (Input_Manager::GetKey(SDL_SCANCODE_W) || Input_Manager::GetKey(SDL_SCANCODE_UP))
				{
					
					PlayerTank.MoveUp(deltaTime);
					PlayerTank.rotation += 1;
					
					
				}
				else if (Input_Manager::GetKey(SDL_SCANCODE_S) || Input_Manager::GetKey(SDL_SCANCODE_DOWN))
				{
					
					PlayerTank.MoveDown(deltaTime);
					PlayerTank.rotation -= 1; 
					
					//firstTank->MoveRight(deltaTime);
				}
				else if (Input_Manager::GetKey(SDL_SCANCODE_SPACE))
				{
					Mix_PlayChannel(-1, coinsSFX, 0);
					//Game.NewLevel();
					
					
					 
					
					////tank shoot going here 
					//OBJexplosion.isAnimated = true;
					//PlayerTank.isAnimated = true;
					//PlayerTank.m_w = OBJexplosion.animPixelWidth;
					//PlayerTank.m_h = OBJexplosion.animPixelHeight; 
					//PlayerTank.changeTexture(TankTexture, explosion);
					//TimeMathInstance.setTimeScale(0.5f);   //changes time scale (useful for slow mo effects) 
					
				}
				

				break;
			case SDL_MOUSEBUTTONUP:
				if (sdlEvent.button.button == SDL_BUTTON_LEFT)
				{
					PlayerTank.Fire(BulletTexture);
				}
				break;
			case SDL_MOUSEMOTION:
				//std::cout << "Current Mouse Position is: " << sdlEvent.motion.x << " , " << sdlEvent.motion.y << std::endl;

				SDL_GetMouseState(&MouseX, &MouseY);
				MagicX = sdlEvent.motion.x; //locks magicx to mousex position
				MagicY = sdlEvent.motion.y; //locks magicy to mousey position
				
				
				break;


			default:
				break;
			}
		}

		std::string levelText = "LEVEL:" + std::to_string(Game.GetLevel());
		SDL_Surface* LevelSurface = TTF_RenderText_Blended(g_font, levelText.c_str(), { 255,255,255,255 });
		SDL_Texture* LevelTexture = SDL_CreateTextureFromSurface(g_sdlRenderer, LevelSurface);
		SDL_FreeSurface(LevelSurface);
		
		Level::CheckPlayerBounds(&PlayerTank);
		g_cameraX = PlayerTank.Pos.x * 0.04;
		g_cameraY = PlayerTank.Pos.y * 0.04;

		//PlayerTank.BarrelAngle = MouseX; 

		//SDL_SetRenderDrawColor(g_sdlRenderer, 19, 47, 209, 255);   ////sets background colour 
		SDL_RenderClear(g_sdlRenderer);

		
		PlayerTank.Draw(g_sdlRenderer, g_cameraX, g_cameraY, MouseX, MouseY, true, deltaTime);
		PlayerTank.coolDown -= deltaTime; 
		firstTank->coolDown -= deltaTime;
		secondTank->coolDown -= deltaTime;
		thirdTank->coolDown -= deltaTime; 
		
		for (int i = 0; i < enemyTanks->spawnedTanks.size(); i++)
		{
			Tank* enemyTank = enemyTanks->spawnedTanks[i];
			
			if (enemyTank->HasLineOfSight(PlayerTank, *enemyTank, Obstacles->SpawnedObstacles))
			{
				//std::cout << "Tank" << i << " has line of sight" << std::endl;
				enemyTank->RotateEnemyBarrelToPlayer(PlayerTank); 
				
				if (enemyTank->coolDown <= 0 && !enemyTank->hasFired)
				{
					enemyTank->Fire(BulletTexture); 
					/*for (auto bulletIter = enemyTank->bullets.begin(); bulletIter != enemyTank->bullets.end();)
					{
						Bullet* bullet = *bulletIter;
						bullet->Draw(g_sdlRenderer, g_cameraX, g_cameraY, PlayerTank.GetXValue(), PlayerTank.GetYValue(), false, deltaTime);
					
						bool bulletHitTank = false;
						if (Game.CheckBulletBounds(bullet))
						{
							enemyTank->BulletsToDestroy.push_back(bullet);
							bulletIter = enemyTank->bullets.erase(bulletIter);
							if (bulletIter == enemyTank->bullets.end())
							{
								break;
							}

						}
					}*/
				}
				else
				{
					//std::cout << "Tank in Cooldown/JustFired" << std::endl; 
				}
				
			}
			else
			{
				std::cout << "Tank" << i << " Has No line of sight" << std::endl; 
			}
		}
		for (auto& enemyTank : enemyTanks->spawnedTanks)
		{
			for (auto bulletIter = enemyTank->bullets.begin(); bulletIter != enemyTank->bullets.end();)
			{
				Bullet* bullet = *bulletIter; 
				if (bullet != nullptr)
				{
					bullet->Draw(g_sdlRenderer, g_cameraX, g_cameraY, PlayerTank.GetXValue(), PlayerTank.GetYValue(), false, deltaTime);
					bool bulletHitTank = false;
					if (Game.CheckBulletBounds(bullet))
					{
						enemyTank->BulletsToDestroy.push_back(bullet);
						bulletIter = enemyTank->bullets.erase(bulletIter);
						if (bulletIter == enemyTank->bullets.end())
						{
							break;
						}
					}
					else
					{
						++bulletIter;
					}
				}
				else
				{
					++bulletIter; 
				}
				
			}
		}
	
		for (auto bulletIter = PlayerTank.bullets.begin(); bulletIter != PlayerTank.bullets.end();)
		{
			Bullet* bullet = *bulletIter;
			bullet->Draw(g_sdlRenderer, g_cameraX, g_cameraY, MouseX, MouseY, false, deltaTime);

			bool bulletHitTank = false; 
		   if (Game.CheckBulletBounds(bullet))
			{
				PlayerTank.BulletsToDestroy.push_back(bullet);
				bulletIter = PlayerTank.bullets.erase(bulletIter);
				if (bulletIter == PlayerTank.bullets.end())
				{
					break;
				}
				 
		   }
		   else
		   {
			   for (Tank* enemyTank : enemyTanks->spawnedTanks)
			   {
				   if (Collision::SquareCollision(bullet->boxCollider, enemyTank->boxCollider))
				   {
					   enemyTank->TakeDamage(1);
					   std::cout << "Enemy Damaged." << std::endl; 
					   PlayerTank.BulletsToDestroy.push_back(bullet);
					   bulletIter = PlayerTank.bullets.erase(bulletIter);
					   std::cout << "This Tank Health now at: " << enemyTank->Health << std::endl; 
					   
					   bulletHitTank = true;
					   break;
				   }
			   }
			   if (!bulletHitTank)
			   {
				   ++bulletIter;
			   }
		   }
			
		   
		   
		   /*else if (Collision::SquareCollision(bullet->boxCollider, firstTank->boxCollider))
			{
				std::cout << "Bullet Hit first tank. Damage Dealt" << std::endl;
				firstTank->TakeDamage(1);
				PlayerTank.BulletsToDestroy.push_back(bullet);
				bulletIter = PlayerTank.bullets.erase(bulletIter); 
				std::cout << "First Tank Health is now: " << firstTank->Health << std::endl; 
				if (firstTank->GetTankState() == Dead)
				{
					std::cout << "Tank Destroyed!" << std::endl;
					
					++Game.score;
				}
			}
			else
			{
				++bulletIter;
			}*/
		}
		PlayerTank.DestroyBullets();
		firstTank->DestroyBullets();
		secondTank->DestroyBullets();
		thirdTank->DestroyBullets(); 
		//enemyTanks->DestroyKilledTanks();

		
		//for (auto* bullet : PlayerTank.bullets)
		//{
		//	bullet->Draw(g_sdlRenderer, g_cameraX, g_cameraY, MouseX, MouseY, false, deltaTime);
		//	
		//}
		//for (auto* bullet : PlayerTank.bullets)
		//{
		//	if (Game.CheckBulletBounds(bullet))
		//	{
		//		PlayerTank.bullets.remove(bullet);                           ////////working on this. trying to delete bullets which have left view 
		//		PlayerTank.BulletsToDestroy.push_back(bullet);
		//		
		//	}
		//}
		//PlayerTank.DestroyBullets();
		
		enemyTanks->DrawTanks(g_sdlRenderer, g_cameraX, g_cameraY,MouseX,MouseY,false, deltaTime);
		//sonic.Draw(g_sdlRenderer, g_cameraX, g_cameraY);
		//sonic.timeInAnimationState = SDL_GetTicks() / 1000.0f;
		Obstacles->DrawObstacles(g_sdlRenderer, g_cameraX, g_cameraY, MouseX, MouseY,false, deltaTime);
		

		//create destination for where the image will be copied{x,y,w,h} 
		SDL_Rect destinationRect{ 25,25,16,16 };
		SDL_Rect destinationRect2{ 50,50,20,20 };
		SDL_Rect destinationRect3{ MagicX - 10, MagicY - 10,20,20 }; //centres mouse to middle of texture with the -10's 
		SDL_Rect fontDestRect{ 200,25,300,32 };
		SDL_Rect ScoreDest{ 20,500,150,50 };
		SDL_Rect backgroundRect{ 1000,800,32,32 };
		
		//SDL_RenderCopy(g_sdlRenderer, penguinTexture, NULL, &destinationRect2);
		
		SDL_RenderCopy(g_sdlRenderer, textTexture, NULL, &fontDestRect);
		SDL_RenderCopy(g_sdlRenderer, LevelTexture, NULL, &ScoreDest);
		Game.RenderTimer(deltaTime, g_font, g_sdlRenderer);



		//update the screen with the state of the render target
		SDL_RenderPresent(g_sdlRenderer);
		SDL_Delay(16);

	}
	//SDL_FreeSurface(image);
	//SDL_FreeSurface(image2);
	

	
	

	

	
	SDL_DestroyTexture(TankTexture);
	SDL_DestroyTexture(BarrelTexture);
	//SDL_DestroyTexture(penguinTexture);
	SDL_DestroyTexture(BulletTexture); 
	Mix_FreeChunk(coinsSFX);
	Mix_FreeMusic(music);
	delete(enemyTanks);
	delete(Obstacles); 
	
	
	cleanup();

	return 0;
}