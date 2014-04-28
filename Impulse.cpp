#include "Impulse.h"


Impulse::Impulse( int x, int y, string texture )
{
	m_Position	= new Vec2D( x, y );
	m_Width		= 1;
	m_Height	= 1;
	m_Rotation	= 0;
	m_Destroyed = false;
	m_Texture	= texture;
	m_Type		= "impulse";
}


Impulse::~Impulse(void)
{
}

void Impulse::Update( double delta )
{
	if( m_Width > 100 ) m_Destroyed = true;

	m_Width	+=2;
	m_Height+=2;
}

void Impulse::Draw()
{
	glColor4f(0,0,0.8,((100.0-(double)m_Width)/100.0));
	glBegin( GL_TRIANGLE_FAN );
		glVertex2f(m_Position->getX() , m_Position->getY());
        for( int i = 0; i <= 360; ++i ) 
		{
			float const t = 2*PI*(float)i/(float)360;
			glVertex2f(m_Position->getX() + sin(t)*m_Width, m_Position->getY() + cos(t)*m_Height);
		}
   glEnd();
   glColor4f(1,1,1,1);
}