#pragma once

#include "gamestate.h"

struct Object
{
	Object(int x, int y, string texture )
		: m_X(x), m_Y(y), m_Texture(texture) {}
	int m_X;
	int m_Y;
	string m_Texture;
};

class Prolog :
	public GameState
{
public:
	Prolog(cGraphics *graphics, cInput *input, cSound *sound); 
	~Prolog();

	int Update( double delta );
	void Draw();
private:
	int				m_TimerBuffer;
	double			m_ViewY;
	vector<Object>	m_Objects;
};

