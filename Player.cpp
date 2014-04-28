#include "Player.h"


Player::Player( int x, int y, int w, int h, string texture )
	: m_Lives(100), m_Vulnerable(true)
{
	m_Position	= new Vec2D( x, y );
	m_Width		= w;
	m_Height	= h;
	m_Texture	= texture;
	m_Rotation	= 0;
	m_Destroyed = false;
	m_Type		= "player";

	m_Speed	= 0;
	m_VelX	= 0;
	m_VelY	= -4;
}


Player::~Player(void)
{
}

void Player::Update( double delta )
{	
}

void Player::Draw()
{
}

int Player::getLives()
{
	return m_Lives;
}

bool Player::isVulnerable()
{
	return m_Vulnerable;
}

void Player::setLives( int l )
{
	m_Lives = l;
}

void Player::setVulnerable( bool v )
{
	m_Vulnerable = v;
}

void Player::IncLive( int l )
{
	m_Lives += l;
}

void Player::decLive( int l )
{
	m_Lives -= l;
}


