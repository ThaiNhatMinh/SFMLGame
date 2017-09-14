#pragma once
#include "pch.h"
#include "CommandQueue.h"
#include "DataTables.h"
#include <array>
class World : public sf::NonCopyable

{
public:
	explicit World(sf::RenderWindow& renderwindow,FontHandles& fonts);
	void Update(sf::Time);
	void Draw();
	CommandQueue& GetCmdQueue();
private:
	void LoadTextures();
	void BuildScene();
	void SpawnEnemies();
	void AddEnemies();
	void AddEnemy(Aircraft::Type type,float x,float y);
	sf::FloatRect GetBattleFieldBounds();
	sf::FloatRect GetViewBounds() const;
	
private:
	enum Layer {
		BackGround,
		Air,
		LayerCount
	};

private:
	sf::RenderWindow&			m_Windows;
	sf::View					m_WorldView;
	TextureHandles				m_Textures;
	FontHandles&					m_Fonts;
	SceneNode					m_SceneGraph;
	std::array<SceneNode*, LayerCount> m_SceneLayer;
	sf::FloatRect				m_WorldBound;
	sf::Vector2f				m_SpawnPosition;
	float						m_ScrollSpeed;
	Aircraft*					m_PlayerAircraft;
	CommandQueue				m_CMDQueue;
	std::vector<SpawnPoint>		m_EnemySpawnPoint;
};