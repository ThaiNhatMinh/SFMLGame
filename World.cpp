#include "pch.h"
#include "World.h"
#include <iostream>
World::World(sf::RenderWindow & renderwindow, FontHandles& fonts) :m_Windows(renderwindow),m_Fonts(fonts),
m_WorldView(renderwindow.getDefaultView()),
m_WorldBound(0.0f, 0.0f, m_WorldView.getSize().x, 2000.0f),
m_SpawnPosition(m_WorldView.getSize().x / 2.0f, m_WorldBound.height - m_WorldView.getSize().y / 2.0f),
m_ScrollSpeed(-50.0f),
m_PlayerAircraft(nullptr)
{
	LoadTextures();
	BuildScene();

	m_WorldView.setCenter(m_SpawnPosition);
}

void World::Update(sf::Time dt)
{

	m_PlayerAircraft->SetVelocity(sf::Vector2f(0, 0));
	
	while (!m_CMDQueue.IsEmpty()) 
		m_SceneGraph.OnCommand(m_CMDQueue.Pop(), dt);
	
	m_WorldView.move(0.0f, m_ScrollSpeed*dt.asSeconds());

	SpawnEnemies();

	m_SceneGraph.Update(dt);
}

void World::Draw()
{
	m_Windows.setView(m_WorldView);
	m_Windows.draw(m_SceneGraph);

}

CommandQueue & World::GetCmdQueue()
{
	return m_CMDQueue;
}

void World::LoadTextures()
{
	m_Textures.Load(Textures::Eagle, "Media/Textures/Eagle.png");
	m_Textures.Load(Textures::Raptor, "Media/Textures/Raptor.png");
	m_Textures.Load(Textures::Desert, "Media/Textures/Desert.png");
	m_Textures.Load(Textures::Avenger, "Media/Textures/Avenger.png");

}

void World::BuildScene()
{
	for (int i = 0; i < LayerCount; i++)
	{
		SceneNode::Ptr layer(new SceneNode());
		m_SceneLayer[i] = layer.get();
		m_SceneGraph.AttachChild(std::move(layer));

	}



	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, m_Textures,m_Fonts));
	m_PlayerAircraft = player.get();
	m_PlayerAircraft->setPosition(m_SpawnPosition);
	m_PlayerAircraft->SetVelocity(sf::Vector2f(40.0f, m_ScrollSpeed));
	m_SceneLayer[Air]->AttachChild(std::move(player));


	sf::Texture& tex = m_Textures.Get(Textures::Desert);
	sf::IntRect texRect(m_WorldBound);
	tex.setRepeated(true);

	std::unique_ptr<SpriteNode> background(new SpriteNode(tex, texRect));
	background->setPosition(m_WorldBound.top, m_WorldBound.left);

	m_SceneLayer[BackGround]->AttachChild(std::move(background));
	
	AddEnemies();
}

void World::SpawnEnemies()
{
	while (!m_EnemySpawnPoint.empty() && GetBattleFieldBounds().top<m_EnemySpawnPoint.back().y)
	{
		SpawnPoint sp = m_EnemySpawnPoint.back();
		std::unique_ptr<Aircraft> enemy(new Aircraft(sp.type, m_Textures, m_Fonts));
		enemy->setPosition(sf::Vector2f(sp.x, sp.y));
		enemy->setRotation(180.0f);

		m_SceneLayer[Air]->AttachChild(std::move(enemy));
		m_EnemySpawnPoint.pop_back();

	}
}

void World::AddEnemies()
{
	AddEnemy(Aircraft::Raptor, 0.f, 500.f);
	AddEnemy(Aircraft::Raptor, 0.f, 1000.f);
	AddEnemy(Aircraft::Raptor, +100.f, 1100.f);
	AddEnemy(Aircraft::Raptor, -100.f, 1100.f);
	AddEnemy(Aircraft::Avenger, -70.f, 1400.f);
	AddEnemy(Aircraft::Avenger, -70.f, 1600.f);
	AddEnemy(Aircraft::Avenger, 70.f, 1400.f);
	AddEnemy(Aircraft::Avenger, 70.f, 1600.f);
	// Sort all enemies according to their y value, such that lower enemies are checked first for spawning
	std::sort(m_EnemySpawnPoint.begin(), m_EnemySpawnPoint.end(), [](SpawnPoint lhs, SpawnPoint rhs)
	{
		return lhs.y < rhs.y;
	});
}

void World::AddEnemy(Aircraft::Type type, float x, float y)
{
	m_EnemySpawnPoint.push_back(SpawnPoint(type,m_SpawnPosition.x + x,m_SpawnPosition.y - y));
}

sf::FloatRect World::GetBattleFieldBounds()
{
	sf::FloatRect bound = GetViewBounds();
	bound.top -= 100;
	bound.height += 100;
	return bound;
}

sf::FloatRect World::GetViewBounds() const
{
	return sf::FloatRect(m_WorldView.getCenter() - m_WorldView.getSize()/2.0f,m_WorldView.getSize());
}
