#include "GameManager.h"

GameManager::GameManager(SDL_Renderer* renderer, TTF_Font* font)
{
	g_sdlRenderer = renderer;
	g_font = font;
	TankTexture = nullptr;
	BarrelTexture = nullptr;
	enemyBarrelTexture = nullptr;
	EnemyTankTexture = nullptr;
	BulletTexture = nullptr;
	coinsSFX = nullptr;
	music = nullptr; 
	enemyTanks = nullptr; 
}

GameManager::~GameManager()
{
}

void GameManager::HandleInput(SDL_Event& sdlEvent)
{
    InputManager.HandleInput(sdlEvent, *this);
}

bool GameManager::Initialise()
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

void GameManager::LoadAssets()
{
	SDL_Surface* textSurface = TTF_RenderText_Blended(g_font, "TANK GAME", { 255,255,255,255 });
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g_sdlRenderer, textSurface);
	if (textTexture == nullptr)
	{
		std::cout << "TTF failed to create text texture. SDL ERROR: " << TTF_GetError() << std::endl;
	}
	SDL_FreeSurface(textSurface);

    TankTexture = LoadTexture("Assets/PNG/Tanks/tankGreen.png");
	BarrelTexture = LoadTexture("Assets/PNG/Tanks/barrelGreen.png");

   EnemyTankTexture = LoadTexture("Assets/PNG/Tanks/tankRed.png");
   enemyBarrelTexture = LoadTexture("Assets/PNG/Tanks/barrelRed.png");

   BulletTexture = LoadTexture("Assets/PNG/Bullets/bulletGreen.png");

   coinsSFX = Mix_LoadWAV("Assets/Coin01.wav");

	 music = Mix_LoadMUS("Assets/battle-mus.mp3");
	//play the music with infinte looping
	Mix_PlayMusic(music, -1);

	Tank PlayerTank(TankTexture, BarrelTexture, Player, "Player");

	enemyTanks = new EnemyTankSpawner(EnemyTankTexture, enemyBarrelTexture);
	enemyTanks->SpawnTank(3);




	Tank* firstTank = enemyTanks->getTankByIndex(0);
	Tank* secondTank = enemyTanks->getTankByIndex(1);
	Tank* thirdTank = enemyTanks->getTankByIndex(2);
}

void GameManager::Render()
{
	SDL_SetRenderTarget(g_sdlRenderer, NULL);
	SDL_RenderClear(g_sdlRenderer);
	
	PlayerTank.Draw(g_sdlRenderer, g_cameraX, g_cameraY, MouseX, MouseY, true, deltaTime);
	for (auto bulletIter = PlayerTank.bullets.begin(); bulletIter != PlayerTank.bullets.end();)
	{
		Bullet* bullet = *bulletIter;
		bullet->Draw(g_sdlRenderer, g_cameraX, g_cameraY, MouseX, MouseY, false, deltaTime);

	}

    enemyTanks->DrawTanks(g_sdlRenderer, g_cameraX, g_cameraY, MouseX, MouseY, false, deltaTime);
	SDL_RenderPresent(g_sdlRenderer);
	SDL_Delay(16);
}

void GameManager::Cleanup()
{
	SDL_DestroyTexture(TankTexture);
	SDL_DestroyTexture(BarrelTexture);
	SDL_DestroyTexture(BulletTexture);
	Mix_FreeChunk(coinsSFX);
	Mix_FreeMusic(music);
	delete(enemyTanks);
	
	
	SDL_DestroyRenderer(g_sdlRenderer);
	SDL_DestroyWindow(g_sdlWindow);
	IMG_Quit();
	Mix_CloseAudio();
	TTF_CloseFont(g_font);
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

void GameManager::RunGame()
{
	keeprunning = true;
	TimeMaths& TimeMathInstance = TimeMaths::getInstance();
    deltaTime = TimeMathInstance.getDeltaTime();
}

Tank& GameManager::GetPlayerTank()
{
    return PlayerTank;
}



SDL_Texture* GameManager::LoadTexture(const char* filename)
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
