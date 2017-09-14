#include "pch.h"
#include "Enity.h"

Enity::Enity(int hitpoint):m_hitpoint(hitpoint)
{
}

void Enity::SetVelocity(sf::Vector2f v)
{
	m_Velocity = v;
}

sf::Vector2f Enity::GetVelocity() const
{
	return m_Velocity;
}

void Enity::Accelerate(sf::Vector2f velocity)
{
	m_Velocity += velocity;
	
}

void Enity::UpdateThis(sf::Time dt)
{
	move(m_Velocity*dt.asSeconds());

}

void Enity::Reqair(int p)
{
	m_hitpoint += p;
}

void Enity::Damage(int p)
{
	m_hitpoint -= p;
}

void Enity::Destroy()
{
	m_hitpoint = 0;
}

int Enity::GetHitpoints() const
{
	return m_hitpoint;
}

bool Enity::IsDestroy() const
{
	return m_hitpoint<=0;
}
