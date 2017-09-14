#pragma once
#include "pch.h"

struct Direction
{
	Direction(float angle, float dis) :angle(angle), distance(dis) {}
	float angle;
	float distance;
};
struct AircraftData
{
	int HitPoints;
	float Speed;
	Textures::ID Tex;
	std::vector<Direction> directions;

};

struct SpawnPoint
{
	SpawnPoint(Aircraft::Type type, float x, float y) :type(type), x(x), y(y) {}
	Aircraft::Type type;
	float x, y;
};

std::vector<AircraftData> initAircraftData();
