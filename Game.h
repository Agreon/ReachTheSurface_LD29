#pragma once

#include "AgreonLibrary/Agreon.h"
#include "AgreonLibrary/cGraphics.h"
#include "AgreonLibrary/cAnimation.h"
#include "AgreonLibrary/cInput.h"
#include "AgreonLibrary/cSound.h"
#include "GameState.h"
#include "Player.h"
#include "Impulse.h"
#include "Obstacle.h"

struct Tile
{
	Tile()
		: m_X(0), m_Y(0), m_Width(0), m_Destroyed(false) {}
	Tile( int x, int y, int width ) 
		: m_X(x), m_Y(y), m_Width(width), m_Destroyed(false) {}
	int m_X;
	int m_Y;
	int m_Width;
	bool m_Destroyed;
};

struct Screen
{
	Screen() 
		: m_X(0), m_Y(0) {}
	Screen( double x, double y ) 
		: m_X(x), m_Y(y) {}
	double m_X;
	double m_Y;
};

class Game : public GameState
{
public:
	Game( cGraphics *graphics, cAnimationManager *animations, cInput *input, cSound *sound );
	~Game();

	int Update( double delta );
	void Draw();
	void SpawnObstacle();
	void SpawnPickUp();
	void UpdateTiles();
private:
	Player		*m_Player;
	vector<cEntity*> m_Entities;
	vector<Tile>	m_Tiles;

	Screen		m_Screen;
	int			m_MouseX;
	int			m_MouseY;
	int			m_MouseCounter;

	int			m_TileWidth;
	bool		m_Paused;
	double		m_ObstacleSpawn;
};

