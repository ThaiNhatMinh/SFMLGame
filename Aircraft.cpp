#include "pch.h"
#include "Aircraft.h"


namespace
{
	const std::vector<AircraftData> Table = initAircraftData();
}

Textures::ID toTextureID(Aircraft::Type type)
{
	switch (type)
	{
	case Aircraft::Eagle:
		return Textures::Eagle;

	case Aircraft::Raptor:
		return Textures::Raptor;
	}
}

Aircraft::Aircraft(Type type, TextureHandles& textures,FontHandles& fonts) :m_Type(type),Enity(Table[type].HitPoints),m_Sprite(textures.Get(toTextureID(type))),m_TravelDistance(0), m_DiretionIndex(0)
{
	sf::FloatRect bound = m_Sprite.getLocalBounds();
	m_Sprite.setOrigin(bound.width / 2.0f, bound.height / 2.0f);

	std::unique_ptr<TextNode> health(new TextNode(fonts, "100", 16));
	m_HealthDisplay = health.get();
	AttachChild(std::move(health));
}

void Aircraft::DrawThis(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_Sprite,states);
}

void Aircraft::UpdateThis(sf::Time dt)
{
	UpdateMoventPattern(dt);
	Enity::UpdateThis(dt);

	UpdateText();
}

unsigned int Aircraft::GetCategory()const 
{
	return Category::PlayerAircraft;
}

void Aircraft::UpdateText()
{
	m_HealthDisplay->SetString(toString(GetHitpoints()) + " HP");
	m_HealthDisplay->setPosition(0.0, 50.0f);
	m_HealthDisplay->setRotation(-getRotation());

}

float Aircraft::GetMaxSpeed() const
{
	return Table[m_Type].Speed;
}

void Aircraft::UpdateMoventPattern(sf::Time dt)
{
	const std::vector<Direction>& direction = Table[m_Type].directions;
	if (!direction.empty())
	{
		float distanceToMove = direction[m_DiretionIndex].distance;
		if (m_TravelDistance > distanceToMove)
		{
			m_DiretionIndex = (m_DiretionIndex + 1) % direction.size();
			m_TravelDistance = 0;
		}
		float radian = toRadian(direction[m_DiretionIndex].angle + 90.0f);
		float vx = GetMaxSpeed() * std::cos(radian);
		float vy = GetMaxSpeed()*std::sin(radian);
		SetVelocity(sf::Vector2f(vx, vy));
		m_TravelDistance += GetMaxSpeed() * dt.asSeconds();
	}


}
