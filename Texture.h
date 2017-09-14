#pragma once

namespace Textures
{
	enum ID
	{
		Eagle,
		Raptor,
		Avenger,
		Desert, 
		TitleScreen,
		ButtonNormal,
		ButtonSelected,
		ButtonPressed,
	};
}

namespace Fonts
{
	enum ID
	{
		Main,
		Label,
	};
}

typedef ResourceHandle<sf::Texture, Textures::ID> TextureHandles;
typedef ResourceHandle<sf::Font, Fonts::ID> FontHandles;