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
	float MoveUp(float deltaTime);
	float MoveDown(float deltaTime);
	float MoveLeft(float deltaTime);
	float MoveRight(float deltaTime);
	float GetXValue()const;
	float GetYValue()const;
	void Draw(SDL_Renderer* renderer) override;
	void changeTexture(SDL_Texture* baseTexture, SDL_Texture* newTexture);
	void SetPosition(int x, int y);
	
	
private:
	
	//BoxCollider enemyCollider; 
	SDL_Texture* m_barrelTexture; 
	Controller TankType;
	int tankID;
	float m_speed = 15; 
	

	

	/*int X;
	int Y;
	int tankWidth = 40;
	int tankHeight = 35;*/
};

