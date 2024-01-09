#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "Obstacle.h"
#include "SDL_mixer.h"

#include <list>
#include <vector>


enum Controller
{
	Player, Enemy
};
enum State
{
	Alive, Dead
};

class Tank : public GameObject
{
public:
	Tank();
	~Tank();
	Tank(SDL_Texture* baseTexture, SDL_Texture* barrelTexture,SDL_Texture* SecondTexture, Controller type, std::string tag);
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
	void LayMine(SDL_Texture* texture); 
	void TakeDamage(int damage); 
	bool HasLineOfSight(const Tank& PlayerTank, const Tank& enemyTank);
	void RotateEnemyBarrelToPlayer(const Tank& playerTank);
	void DestroyBullets();
	int GetAmmo();
	int GetHealth();
	State GetTankState();
	//GameObject explosionObject; 
	float BarrelAngle; 
	int Health; 
	float Ammo; 
	float MinesAmmo; 
	float coolDown;
	bool hasFired = false; 
	std::list<Bullet*> bullets;
	std::list<Bullet*> BulletsToDestroy; 
	
	
private:
	
	//BoxCollider enemyCollider; 
	SDL_Texture* m_barrelTexture; 
	SDL_Texture* ExplodingTexture;
	Controller TankType;
	State TankState; 
	Mix_Chunk* Win;
	
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

