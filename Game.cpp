#include "Game.h"


Game::Game( cGraphics *graphics, cAnimationManager *animations, cInput *input, cSound *sound )
	: m_MouseCounter(0),
	m_TileWidth(24), 
	m_Paused(false),
	m_ObstacleSpawn(75)
{
	m_Graphics			= graphics;
	m_AnimationManager	= animations;
	m_Input				= input;
	m_Sound				= sound;

	m_AnimationManager->createAnimation("player_anim","player_anim",-1,8,0,SCREEN_WIDTH/2 - 64,300,128,128);

	m_Player = new Player( SCREEN_WIDTH/2 - 64, 300, 128, 128, "player" );
	m_Entities.push_back( m_Player );
	m_Screen = Screen(0,0);

	for( int i = 0; i < SCREEN_WIDTH/m_TileWidth+3; i++ )
	{
		for( int j = 0; j < SCREEN_HEIGHT/m_TileWidth+12; j++ )
		{
			m_Tiles.push_back( Tile((i*m_TileWidth) -m_Screen.m_X -m_TileWidth ,(j*m_TileWidth)-m_Screen.m_Y - m_TileWidth*2,m_TileWidth));
		}
	}
	PLAYER_POINTS = 0;
}


Game::~Game()
{
	m_Sound->pauseSound("music");
	m_Sound->playSound("music_menu");
}


int Game::Update( double delta )
{
	if( m_Paused ) 
	{
		if( m_Input->isKeyPressed(SDLK_SPACE) ) m_Paused = false; 

		if( m_Input->isKeyPressed(SDLK_BACKSPACE) ) return STATE_MENU;

		return STATE_NULL;
	}

	if( m_Input->isKeyPressed(SDLK_ESCAPE) ) m_Paused = true;

	PLAYER_POINTS -= m_Player->getVelY();

	if( m_Player->getLives() <= 0 ) return STATE_POINTS;

	if( m_MouseCounter > 0 ) m_MouseCounter--;

	// Impulse Creation
	if( m_Input->leftMousePressed() && m_MouseCounter == 0 )
	{
		if( m_Input->getMousePositionY() > m_Player->getY() + m_Player->getHeight()/2 + 10)
		{
			m_MouseX = m_Input->getMousePositionX();
			m_MouseY = m_Input->getMousePositionY();

			m_Entities.push_back( new Impulse( m_MouseX - m_Screen.m_X, m_MouseY - m_Screen.m_Y, "impulse"));
			m_Sound->playSound("impulse");			

			int diffX = m_Player->getX() + m_Player->getWidth() / 2 - m_MouseX; 
			int diffY = m_Player->getY() + m_Player->getHeight() / 2 - m_MouseY;

			double diff = sqrt( diffX*diffX + diffY*diffY );

			if( diff < 200 && diff > -200 )
			{
				if( diffX > 10 || diffX < - 10 ) m_Player->setVelX( diffX / 20 );
				else m_Player->setVelX( 0 );

				if( m_Player->getVelX() > 4 ) m_Player->setVelX(4);
				if( m_Player->getVelX() < -4 ) m_Player->setVelX(-4);

				if( (m_Player->getVelX() >= -4 && m_Player->getVelX() <= -2) ||
					(m_Player->getVelX() <= 4 && m_Player->getVelX() >= 2) ) m_Player->setVelY(-2);

				if( (m_Player->getVelX() >= -2 && m_Player->getVelX() < 0) ||
					(m_Player->getVelX() <= 2 && m_Player->getVelX() > 0) ) m_Player->setVelY(-3);
				if( m_Player->getVelX() == 0 ) m_Player->setVelY(-4);

				double angle = tilt( m_MouseX, m_MouseY, m_Player->getX() + m_Player->getWidth() / 2, m_Player->getY() + m_Player->getHeight() / 2 );
				if( angle < 0 ) angle -= 180;
				m_Player->setRotation( angle - 90 );
			}
			m_MouseCounter = 14;
		}
	}

	UpdateTiles();
	SpawnObstacle();
	SpawnPickUp();

	bool coll = false;

	// Player Obstacle Collision
	for( auto& entity: m_Entities )
	{
		if( entity->getType () == "player" || entity->getType() == "impulse" ) continue;
		float deltaX = m_Player->getX() - entity->getX() - m_Screen.m_X;
		float deltaY = m_Player->getY() - (entity->getY() + m_Screen.m_Y);

		float distance = sqrtf(deltaX*deltaX + deltaY*deltaY);
 
		if (distance <= m_Player->getWidth()/2 + (entity->getWidth()+entity->getHeight())/2/2)
		{
			if( entity->getType() == "worm" )
			{
				PLAYER_POINTS += 100;
				m_Player->IncLive(10);
				entity->setDestroyed(true);
				m_Sound->playSound("pickup");
			}
			else
			{
				if( m_Player->isVulnerable() )
				{
					m_Player->decLive(30);
					m_Player->setVelX(0);
					m_Player->setVelY(-4);
					m_Player->setRotation(0);
					m_Sound->playSound("hit");
				}
				m_Player->setVulnerable(false);
				coll = true;
				break;
			}
		}
	}

	if( coll == false )
	{
		m_Player->setVulnerable(true);
	}

	for( auto& tile: m_Tiles )
	{
		float deltaX = m_Player->getX() + m_Player->getWidth()/2 - tile.m_X - 10 - m_Screen.m_X;
		float deltaY = m_Player->getY() + m_Player->getHeight()/2 - (tile.m_Y + m_Screen.m_Y);
 
		float distance = sqrtf(deltaX*deltaX + deltaY*deltaY);
 
		if (distance <= 64)
		{
			tile.m_Destroyed = true;
		}
	}

	// Entity-Update
	for( auto& entity : m_Entities ) entity->Update( delta );
	for( auto& entity : m_Entities )
	{
		if( entity->getY() + m_Screen.m_Y - entity->getHeight() > SCREEN_HEIGHT ) entity->setDestroyed(true);
	}

	for( int i = 0; i < m_Entities.size(); i++ )
	{
		if( m_Entities[i]->isDestroyed() )
		{
			m_Entities.erase( m_Entities.begin() + i );
		}
	}

	m_Screen.m_X -= m_Player->getVelX() * delta * 2;
	m_Screen.m_Y -= m_Player->getVelY() * delta * 2;

	m_AnimationManager->updateAll();
	m_AnimationManager->setPosition("player_anim",m_Player->getPosition()->getX(), m_Player->getPosition()->getY() );
	m_AnimationManager->setRotation("player_anim",m_Player->getRotation());

	return STATE_NULL;
}

void Game::UpdateTiles()
{
	for( int i = 0; i < m_Tiles.size(); i++ )
	{
		if( m_Tiles[i].m_Y + m_Screen.m_Y > SCREEN_HEIGHT ) 
		{
			m_Tiles[i].m_Y = - m_Screen.m_Y - m_TileWidth;
			m_Tiles[i].m_Destroyed = false;
		}
		if( m_Player->getVelX() > 0 )
		{
			if( m_Tiles[i].m_X + m_Screen.m_X + m_TileWidth < 0 )
			{
				m_Tiles[i].m_X = SCREEN_WIDTH - m_Screen.m_X + m_TileWidth;
				m_Tiles[i].m_Destroyed = false;
			}
		}
		else if( m_Player->getVelX() < 0 ) 
		{
			if( m_Tiles[i].m_X > SCREEN_WIDTH - m_Screen.m_X )
			{
				m_Tiles[i].m_X = -m_Screen.m_X - m_TileWidth*2;
				m_Tiles[i].m_Destroyed = false;
			}
		}
	}

	for( int j = 0; j < m_Tiles.size(); j++ )
	{
		if( m_Tiles[j].m_Y < - m_Screen.m_Y - m_TileWidth + 200 )
		{
			while( m_Tiles[j].m_Y % m_TileWidth != 0 )
			{
				m_Tiles[j].m_Y--;
			}
		}
		if( m_Player->getVelX() > 0 )
		{
			while( m_Tiles[j].m_X % m_TileWidth != 0 )
			{
				m_Tiles[j].m_X--;
			}
		}
		else if( m_Player->getVelX() < 0 ) 
		{
			while( m_Tiles[j].m_X % m_TileWidth != 0 )
			{
				m_Tiles[j].m_X++;
			}
		}
	}
}

void Game::SpawnObstacle()
{
	m_ObstacleSpawn -= 0.005;
	int r1 = rand() % 80;

	if( r1 > m_ObstacleSpawn )
	{
		int randX = rand() % (SCREEN_WIDTH*4) - m_Screen.m_X - SCREEN_WIDTH*2;

		int randType = rand() % 5;
		Obstacle *obstacle;

		switch( randType )
		{
		case 0: obstacle = new Obstacle( randX, -m_Screen.m_Y - 128, "rock" ); break;
		case 1: obstacle = new Obstacle( randX, -m_Screen.m_Y - 64, "bone" ); break;
		case 2: obstacle = new Obstacle( randX, -m_Screen.m_Y - 96, "apple" ); break;
		case 3: obstacle = new Obstacle( randX, -m_Screen.m_Y - 96, "stick" ); break;
		case 4: obstacle = new Obstacle( randX, -m_Screen.m_Y - 128, "ring" ); break;
		default: obstacle = new Obstacle( randX, -m_Screen.m_Y - 128, "rock" );			
		}

		bool coll = false;

		for( int i = 0; i < m_Entities.size(); i++ )
		{
			float deltaX = obstacle->getX() + m_Screen.m_X - m_Entities[i]->getX() - m_Screen.m_X;
			float deltaY = obstacle->getY() + m_Screen.m_Y - ( m_Entities[i]->getY() + m_Screen.m_Y);
 
			float distance = sqrtf(deltaX*deltaX + deltaY*deltaY);
 
			if (distance < 128)
			{
				coll = true;
				break;
			}
		}

		if( !coll ) m_Entities.push_back( obstacle );
	}
}

void Game::SpawnPickUp()
{
	int r1 = rand() % 80;

	if( r1 > 78 )
	{
		int randX = rand() % (SCREEN_WIDTH*2-64) - m_Screen.m_X - SCREEN_WIDTH;
		Obstacle* pickup = new Obstacle( randX, -m_Screen.m_Y - 128, "worm" );

		bool coll = false;

		for( int i = 0; i < m_Entities.size(); i++ )
		{
			float deltaX = pickup->getX() + m_Screen.m_X - m_Entities[i]->getX() - m_Screen.m_X;
			float deltaY = pickup->getY() + m_Screen.m_Y - ( m_Entities[i]->getY() + m_Screen.m_Y);
 
			float distance = sqrtf(deltaX*deltaX + deltaY*deltaY);
 
			if (distance < 128)
			{
				coll = true;
				break;
			}
		}
		if( !coll ) m_Entities.push_back( pickup );
	}
}

void Game::Draw()
{
	m_Graphics->setColor(0.2,0.08,0,0.9);
	m_Graphics->drawRectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	m_Graphics->setColor(1,1,1,1);

	glTranslatef( m_Screen.m_X, m_Screen.m_Y,  0 );
	// Tiles
	m_Graphics->setColor(0.54,0.46,0.39,1);
	glBegin(GL_QUADS);
	for( auto& tile : m_Tiles )
	{
		if( tile.m_Destroyed ) continue;
		glVertex2f( tile.m_X, tile.m_Y );
		glVertex2f( tile.m_X + m_TileWidth, tile.m_Y );
		glVertex2f( tile.m_X + m_TileWidth, tile.m_Y + m_TileWidth );
		glVertex2f( tile.m_X, tile.m_Y + m_TileWidth );
	}
	glEnd();
	m_Graphics->setColor(1,1,1,1);

	for( auto& entity : m_Entities )
	{
		if( entity->getType() == "player") continue;
		if( entity->getType() == "impulse" )
		{
			entity->Draw();
			continue;
		}
		m_Graphics->drawTexture( entity->getTexture(), entity->getX(), entity->getY(), entity->getRotation() );
	}
	glLoadIdentity();

	if( m_Player->isVulnerable() == false ) m_Graphics->setColor(1,1,1,0.6);
	m_AnimationManager->show("player_anim");
	m_Graphics->setColor(1,1,1,1);

	// UI
	string lives = "Health: "+itos(m_Player->getLives());
	m_Graphics->drawText(lives.c_str(),16,36);
	string points = "Points: "+itos(PLAYER_POINTS);
	m_Graphics->drawText(points.c_str(),16,66);

	if( m_Paused )
	{
		m_Graphics->drawText("Press BackSpace to Exit!",250,150);
		m_Graphics->drawText("Press Space to Continue!",250,200);
	}
}