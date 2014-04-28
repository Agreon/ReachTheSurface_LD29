#pragma once

#include "gamestate.h"

class Menu :
	public GameState
{
public:
	Menu(cGraphics *graphics, cInput *input, cSound *sound); 
	~Menu();

	int Update( double delta );
	void Draw();
private:
	int	m_MenuPoint;
	int m_TimeBuffer;
};