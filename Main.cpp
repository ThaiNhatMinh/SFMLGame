#include "pch.h"
#include <iostream>

void main()
{
	try
	{
		//Game newGame;
		//newGame.Run();
		Appicaltion game;
		game.Run();
	}
	catch (std::exception& e)
	{
		std::cout<<"\nEXCEPTION: " << e.what() << std::endl;
	}
}