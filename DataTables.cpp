#include "pch.h"
#include "DataTables.h"


std::vector<AircraftData> initAircraftData()
{
	std::vector<AircraftData> data(Aircraft::TypeCount);
	data[Aircraft::Eagle].HitPoints = 100;
	data[Aircraft::Eagle].Speed = 200.f;
	data[Aircraft::Eagle].Tex = Textures::Eagle;


	data[Aircraft::Raptor].HitPoints = 20;
	data[Aircraft::Raptor].Speed = 80.f;
	data[Aircraft::Raptor].Tex = Textures::Raptor;
	data[Aircraft::Raptor].directions.push_back(Direction(+45.f, 80.f));
	data[Aircraft::Raptor].directions.push_back(Direction(-45.f, 160.f));
	data[Aircraft::Raptor].directions.push_back(Direction(+45.f, 80.f));

	data[Aircraft::Avenger].HitPoints = 40;
	data[Aircraft::Avenger].Speed = 50.f;
	data[Aircraft::Avenger].Tex = Textures::Avenger;
	data[Aircraft::Avenger].directions.push_back(Direction(+45.f, 50.f));
	data[Aircraft::Avenger].directions.push_back(Direction(0.f, 50.f));
	data[Aircraft::Avenger].directions.push_back(Direction(-45.f, 100.f));
	data[Aircraft::Avenger].directions.push_back(Direction(0.f, 50.f));
	data[Aircraft::Avenger].directions.push_back(Direction(+45.f, 50.f));
	return data;
}