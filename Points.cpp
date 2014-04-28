#include "Points.h"


Points::Points(cGraphics *graphics, cInput *input, cSound *sound) 
	: m_MenuPoint(0), m_TimeBuffer(0), m_NewHighScore(false)
{
	m_Graphics	= graphics;
	m_Input		= input;
	m_Sound		= sound;
	getHighScore();
}


Points::~Points()
{
}

int Points::Update( double delta )
{
	if( m_TimeBuffer > 0 ) m_TimeBuffer--;

	if( m_Input->isKeyPressed(SDLK_ESCAPE) ) return STATE_MENU;

	if( m_Input->isKeyPressed(SDLK_SPACE) )
	{
		switch(m_MenuPoint)
		{
		case 0: return STATE_MENU;
		case 1: return STATE_PROLOG;
		case 2: return STATE_EXIT;
		}
	}

	if( m_Input->isKeyPressed(SDLK_LEFT) && m_TimeBuffer == 0 )
	{
		if( m_MenuPoint > 0 )
		{
			m_MenuPoint--;
			m_Sound->playSound("button");
		}	
		m_TimeBuffer = 8;
	}
	if( m_Input->isKeyPressed(SDLK_RIGHT) && m_TimeBuffer == 0 )
	{
		if( m_MenuPoint < 2 )
		{
			m_MenuPoint++;
			m_Sound->playSound("button");
		}
		m_TimeBuffer = 8;
	}

	return STATE_NULL;
}

void Points::Draw()
{
	m_Graphics->drawTexture("menu_background",0,0);

	m_Graphics->setFontSize(52);
	string points = "Points: "+ itos(PLAYER_POINTS);
	m_Graphics->drawText(points.c_str(),75,350);
	string highscore = "Highscore: "+itos(m_HighScore);
	m_Graphics->drawText(highscore.c_str(),75,400);
	if( m_NewHighScore ) m_Graphics->drawText("New Highscore!",465,350);

	/*m_Graphics->setColor( 0.54, 0.4, 0.3, 1);
	m_Graphics->drawRectangle( 130, 460, 148, 72 );
	m_Graphics->setColor( 0.54, 0.4, 0.4, 1);
	m_Graphics->drawRectangle( 135, 464, 138, 64 );

	m_Graphics->setColor( 0.54, 0.4, 0.3, 1);
	m_Graphics->drawRectangle( 130, 460, 148, 72 );
	m_Graphics->setColor( 0.54, 0.4, 0.4, 1);
	m_Graphics->drawRectangle( 135, 464, 138, 64 );

	m_Graphics->setColor( 0.54, 0.4, 0.3, 1);
	m_Graphics->drawRectangle( 130, 460, 148, 72 );
	m_Graphics->setColor( 0.54, 0.4, 0.4, 1);
	m_Graphics->drawRectangle( 135, 464, 138, 64 );

	m_Graphics->setColor( 1, 1, 1, 1);*/

	if( m_MenuPoint == 0 ) m_Graphics->setFontColor(0.7,0.7,1);
	else m_Graphics->setFontColor(1,1,1);
	m_Graphics->drawText("Menu",150,510);

	if( m_MenuPoint == 1 ) m_Graphics->setFontColor(0.7,0.7,1);
	else m_Graphics->setFontColor(1,1,1);
	m_Graphics->drawText("Retry",350,510);

	if( m_MenuPoint == 2 ) m_Graphics->setFontColor(0.7,0.7,1);
	else m_Graphics->setFontColor(1,1,1);
	m_Graphics->drawText("Exit",550,510);

	m_Graphics->setFontColor(1,1,1);
}

void Points::getHighScore()
{
	ifstream in("data/game.cfg");
	string line;
	vector<string> lines;
	
	if(!in.is_open())
	{
		(*Log) << "ERROR: Could not open game.cfg!";
		return;
	}
	while( getline( in, line )) lines.push_back(line);

	m_HighScore = stoi(lines[0].c_str());

	if( m_HighScore <= PLAYER_POINTS )
	{
		m_HighScore = PLAYER_POINTS;
		in.close();
		ofstream out("data/game.cfg");

		out << m_HighScore << endl;

		out.close();
		m_NewHighScore = true;
	}
}