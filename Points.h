#pragma once

#include "gamestate.h"

class Points :
	public GameState
{
public:
	Points(cGraphics *graphics, cInput *input, cSound *sound); 
	~Points();

	int Update( double delta );
	void Draw();

	void getHighScore();
private:
	int	m_MenuPoint;
	int m_TimeBuffer;
	int m_HighScore;
	bool m_NewHighScore;
};

