#include "cApp.h"

cApp::cApp()
	: m_NextState(STATE_NULL)
{
}


cApp::~cApp(void)
{
}


bool cApp::Init()
{
	m_Graphics			= new cGraphics();
	m_AnimationManager	= new cAnimationManager(m_Graphics);
	m_Input				= new cInput();
	m_Sound				= new cSound();
	m_Timer				= new cTimer();
	
	m_Graphics->init( SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME, NULL );
	if( !LoadData() ) return false;

	m_Graphics->setFont("astron");
	m_Graphics->setFontSize(32);

	srand((unsigned) time(NULL));

	m_Sound->setVolume(100);

	return true;
}


void cApp::Run()
{
	m_Running = Init();

	m_StateID = STATE_INTRO;
	m_CurrentState = new Intro( m_Graphics, m_Input, m_Sound );

	while( m_Running )
	{
		if( m_Input->handleInput() ) m_Running = false;

		m_Timer->update();
		int delta = m_Timer->getDelta();
		if( delta > 24 ) delta = 24;

		m_NextState = m_CurrentState->Update( delta );
		ChangeState();

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0,0,0,1);
		
		m_CurrentState->Draw();

		SDL_GL_SwapBuffers();

		SDL_Delay( 16 );
	}
	CleanUp();
}

void cApp::ChangeState()
{
	if( m_NextState == STATE_EXIT )
	{
		m_Running = false;
		return;
	}
	if(m_NextState != STATE_NULL)
	{
        if(m_NextState != STATE_EXIT)
		{
			delete m_CurrentState;
        }
        switch(m_NextState)
		{
            case STATE_MENU:
				m_CurrentState = new Menu(m_Graphics,m_Input,m_Sound);
                break;
			case STATE_PROLOG:
				m_CurrentState = new Prolog(m_Graphics,m_Input,m_Sound);
                break;
            case STATE_GAME:
				m_CurrentState = new Game(m_Graphics,m_AnimationManager,m_Input,m_Sound);
                break;
			case STATE_POINTS:
				m_CurrentState = new Points(m_Graphics,m_Input,m_Sound);
        }
		m_StateID = m_NextState;
        m_NextState = STATE_NULL;
    }
}


void cApp::CleanUp()
{
	
}


bool cApp::LoadData()
{
	if( !m_Graphics->loadTexture("data/agreon_logo.png","logo")	||
		!m_Graphics->loadTexture("data/menu_background.png","menu_background")	||
		!m_Graphics->loadTexture("data/menupoint.png","menupoint")	||
		!m_Graphics->loadTexture("data/player_animation.png","player_anim")	||
		!m_Graphics->loadTexture("data/rock.png","rock")		||
		!m_Graphics->loadTexture("data/bone.png","bone")		||
		!m_Graphics->loadTexture("data/apple.png","apple")		||
		!m_Graphics->loadTexture("data/stick.png","stick")		||
		!m_Graphics->loadTexture("data/ring.png","ring")		||
		!m_Graphics->loadTexture("data/worm.png","worm")		||
		!m_Graphics->loadFont("data/font/astron_boy.ttf","astron") ||
		!m_Sound->loadSound("data/sound/button.wav","button")	|| 
		!m_Sound->loadSound("data/sound/hit.wav","hit")			|| 
		!m_Sound->loadSound("data/sound/impulse.wav","impulse") ||
		!m_Sound->loadSound("data/sound/pickup.wav","pickup")	||
		!m_Sound->loadMusic("data/sound/music.mp3","music")		||
		!m_Sound->loadMusic("data/sound/music_menu.mp3","music_menu")
		) return false;

	return true;
}


int main( int argc, char* args[] )
{
	cApp *app = new cApp();
	app->Run();

	delete app;
    return 0;
}