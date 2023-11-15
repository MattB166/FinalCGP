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
	if (tank->m_x <= 0)
	{
		tank->m_x = 0;
	}
	else if (tank->m_x >= WorldX)
	{
		tank->m_x = WorldX - 1;
	}
	
	if (tank->m_y <= 0)
	{
		tank->m_y = 0;
	}
	else if (tank->m_y >= WorldY)
	{
		tank->m_y = WorldY - 1; 
	}
	
	
	 //compares tank pos to bounds of window and if same the pos 
}


