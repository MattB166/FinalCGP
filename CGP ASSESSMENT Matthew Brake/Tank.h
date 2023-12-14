#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include <list>

enum Controller
{
	Player, Enemy
};

class Tank : public GameObject
{
public:
	Tank();
	~Tank();
	Tank(SDL_Texture* baseTexture, SDL_Texture* barrelTexture);
	float MoveUp(float deltaTime);
	float MoveDown(float deltaTime);
	float MoveLeft(float deltaTime);
	float MoveRight(float deltaTime);
	float GetXValue()const;
	float GetYValue()const;
	void Draw(SDL_Renderer* renderer, float CameraX, float CameraY, int MouseX, int MouseY, bool isPlayer, float deltaTime) override;
	void changeTexture(SDL_Texture* baseTexture, SDL_Texture* newTexture);
	void SetPlayerPosition(int x, int y);
	void SetEnemyPosition(int x, int y); 
	void SetColliderPos(int x, int y);
	void RotateTank(float RotationAngle); 
	void UpdateTank(float deltaTime); 
	void Fire(SDL_Texture* texture);
	float BarrelAngle; 
	int Health; 
	std::list<Bullet*> bullets;
	
private:
	
	//BoxCollider enemyCollider; 
	SDL_Texture* m_barrelTexture; 
	Controller TankType;
	float angle; 
	RigidBody2D rb;
	int tankID;
	float m_speed = 10; 
	
	//Vector2 TankPos;
	

	

	

	/*int X;
	int Y;
	int tankWidth = 40;
	int tankHeight = 35;*/
};

