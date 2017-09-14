#pragma once
#include "pch.h"

class Aircraft : public Enity
{
public:
	enum Type
	{
		Eagle,
		Raptor,
		Avenger,
		TypeCount
	};

public:
	explicit Aircraft(Type type,TextureHandles& textures, FontHandles& fonts);
	virtual void DrawThis(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void UpdateThis(sf::Time dt);
	virtual unsigned int GetCategory()const override;

	void UpdateText();

	float GetMaxSpeed()const;
	void UpdateMoventPattern(sf::Time dt);

private:
	sf::Sprite m_Sprite;
	TextNode* m_HealthDisplay;
	float m_TravelDistance;
	int m_DiretionIndex;
	Type m_Type;
};