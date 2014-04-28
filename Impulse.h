#pragma once

#include "agreonlibrary\centity.h"

class Impulse :
	public cEntity
{
public:
	Impulse( int x, int y, string texture );
	~Impulse();

	void Update( double delta );
	void Draw();
private:
};

