#pragma once
#include "GameObject.h"

enum Controller
{
	Player, Enemy
};

class Tank : public GameObject
{
public:
	Tank();
	Tank(SDL_Texture* baseTexture, SDL_Texture* barrelTexture);
	int MoveUp();
	int MoveDown();
	int MoveLeft();
	int MoveRight();
	int GetXValue()const;
	int GetYValue()const;
	void Draw(SDL_Renderer* renderer) override;
	void changeTexture(SDL_Texture* baseTexture, SDL_Texture* newTexture);
	void SetPosition(int x, int y);
	
	
private:
	
	SDL_Texture* m_barrelTexture; 
	Controller TankType;
	int tankID;
	

	

	/*int X;
	int Y;
	int tankWidth = 40;
	int tankHeight = 35;*/
};

