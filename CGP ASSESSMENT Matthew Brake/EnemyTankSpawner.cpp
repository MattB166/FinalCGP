#include "EnemyTankSpawner.h"
#include "Tank.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


EnemyTankSpawner::EnemyTankSpawner()
{

}

EnemyTankSpawner::EnemyTankSpawner(SDL_Texture* BaseTexture, SDL_Texture* BarrelTexture)
{
	enemyBaseTexture = BaseTexture;
	enemyBarrelTexture = BarrelTexture;
	

	enemyCollider.m_width = 40;
	enemyCollider.m_height = 35;

	srand(static_cast<unsigned int>(std::time(0)));




}

EnemyTankSpawner::~EnemyTankSpawner()
{
	for (Tank* tank : spawnedTanks)
	{
		delete tank;
	}
}



void EnemyTankSpawner::SpawnTank(int amountOfTanks)
{
	for (int i = 0; i < amountOfTanks; i++)
	{
		//Tank enemyTank;
		//spawnedTanks.push_back(&enemyTank);
		int tankWidth = 40;
		int tankHeight = 35;

		//int x = std::rand() % (WindowWidth - tankWidth);
		//int y = std::rand() % (WindowHeight - tankHeight);

		////need to assign random dst rects 
		spawnedTanks.push_back(new Tank(enemyBaseTexture, enemyBarrelTexture));

		int x = std::rand() % (800 - tankWidth);  ///not very random
		int y = std::rand() % (600 - tankHeight);



		spawnedTanks[i]->SetEnemyPosition(x, y); //testing various positions 
		spawnedTanks[i]->SetColliderPos(spawnedTanks[i]->Pos.x, spawnedTanks[i]->Pos.y);
		

	}

	//need a way to assign randomly spawned positions on map 
	//spawnedTanks[0]->m_x = 100;
	//spawnedTanks[1]->m_x = 200;
	//spawnedTanks[2]->m_x = 300;
	std::cout << "Enemy Tanks Created: " << spawnedTanks.size() << std::endl;
	std::cout << "First Tank Position is: " << spawnedTanks[0]->Pos.x << " , " << spawnedTanks[0]->Pos.y << std::endl;
	std::cout << "First Tank Collider is: " << spawnedTanks[0]->boxCollider.x << " , " << spawnedTanks[0]->boxCollider.y << std::endl; 
}

void EnemyTankSpawner::DrawTanks(SDL_Renderer* renderer, float CameraX, float CameraY)
{

	for (Tank* tank : spawnedTanks)
	{
		tank->Draw(renderer, CameraX, CameraY);

	}
}

Tank* EnemyTankSpawner::getTankByIndex(int index) const
{
	if (index >= 0 && index < spawnedTanks.size())
	{
		return spawnedTanks[index];
    }
	else
	
	return nullptr;
}


void EnemyTankSpawner::AssignID()
{
	for (int i = 0; i < spawnedTanks.size(); i++)
	{
		///assign id for each tank as it is created 
	}
}

















