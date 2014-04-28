#pragma once

#include "agreonlibrary\centity.h"
#include "agreonlibrary\imovable.h"

class Player :
	public cEntity, public IMovable
{
public:
	Player( int x, int y, int w, int h, string texture );
	~Player();

	void Update( double delta );
	void Draw();

	int getLives();
	int getPoints();
	bool isVulnerable();

	void setLives( int l );
	void setVulnerable( bool v );

	void IncLive( int l );
	void decLive( int l );
private:
	int m_Lives;
	bool m_Vulnerable;
};

