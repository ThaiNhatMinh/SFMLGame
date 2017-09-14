#pragma once

#include "pch.h"


class Enity : public SceneNode
{
public:
	explicit Enity(int hitpoint);
	void SetVelocity(sf::Vector2f v);
	sf::Vector2f GetVelocity()const;
	void Accelerate(sf::Vector2f velocity);
	virtual void UpdateThis(sf::Time dt);


	void Reqair(int p);
	void Damage(int p);
	void Destroy();
	int GetHitpoints()const;
	bool IsDestroy()const;

private:
	int m_hitpoint;
	sf::Vector2f m_Velocity;
};