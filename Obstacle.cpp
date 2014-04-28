#include "Obstacle.h"


Obstacle::Obstacle( int x, int y, string type )
{
	m_Position = new Vec2D(x,y);
	m_Type = type;
	m_Texture = type;

	if( type == "rock" )
	{
		m_Width = 128;
		m_Height = 128;
	}
	else if( type == "bone" )
	{
		m_Width = 128;
		m_Height = 64;
	}
	else if( type == "worm" )
	{
		m_Width = 96;
		m_Height = 96;
	}

	m_Destroyed = false;
}


Obstacle::~Obstacle()
{
}

void Obstacle::Update( double delta )
{
}

void Obstacle::Draw()
{

}