#include "Tank.h"
#include "SDL.h"
#include <iostream>



Tank::Tank()
{
	
}

Tank::~Tank()
{
	for (auto* bullet : bullets)
	{
		delete bullet;
	}
	Mix_FreeChunk(Win); 
}

Tank::Tank(SDL_Texture* baseTexture, SDL_Texture* barrelTexture,SDL_Texture* SecondTexture, Controller type, std::string tag)
{
	m_texture = baseTexture; 
	m_barrelTexture = barrelTexture;
	ExplodingTexture = SecondTexture; 
	TankType = type; 
	Win = Mix_LoadWAV("Assets/Winsound.wav");
	std::cout <<  "Tank Created" << std::endl;
	m_w= 40;
	m_h = 35;
	Pos.x = 50;
	Pos.y= 50;
	//boxCollider.x = m_x;
	//boxCollider.y = m_y;
	SetPlayerPosition(200, 200);
	boxCollider.m_height = 35;
	boxCollider.m_width = 40;
	Health = 3;
	TankState = Alive; 
	Ammo = 10; 
	boxCollider.Tag = tag; 
	coolDown = 0.0f;

	isAnimated = false;
    animationSpeed = 60;
	animPixelWidth = 48;
	animPixelHeight = 48; 
	animState = 0;
	animFrames = 7; 
	
	/////need to set min and max x and y values for collision function 
	
	
}



float Tank::MoveUp(float deltaTime)
{
	Pos.y -= m_speed * deltaTime;
	//TankPos.y -= m_speed * deltaTime;
	boxCollider.y = Pos.y;
	return Pos.y;
}

float Tank::MoveDown(float deltaTime)
{
	Pos.y += m_speed * deltaTime;
	boxCollider.y = Pos.y;
	return Pos.y;
}

float Tank::MoveLeft(float deltaTime)
{
	Pos.x -= m_speed * deltaTime;
	boxCollider.x = Pos.x;
	return Pos.x;
}


float Tank::MoveRight(float deltaTime)
{
	Pos.x += m_speed * deltaTime;
	boxCollider.x = Pos.x;
	return Pos.x; 
}

float Tank::GetXValue() const
{
	return Pos.x;
}

float Tank::GetYValue() const
{
	return Pos.y;
}

void Tank::Draw(SDL_Renderer* renderer, float CameraX, float CameraY, int MouseX, int MouseY, bool isPlayer, float deltaTime)
{
	GameObject::Draw(renderer, CameraX, CameraY, MouseX, MouseY, false, deltaTime);
	Vector2 PlayerPos;
	if (isPlayer)
	{
		Vector2 tankCentre = Pos + Vector2(m_w / 2, m_h / 2);
		Vector2 mouseVec = Vector2(MouseX, MouseY) - tankCentre;
		BarrelAngle = atan2(mouseVec.y, mouseVec.x) * (180.0 / M_PI); 
		PlayerPos = tankCentre;
	}
	/*else
	{
		//// need a way for the enemy barrel to be locked on to player pos 
		
	}*/
	int x = Pos.x + m_w / 2 - 8 / 2; /// setting barrel width 
	int y = Pos.y + m_h / 2;  ///setting barrel height 
	SDL_Rect dstRect{ x - CameraX ,y - CameraY ,m_w / 5,m_h / 1.3 }; //sets barrel dest to correct position
	SDL_Point BarrelAnchor = { 4,0 }; 
	
	//SDL_RenderCopy(renderer, m_barrelTexture, NULL, &dstRect);
	SDL_RenderCopyEx(renderer, m_barrelTexture, NULL, &dstRect, BarrelAngle - 90, &BarrelAnchor, { SDL_FLIP_NONE });     
	//SDL_RenderCopyEx(renderer,m_barrelTexture,NULL,&dstRect,angle,) //last couple of parameters needed 

}




void Tank::changeTexture(SDL_Texture* baseTexture, SDL_Texture* newTexture)  ////changes texture on command between 2, useful for landmines flashing 
{
	if (m_texture != newTexture)
	{
		m_texture = newTexture;
		//GameObject::Draw(renderer);
	}
	else
	{
		m_texture = baseTexture;
		//GameObject::Draw(renderer);
	}

	
}

void Tank::SetPlayerPosition(int x , int y)
{
	Pos.x = x;
	Pos.y = y;
}

void Tank::SetEnemyPosition(int x, int y)
{
	Pos.x = x;
	Pos.y = y;
}

void Tank::SetColliderPos(int x, int y)
{
	boxCollider.x = x;
	boxCollider.y = y; 
}

void Tank::RotateTank(float RotationAngle)
{
	rb.angle += RotationAngle;
}

void Tank::UpdateTank(float deltaTime)
{

}

void Tank::Fire(SDL_Texture* texture)
{
	//std::cout << "Firing" << std::endl; 
	if (Ammo <= 0)
	{
		Ammo = 0; 
		//std::cout << "NO AMMO" << std::endl; 
		///do nothing
	}
	else if (coolDown > 0)
	{
		///do nothing 
	}
	else if (TankState == Dead)
	{
		////cannot fire
	}
	else
	{

		Bullet* bullet = new Bullet(texture);
		///set bullet velocity here. maybe bullet draw function here too? or inside its own class? 
		///bullet->fire( needs to take turret angle etc in this. 
		bullet->Fire(BarrelAngle, Pos.x + m_w / 2, Pos.y + m_h / 2);
		bullets.push_back(bullet);
		coolDown = 60.0f; 
		//std::cout << "Added bullet to list" << std::endl; 
		std::cout << "Barrel Angle is: " << BarrelAngle << std::endl;
		--Ammo; 
	}
	
	
}

void Tank::LayMine(SDL_Texture* texture)
{
	/// minebomb.laymine etc etc 
}

void Tank::TakeDamage(int damage)
{
	Health -= damage; 
	std::cout << "Damage Taken" << std::endl; 
	if (Health <= 0)
	{
		Health = 0; 
		TankState = Dead;
		Mix_PlayChannel(-1, Win, 0);
		if (!Win)
		{
			std::cerr << "Failed to load sound: " << Mix_GetError() << std::endl;
		}
		m_texture = ExplodingTexture; 
		m_barrelTexture = nullptr; 
		if (animState != 7)
		{
			isAnimated = true;
			animState = 0;
			//explosionObject.Pos.x = Pos.x;
			//explosionObject.Pos.y = Pos.y;
			std::cout << "TANK Dead. animation playing" << std::endl;
		}
		
	}
}

bool Tank::HasLineOfSight(const Tank& PlayerTank, const Tank& enemyTank, const std::vector<Obstacle*>& obstacles)
{
	
	
		int playerX = PlayerTank.GetXValue() + PlayerTank.m_w / 2;
		int playerY = PlayerTank.GetYValue() + PlayerTank.m_h / 2;
		int enemyX = enemyTank.GetXValue() + enemyTank.m_w / 2;
		int enemyY = enemyTank.GetYValue() + enemyTank.m_h / 2;

		int dx = abs(enemyX - playerX);
		int dy = abs(enemyY - playerY);

		int sx = (playerX < enemyX) ? 1 : -1;
		int sy = (playerY < enemyY) ? 1 : -1;
		bool isBlockingLOS = false; 

		int err = dx - dy;
		bool playerOnSameSide = true; 
		while (true)
		{
			if (playerX == enemyX && playerY == enemyY)
			{
				std::cout << "SAME POS. BREAKING" << std::endl; 
				break;

			}
			for (const Obstacle* obstacleptr : obstacles)
			{
				const Obstacle& obstacle = *obstacleptr;
				if (obstacle.contains(PlayerTank.Pos.x, PlayerTank.Pos.y))
				{
					isBlockingLOS = true;
					int distanceToObject = std::sqrt(std::pow(obstacle.Pos.x - PlayerTank.Pos.x, 2) + std::pow(obstacle.Pos.y - PlayerTank.Pos.y, 2));
					if (distanceToObject < 10 && ((sx > 0 && playerX < obstacle.Pos.x) || (sx < 0 && playerX > obstacle.Pos.x)))
					{
						playerOnSameSide = false;
					}
					std::cout << "LOS Blocked by obstacle at: " << obstacle.Pos.x << " , " << obstacle.Pos.y << std::endl; 
					break;
				}
					//return false;
			}
			if (isBlockingLOS)
			{
				if (!playerOnSameSide)
				{
					std::cout << "Player on other side of obstacle. Unreachable!" << std::endl; 
					return false;
				}
				return false;
			}
				
			int e2 = 2 * err;

			if (e2 > -dy)
			{
				err -= dy;
				playerX += sx;
			}
			if (e2 < dx)
			{
				err += dx;
				playerY += sy;
		
			}
			

		}
		std::cout << "LOS Clear" << std::endl; 
		return true;
		
		
		//return false; 

	
	
}
void Tank::RotateEnemyBarrelToPlayer(const Tank& playerTank)
{
	if (TankState != Dead)
	{
		float angle = atan2(playerTank.Pos.y - Pos.y, playerTank.Pos.x - Pos.x);

		angle = angle * 180.0f / M_PI;

		BarrelAngle = angle;
	}
	
}

void Tank::DestroyBullets()
{
	for (auto* bullet : BulletsToDestroy)
	{
		delete bullet;
		std::cout << " Bullet destroyed from memory" << std::endl;

	}
	BulletsToDestroy.clear();
}

int Tank::GetAmmo()
{
	return Ammo; 
}

int Tank::GetHealth()
{
	return Health; 
}
State Tank::GetTankState()
{
	return TankState;
}






