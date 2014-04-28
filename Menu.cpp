#include "Menu.h"


Menu::Menu(cGraphics *graphics, cInput *input, cSound *sound) 
	: m_MenuPoint(0), m_TimeBuffer(10)
{
	m_Graphics	= graphics;
	m_Input		= input;
	m_Sound		= sound;

	m_Graphics->setFont("astron");
	m_Graphics->setFontSize(30);
}


Menu::~Menu()
{
	m_Sound->pauseSound("music_menu");
}


int Menu::Update( double delta )
{
	if( m_TimeBuffer > 0 )
	{
		m_TimeBuffer--;
		return STATE_NULL;
	}

	if( m_Input->isKeyPressed(SDLK_SPACE) || m_Input->isKeyPressed(SDLK_RETURN) )
	{
		switch(m_MenuPoint)
		{
		case 0:
			return STATE_PROLOG;
		case 1:
			return STATE_EXIT;
		default:
			break;
		}
	}

	if( m_Input->isKeyPressed(SDLK_UP) )
	{
		if( m_MenuPoint == 1 )
		{
			m_MenuPoint--;
			m_Sound->playSound("button");
		}	
	}
	if( m_Input->isKeyPressed(SDLK_DOWN) )
	{
		if( m_MenuPoint == 0 )
		{
			m_MenuPoint++;
			m_Sound->playSound("button");
		}
	}

	return STATE_NULL;
}

void Menu::Draw()
{
	m_Graphics->drawTexture("menu_background",0,0);

	m_Graphics->drawTexture("menupoint",(SCREEN_WIDTH-360)/2, 300);
	m_Graphics->drawTexture("menupoint",(SCREEN_WIDTH-360)/2, 420);
	
	if( m_MenuPoint == 0 )
	{
		m_Graphics->setFontColor(0.7,0.7,1);
		m_Graphics->drawText("Start Game",340,350);	
		m_Graphics->setFontColor(1,1,1);
		m_Graphics->drawText("Exit",380,470);
	}
	else
	{
		m_Graphics->setFontColor(1,1,1);
		m_Graphics->drawText("Start Game",340,350);	
		m_Graphics->setFontColor(0.7,0.7,1);
		m_Graphics->drawText("Exit",380,470);
	}	
}