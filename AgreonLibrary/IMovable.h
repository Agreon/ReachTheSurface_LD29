#pragma once

class IMovable
{
protected:
	double	m_VelX;
	double	m_VelY;
	double	m_Speed;
public:
	IMovable();
	~IMovable();

	void setVelX( double velX )
	{
		m_VelX = velX;
	}

	void setVelY( double velY )
	{
		m_VelY = velY;
	}

	void setSpeed( double speed )
	{
		m_Speed = speed;
	}

	double getVelX()
	{
		return m_VelX;
	}

	double getVelY()
	{
		return m_VelY;
	}

	double getSpeed()
	{
		return m_Speed;
	}
};

