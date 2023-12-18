#include "Input_Manager.h"
#include "GameManager.h"


void Input_Manager::HandleInput(SDL_Event& sdlEvent, GameManager& gameManager)
{
	bool& keepRunning = gameManager.keeprunning; 
	Tank& PlayerTank = gameManager.GetPlayerTank();
	float& deltaTime = gameManager.deltaTime;
	Mix_Chunk* coinsSFX = gameManager.coinsSFX;
	SDL_Texture* BulletTexture = gameManager.BulletTexture; 
	
	while (keepRunning)
	{


		while (SDL_PollEvent(&sdlEvent))
		{
			switch (sdlEvent.type)
			{
			case SDL_QUIT:
				keepRunning = false;
				break;
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
				{
					keepRunning = false;
				}
				else if (sdlEvent.key.keysym.sym == SDLK_a || sdlEvent.key.keysym.sym == SDLK_LEFT)
				{
					//std::cout << PlayerTank.Pos.x; 



					PlayerTank.MoveLeft(deltaTime);



				}
				else if (sdlEvent.key.keysym.sym == SDLK_d || sdlEvent.key.keysym.sym == SDLK_RIGHT)
				{

					PlayerTank.MoveRight(deltaTime);
					//sonic.m_x++;


				}
				else if (sdlEvent.key.keysym.sym == SDLK_w || sdlEvent.key.keysym.sym == SDLK_UP)
				{

					PlayerTank.MoveUp(deltaTime);
					PlayerTank.rotation += 1;


				}
				else if (sdlEvent.key.keysym.sym == SDLK_s || sdlEvent.key.keysym.sym == SDLK_DOWN)
				{

					PlayerTank.MoveDown(deltaTime);
					PlayerTank.rotation -= 1;

					//firstTank->MoveRight(deltaTime);
				}
				else if (sdlEvent.key.keysym.sym == SDLK_SPACE)
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
				std::cout << "Current Mouse Position is: " << sdlEvent.motion.x << " , " << sdlEvent.motion.y << std::endl;

				//SDL_GetMouseState(&MouseX, &MouseY);
				//MagicX = sdlEvent.motion.x; //locks magicx to mousex position
				//MagicY = sdlEvent.motion.y; //locks magicy to mousey position


				break;


			default:
				break;
			}
		}
	}
}
