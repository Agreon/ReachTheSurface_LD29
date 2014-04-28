#pragma once

#include "agreonlibrary\centity.h"

class Obstacle :
	public cEntity
{
public:
	Obstacle( int x, int y, string type );
	~Obstacle();

	void Update( double delta );
	void Draw();
private:

};

