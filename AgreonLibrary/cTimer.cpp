/**
*	@file cTimer.cpp
*
*	@brief This file contains the cTimer functions.
*/
#include "cTimer.h"

cTimer::cTimer()
{
	m_LastTime = clock();
}


cTimer::~cTimer()
{
}

void cTimer::update()
{
	m_CurrentTime = clock();
   	m_DeltaTime = m_CurrentTime - m_LastTime;
   	m_LastTime = m_CurrentTime;
}

double cTimer::getDelta()
{
	return (double)m_DeltaTime/16;
}