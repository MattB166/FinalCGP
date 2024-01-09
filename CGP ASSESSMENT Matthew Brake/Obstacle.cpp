#include "Obstacle.h"


const std::vector<int> Obstacle::Rotations = { 0,90,180,270 };
Obstacle::Obstacle()
{

}

Obstacle::~Obstacle()
{
	for (auto Obstacle : SpawnedObstacles)
	{
		delete Obstacle; 
	}
}

Obstacle::Obstacle(SDL_Texture* texture)
{
	m_texture = texture;
	m_w = 60;
	m_h = 60;
	boxCollider.m_height = 45;
	boxCollider.m_width = 30;

	srand(static_cast<unsigned int>(std::time(0)));

	if (!Rotations.empty())
	{
		int randomSelection = std::rand() % Rotations.size();

		int selectedRot = Rotations[randomSelection];

		rotation = selectedRot;
	}
}

void Obstacle::SpawnObstacles(int Amount, const EnemyTankSpawner& tankSpawner)
{
	for (int i = 0; i < Amount; i++)
	{
		bool overlap; 
		int ObstWidth = 60;
		int ObstHeight = 60; 

		int x;
		int y;

		do
		{
			overlap = false;
			x = std::rand() % (800 - ObstWidth);
			y = std::rand() % (600 - ObstHeight);
			for (const auto& obstacle : SpawnedObstacles)
			{
				int dx = std::abs(x - obstacle->Pos.x);
				int dy = std::abs(y - obstacle->Pos.y); 
				if (dx < (ObstWidth + 10) && dy < (ObstHeight + 10))

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
				if (dx < (ObstWidth + 5) && dy < (ObstHeight + 5))
				{
					overlap = true;
					std::cout << "Overlap detected. spawning at new position." << std::endl;
					break;
				}
			}
		    


		} while (overlap);

		SpawnedObstacles.push_back(new Obstacle(m_texture));
		SpawnedObstacles[i]->SetPosition(x, y); 
		SpawnedObstacles[i]->SetColliderPos(SpawnedObstacles[i]->Pos.x, SpawnedObstacles[i]->Pos.y); 
	}

	std::cout << "Obstacles Created: " << SpawnedObstacles.size() << std::endl; 
	std::cout << "First Obstacle at: " << SpawnedObstacles[0]->Pos.x << " , " << SpawnedObstacles[0]->Pos.y << std::endl; 
	std::cout << "Second Obstacle at: " << SpawnedObstacles[1]->Pos.x << " , " << SpawnedObstacles[1]->Pos.y << std::endl; 
}

void Obstacle::DrawObstacles(SDL_Renderer* renderer, float CameraX, float CameraY, int MouseX, int MouseY, bool isPlayer, float deltaTime)
{
	for (Obstacle* obstacle : SpawnedObstacles)
	{
		obstacle->Draw(renderer, CameraX, CameraY, MouseX, MouseY, false, deltaTime); 
	}
}

void Obstacle::DestroyObstacles()
{
	
}

void Obstacle::SetPosition(int x, int y)
{
	Pos.x = x;
	Pos.y = y;
}

void Obstacle::SetColliderPos(int x, int y)
{
	boxCollider.x = x;
	boxCollider.y = y; 
}

bool Obstacle::contains(int px, int py) const
{
	return px >= Pos.x && px <= Pos.x + m_w && py >= Pos.y && py <= Pos.y + m_h;
}

const std::vector<Obstacle*>& Obstacle::GetSpawnedObstacles() const
{
	return SpawnedObstacles; 
}
