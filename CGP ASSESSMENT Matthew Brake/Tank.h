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
	int MoveUp(float deltaTime);
	int MoveDown(float deltaTime);
	int MoveLeft(float deltaTime);
	int MoveRight(float deltaTime);
	int GetXValue()const;
	int GetYValue()const;
	void Draw(SDL_Renderer* renderer) override;
	void changeTexture(SDL_Texture* baseTexture, SDL_Texture* newTexture);
	void SetPosition(int x, int y);
	
	
private:
	
	//BoxCollider enemyCollider; 
	SDL_Texture* m_barrelTexture; 
	Controller TankType;
	int tankID;
	float m_speed = 13; 
	

	

	/*int X;
	int Y;
	int tankWidth = 40;
	int tankHeight = 35;*/
};

