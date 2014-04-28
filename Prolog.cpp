#include "Prolog.h"


Prolog::Prolog(cGraphics *graphics, cInput *input, cSound *sound) 
	: m_ViewY(0),m_TimerBuffer(12)
{
	m_Graphics	= graphics;
	m_Input		= input;
	m_Sound		= sound;

	m_Graphics->setFont("astron");
	m_Graphics->setFontSize(30);
	for( int i = 0; i < 40; i++ )
	{
		int rX = rand() % (SCREEN_WIDTH-128) + 64;
		int rY = rand() % 2800 + 600;
		int rT = rand() % 3;
		if( rT == 0 )	m_Objects.push_back( Object( rX, rY, "rock" ) );
		if( rT == 1 )	m_Objects.push_back( Object( rX, rY, "bone" ) );
		if( rT == 2 )	m_Objects.push_back( Object( rX, rY, "worm" ) );
	}

	m_Sound->playSound("music");
}


Prolog::~Prolog()
{
}


int Prolog::Update( double delta )
{
	if( m_TimerBuffer > 0 ) m_TimerBuffer--;

	if( m_ViewY > -3600 ) 
	{
		m_ViewY -= 16;
	}

	if( m_Input->isKeyPressed(SDLK_SPACE) && m_TimerBuffer <= 0 )
	{
		if( m_ViewY > -3600 ) m_ViewY = -3600;
		else return STATE_GAME;

		m_TimerBuffer = 5;
	}


	return STATE_NULL;
}

void Prolog::Draw()
{
	//m_Graphics->setColor(0.2,0.09,0,0.9);
	m_Graphics->setColor(0.54,0.46,0.39,1);
	m_Graphics->drawRectangle(0,0,SCREEN_WIDTH,3000);
	m_Graphics->setColor(1,1,1,1);

	glTranslated(0,m_ViewY,0);

	m_Graphics->drawTexture("menu_background",0,0);

	m_Graphics->drawTexture("menupoint",(SCREEN_WIDTH-360)/2, 300);
	m_Graphics->drawTexture("menupoint",(SCREEN_WIDTH-360)/2, 420);
	
	m_Graphics->setFontColor(0.7,0.7,1);
	m_Graphics->drawText("Start Game",340,350);	
	m_Graphics->setFontColor(1,1,1);
	m_Graphics->drawText("Exit",380,470);

	for( int i = 0; i < m_Objects.size(); i++ )
	{
		m_Graphics->drawTexture( m_Objects[i].m_Texture, m_Objects[i].m_X, m_Objects[i].m_Y );
	}

	m_Graphics->setFontSize(42);
	m_Graphics->drawText("Press Space to start!",240,4100);
	m_Graphics->setFontSize(32);
	m_Graphics->drawText("You have to navigate the mole with sound waves.",120,3700);
	m_Graphics->drawText("Click somewhere to create a sound wave.",150,3750);
	m_Graphics->drawText("Avoid the Obstacles and collect the Worms!",140,3800);
	
	m_Graphics->drawSection("player_anim",128,0,128,128,SCREEN_WIDTH/2 - 64, 3900, 0);
//	m_Graphics->drawTexture("player_anim", SCREEN_WIDTH/2 - 64, 3900 );

	glLoadIdentity();
}