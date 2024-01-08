#include "EnemyTankSpawner.h"
#include "Tank.h"
#include "Collision.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


EnemyTankSpawner::EnemyTankSpawner()
{

}

EnemyTankSpawner::EnemyTankSpawner(SDL_Texture* BaseTexture, SDL_Texture* BarrelTexture, SDL_Texture* SecondTexture)
{
	enemyBaseTexture = BaseTexture;
	enemyBarrelTexture = BarrelTexture;
	SecondaryTexture = SecondTexture; 

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
		
		int tankWidth = 40;
		int tankHeight = 35;
		bool overlap; 
		
		int x;
		int y;

		do {
			
		    overlap = false;
			x = std::rand() % (800 - tankWidth);
			y = std::rand() % (600 - tankHeight);
			for (const auto& tank : spawnedTanks)
			{
				int dx = std::abs(x - tank->Pos.x);
				int dy = std::abs(y - tank->Pos.y);

				if (dx < (tankWidth + 10) && dy < (tankHeight + 10))

				{
					overlap = true;
					std::cout << "Overlap detected. spawning at new position." << std::endl; 
					break;
				}
			}
		} while (overlap);

		

		

		spawnedTanks.push_back(new Tank(enemyBaseTexture, enemyBarrelTexture,SecondaryTexture, Enemy, "Enemy"));
		spawnedTanks[i]->SetEnemyPosition(x, y); //testing various positions 
		spawnedTanks[i]->SetColliderPos(spawnedTanks[i]->Pos.x, spawnedTanks[i]->Pos.y);
		spawnedTanks[i]->Ammo = 10; 
		
		///want a way to check their positions so do not spawn on each other 
		///check spawn pos doesnt clash with another tank 
	}

	
	std::cout << "Enemy Tanks Created: " << spawnedTanks.size() << std::endl;
	std::cout << "First Tank Position is: " << spawnedTanks[0]->Pos.x << " , " << spawnedTanks[0]->Pos.y << std::endl;
	std::cout << "First Tank Collider is: " << spawnedTanks[0]->boxCollider.x << " , " << spawnedTanks[0]->boxCollider.y << std::endl; 
}

void EnemyTankSpawner::DrawTanks(SDL_Renderer* renderer, float CameraX, float CameraY, int MouseX, int MouseY, bool isPlayer, float deltaTime)
{

	for (Tank* tank : spawnedTanks)
	{
		tank->Draw(renderer, CameraX, CameraY, MouseX,MouseY, false, deltaTime);

	}
	
}
//void EnemyTankSpawner::DestroyKilledTanks()
//{
//	for (auto* tank : TanksToDestroy)
//	{
//		delete tank;
//		std::cout << "Tank Destroyed" << std::endl; 
//	}
//	TanksToDestroy.clear();
//}


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

















