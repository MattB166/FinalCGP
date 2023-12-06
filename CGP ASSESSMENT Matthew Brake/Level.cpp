#include "Level.h"

float Level::WorldX = 800;
float Level::WorldY = 600;

Level::Level()
{

}

void Level::PlayGame()
{

}

void Level::NewLevel()
{
	//once tanks all destroyed. new level loads 
}

void Level::CheckPlayerBounds(Tank* tank)
{
	if (tank->Pos.x <= 0)
	{
		tank->Pos.x = 0;
	}
	else if (tank->Pos.x >= WorldX - tank->m_w)
	{
		tank->Pos.x = WorldX - tank->m_w;
	}
	
	if (tank->Pos.x <= 0)
	{
		tank->Pos.y = 0;
	}
	else if (tank->Pos.y >= WorldY - tank->m_h)
	{
		tank->Pos.y = WorldY - tank->m_h;
	}
	
	
	 //compares tank pos to bounds of window and if same the pos 
}


