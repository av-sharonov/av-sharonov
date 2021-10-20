#pragma once
#include <SFML/Graphics.hpp>
//#include "Player.h"
#include <windows.h>

class Graphon
{
public:
	//Graphon();
	int init(HWND window);
	void draw(sf::RenderTarget& target, sf::RenderStates states);  // const;
	void drawBack();
	int reInit(HWND Window);
//protected:
	sf::Font font;
	sf::Texture textureBack;
	sf::Texture frame;
	sf::Sprite spriteFrame;
	std::vector<sf::Texture> texturesWhite;  // = sf::Texture[9];
	std::vector<sf::Texture> texturesBlack;   // [9] ;
	std::vector<sf::Sprite> spritesWhite;  // [9] ;
	std::vector<sf::Sprite> spritesBlack;  // [9] ;
	//if (!texture1.loadFromFile("resources/image1.jpg") || !texture2.loadFromFile("resources/image2.jpg"))
	//	return EXIT_FAILURE;
	HWND window;
	std::unique_ptr<sf::Sprite> spriteBack; 
	std::unique_ptr<sf::RenderWindow> SFMLView;

};

