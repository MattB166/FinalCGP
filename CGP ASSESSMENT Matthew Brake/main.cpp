#include <iostream>
#include <fstream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Tank.h"
#include "EnemyTankSpawner.h"
#include "Collision.h"
#include "Collider.h"
#include "BoxCollider.h"




SDL_Window* g_sdlWindow;
SDL_Renderer* g_sdlRenderer;
const Uint8* keystate;
TTF_Font* g_font; 

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
	

	
	
	
	SDL_Surface* textSurface = TTF_RenderText_Blended(g_font, "Hello World", { 255,255,255,255 });
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g_sdlRenderer, textSurface);
	if (textTexture == nullptr)
	{
		std::cout << "TTF failed to create text texture. SDL ERROR: " << TTF_GetError() << std::endl;
	}
	SDL_FreeSurface(textSurface);

	////load door as a surface
	//SDL_Surface* image = SDL_LoadBMP("Assets/door.bmp");
	//////error checking
	//if (image == nullptr)
	//{
	//	std::cout << "Failed to load image" << SDL_GetError();
	//}

	

	SDL_Texture* TankTexture = LoadTexture("Assets/PNG/Tanks/tankGreen.png");
	SDL_Texture* BarrelTexture = LoadTexture("Assets/PNG/Tanks/barrelGreen.png");

	SDL_Texture* EnemyTankTexture = LoadTexture("Assets/PNG/Tanks/tankRed.png");
	SDL_Texture* enemyBarrelTexture = LoadTexture("Assets/PNG/Tanks/barrelRed.png");

	int tankWidth = 40;
	int tankHeight = 35;

	int barrelWidth = 8;
	int barrelHeight = 25;

	int TankX = 200;
	int TankY = 200;

	//Tank MyTank(g_sdlRenderer, TankTexture, TankX, TankY);

	Tank PlayerTank(TankTexture,BarrelTexture);
	

	/*TankSpawner enemytanks(TankTexture, BarrelTexture);

	enemytanks.SpawnTank(4);*/

	EnemyTankSpawner* enemyTanks = new EnemyTankSpawner(EnemyTankTexture, enemyBarrelTexture);

	enemyTanks->SpawnTank(3);
	
	
	
	
	
	
	//if (Collision::CircleCollision(2, 3, 1, 3, 2, 0.5f))   //testing circle collision 
	//{
	//	std::cout << "overlap detected" << std::endl; 
	//}

	if (Collision::SquareCollision(PlayerTank.boxCollider, enemyTanks->enemyCollider))
	{
		std::cout << "Clash" << std::endl; 
		std::cout << PlayerTank.boxCollider.x << " , " << PlayerTank.boxCollider.y << std::endl; 
		std::cout << enemyTanks->enemyCollider.x << " , " << enemyTanks->enemyCollider.y << std::endl; 
	}
	else
	{
		std::cout << "No Clash" << std::endl; 
	}



	/*SDL_Surface* image2 = SDL_LoadBMP("Assets/dig10k_penguin.bmp");
	if (image2 == nullptr)
	{
		std::cout << "Failed to load image" << SDL_GetError();
	}*/

	SDL_Texture* penguinTexture = LoadTexture("Assets/door.png");
	//SDL_Texture* penguinTexture = LoadTexture("Assets/dig10k_penguin.bmp");


	//SDL_Texture* texture = SDL_CreateTextureFromSurface(g_sdlRenderer, image);
	////error checking
	//if (texture == nullptr)
	//{
	//	std::cout << "Failed to create texture from surface. SDL ERROR: " << SDL_GetError() << std::endl;
	//}

	/*SDL_Texture* texture2 = SDL_CreateTextureFromSurface(g_sdlRenderer, image2);
	if (texture2 == nullptr)
	{
		std::cout << "Failed to create texture from surface. SDL ERROR: " << SDL_GetError() << std::endl;
	}
*/

//load sound effect file
	Mix_Chunk* coinsSFX = Mix_LoadWAV("Assets/Coin01.wav");

	Mix_Music* music = Mix_LoadMUS("Assets/rng_lo-fi_loop.mp3");
	//play the music with infinte looping
	Mix_PlayMusic(music, -1);


	SDL_Texture* MagicTexture = SDL_CreateTexture(g_sdlRenderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_TARGET, 64, 64); //creating own texture 

	SDL_SetRenderTarget(g_sdlRenderer, MagicTexture); //MAGIC TEXTURE COULD BE USEFUL AS LANDMINES  

	SDL_SetRenderDrawColor(g_sdlRenderer, 0, 255, 0, 255);
	SDL_Rect BoxDST = { 16,16,32,32 };
	SDL_RenderFillRect(g_sdlRenderer, &BoxDST); //renders texture to the display 

	SDL_SetRenderTarget(g_sdlRenderer, NULL);

	bool keepRunning = true;

	int MagicX = 80, MagicY = 80;
	int MagicWidth, MagicHeight;

	//SDL_QueryTexture(MagicTexture, NULL, NULL, &MagicWidth, &MagicHeight);



	Uint32 previousFrameTicks = SDL_GetTicks();

	while (keepRunning)
	{
		float deltaTime = (SDL_GetTicks() - (float)(previousFrameTicks)) / 1000;
		previousFrameTicks = SDL_GetTicks();
		SDL_Event sdlEvent;   //logs event queue  
		while (SDL_PollEvent(&sdlEvent))
		{
			/*keystate = SDL_GetKeyboardState(NULL);
			* if(keystate[SDL_SCANCODE_RIGHT])
			* ++MagicX
			*
			if(keystate)*///start of keystate function 
			
			

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
					//--MagicX;
					//--TankX;
					PlayerTank.MoveLeft();
					/*MyTank.MoveLeft();
					MyTank.Render();*/
					//std::cout << " X value of Tank is: " << PlayerTank.GetXValue() << std::endl;
				}
				else if (sdlEvent.key.keysym.sym == SDLK_d || sdlEvent.key.keysym.sym == SDLK_RIGHT)
				{
					//++MagicX;
					//++TankX;
					//PlayerTank.MoveRight();
					PlayerTank.m_x += 200 * deltaTime; ///need this inside game logic to then call above function 
					//std::cout << " X value of Tank is: " << PlayerTank.GetXValue() << std::endl;
				}
				else if (sdlEvent.key.keysym.sym == SDLK_w || sdlEvent.key.keysym.sym == SDLK_UP)
				{
					//--MagicY;
					//--TankY;
					PlayerTank.MoveUp();
					//std::cout << "Y Value of Tank is: " << PlayerTank.GetYValue() << std::endl;
				}
				else if (sdlEvent.key.keysym.sym == SDLK_s || sdlEvent.key.keysym.sym == SDLK_DOWN)
				{
					//++MagicY;
					//++TankY;
					PlayerTank.MoveDown();
					//std::cout << "Y Value of Tank is: " << PlayerTank.GetYValue() << std::endl;
				}
				else if (sdlEvent.key.keysym.sym == SDLK_SPACE)
				{
					Mix_PlayChannel(-1, coinsSFX, 0);
					////tank shoot going here 
					PlayerTank.changeTexture(TankTexture, MagicTexture);
				}
				

				break;
			case SDL_KEYUP:
				if (sdlEvent.key.keysym.sym == SDLK_w || sdlEvent.key.keysym.sym == SDLK_UP)
				{
					std::cout << "Up pressed" << std::endl;
				}


				break;
			case SDL_MOUSEBUTTONUP:
				if (sdlEvent.button.button == SDL_BUTTON_LEFT)
				{
					std::cout << "Button Click" << std::endl;
					int x;
					int y;
					SDL_GetMouseState(&x, &y);
					std::cout << "X value is: " << x << "," << " Y Value is: " << y << std::endl;
				}
				break;
			case SDL_MOUSEMOTION:
				std::cout << "Current Mouse Position is: " << sdlEvent.motion.x << " , " << sdlEvent.motion.y << std::endl;

				MagicX = sdlEvent.motion.x; //locks magicx to mousex position
				MagicY = sdlEvent.motion.y; //locks magicy to mousey position
				break;


			default:
				break;
			}
		}

		SDL_SetRenderDrawColor(g_sdlRenderer, 19, 47, 209, 255);   ////sets background colour 
		SDL_RenderClear(g_sdlRenderer);


		PlayerTank.Draw(g_sdlRenderer);
		enemyTanks->DrawTanks(g_sdlRenderer);

		//create destination for where the image will be copied{x,y,w,h} 
		SDL_Rect destinationRect{ 25,25,16,16 };
		SDL_Rect destinationRect2{ 50,50,20,20 };
		SDL_Rect destinationRect3{ MagicX - 10, MagicY - 10,20,20 }; //centres mouse to middle of texture with the -10's 
		SDL_Rect fontDestRect{ 25,100,300,32 };
		//SDL_Rect TankRect{ TankX,TankY,tankWidth,tankHeight }; 
		//int barrelX = TankRect.x + (TankRect.w - barrelWidth) / 2;
		//int barrelY = TankRect.y + TankRect.h / 2; //locking bottom of barrel to centre of tank 
		//SDL_Rect barrelRect{ barrelX,barrelY,barrelWidth,barrelHeight };

		//copy texture onto rendering target at specified locations 
		//SDL_RenderCopy(g_sdlRenderer, TankTexture, NULL, &TankRect);
		//SDL_RenderCopy(g_sdlRenderer, BarrelTexture, NULL, &barrelRect);
		SDL_RenderCopy(g_sdlRenderer, penguinTexture, NULL, &destinationRect2);
		SDL_RenderCopy(g_sdlRenderer, MagicTexture, NULL, &destinationRect3);
		SDL_RenderCopy(g_sdlRenderer, textTexture, NULL, &fontDestRect);



		//update the screen with the state of the render target
		SDL_RenderPresent(g_sdlRenderer);
		SDL_Delay(16);

	}
	//SDL_FreeSurface(image);
	//SDL_FreeSurface(image2);
	

	
	

	

	//clean up
	SDL_DestroyTexture(TankTexture);
	SDL_DestroyTexture(BarrelTexture);
	SDL_DestroyTexture(penguinTexture);
	Mix_FreeChunk(coinsSFX);
	Mix_FreeMusic(music);
	delete(enemyTanks);
	
	cleanup();

	return 0;
}