#pragma once

#include "AgreonLibrary/agreon.h"
#include "Intro.h"
#include "Menu.h"
#include "Prolog.h"
#include "Game.h"
#include "Points.h"

class cApp
{
public:
	cApp();
	~cApp();

	bool Init();
	void Run();
	void CleanUp();
	bool LoadData();

	void ChangeState();
private:
	cGraphics			*m_Graphics;
	cAnimationManager	*m_AnimationManager;
	cInput				*m_Input;
	cSound				*m_Sound;
	cTimer				*m_Timer;
	
	GameState	*m_CurrentState;
	int			m_NextState;
	int			m_StateID;

	bool		m_Running;
};

