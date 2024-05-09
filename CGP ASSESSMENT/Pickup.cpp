#include "Pickup.h"

Pickup::Pickup()
{

}

Pickup::~Pickup()
{
	for (auto pickup : spawnedPickups)
	{
		delete pickup;
	}
}

Pickup::Pickup(SDL_Texture* texture,SDL_Texture* PickedUpTexture)
{
	m_texture = texture;
	SecondTexture = PickedUpTexture; 
	value = 5; 
	m_h = 25;
	m_w = 25;
	boxCollider.m_height = 25;
	boxCollider.m_width = 25; 

}

void Pickup::SpawnPickups(int Amount, const EnemyTankSpawner& tankSpawner, const Obstacle& obstacle)
{
	for (int i = 0; i < Amount; i++)
	{
		bool overlap;
		int PickWidth = 25;
		int PickHeight = 25;
		
		int x;
		int y;
		do
		{
			overlap = false;
			x = std::rand() % (800 - PickWidth);
			y = std::rand() % (600 - PickHeight);
			for (const auto& pickup : spawnedPickups)
			{
				int dx = std::abs(x - pickup->Pos.x);
				int dy = std::abs(y - pickup->Pos.y);
				if (dx < (PickWidth + 100) && dy < (PickHeight + 100))

				{
					overlap = true;
					std::cout << "Overlap detected. spawning at new position." << std::endl;
					break;
				}
			}
			const std::vector<Tank*>& spawnedTanks = tankSpawner.GetSpawnedTanks();
			for (const auto& TANK : spawnedTanks)
			{
				int dx = std::abs(x - TANK->Pos.x);
				int dy = std::abs(y - TANK->Pos.y);
				if (dx < (PickWidth + 5) && dy < (PickHeight + 5))
				{
					overlap = true;
					std::cout << "Overlap detected. spawning at new position." << std::endl;
					break;
				}
			}
			const std::vector<Obstacle*>& SpawnedObstacles = obstacle.GetSpawnedObstacles();
			for (const auto& obstacle : SpawnedObstacles)
			{
				int dx = std::abs(x - obstacle->Pos.x);
				int dy = std::abs(y - obstacle->Pos.y);
				if (dx < (PickWidth + 10) && dy < (PickHeight + 10))

				{
					overlap = true;
					std::cout << "Overlap detected. spawning at new position." << std::endl;
					break;
				}
			}
		} while (overlap);

		spawnedPickups.push_back(new Pickup(m_texture, SecondTexture));
		spawnedPickups[i]->SetPosition(x, y); 
		spawnedPickups[i]->SetColliderPos(spawnedPickups[i]->Pos.x, spawnedPickups[i]->Pos.y);



	
	}
}

void Pickup::SetPosition(int x, int y)
{
	Pos.x = x;
	Pos.y = y;
}

void Pickup::SetColliderPos(int x, int y)
{
	boxCollider.x = x;
	boxCollider.y = y; 
}

int Pickup::GetValue()
{
	return value; 
}

void Pickup::PickupItem()
{
	isPickedup = true;
	m_texture = SecondTexture; 

}

void Pickup::DrawPickups(SDL_Renderer* renderer, float CameraX, float CameraY, int MouseX, int MouseY, bool isPlayer, float deltaTime)
{
	for (auto pickup : spawnedPickups)
	{
		pickup->Draw(renderer, CameraX, CameraY, MouseX, MouseY, false, deltaTime); 
	}
}
