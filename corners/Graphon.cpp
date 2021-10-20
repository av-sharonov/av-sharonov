#include "Graphon.h"
#include "data.h"

int Graphon::init(HWND Window)
{
	window = Window;
	sf::Rect rct=sf::IntRect(0, 0, 500, 500);
	sf::Rect rctFig = sf::IntRect(0, 0, 50, 50);
	font.loadFromFile("calibri.ttf");
	sf::Rect rctFrame = sf::IntRect(0, 0, 60, 60);
	//sf::Image image;
	// image.loadFromFile("c:\\desk.jpg");
	// textureBack.loadFromImage(image, rct);
	/// 	bool ret = textureBack.loadFromFile("resources\desk.jpg", rct);	bool ret = textureBack.loadFromFile("resources\\desk.jpg", rct);
	if (!textureBack.loadFromFile("resources\\desk1.png", rct))	//if(ret==0)
		return EXIT_FAILURE;
	spriteBack = std::make_unique<sf::Sprite>(textureBack);
	if(!frame.loadFromFile("resources\\frame.png", rctFrame))
		return EXIT_FAILURE;
	spriteFrame = sf::Sprite(frame);
	spriteFrame.setOrigin(sf::Vector2f(frame.getSize()) / 2.f);
	spriteFrame.setPosition(spriteFrame.getOrigin());
	//int i;
	for (int i = 0; i < ARRAY_PLAYERS_SIZE; i++)
	{
		texturesWhite.push_back(sf::Texture());
				//texturesWhite[i] = sf::Texture();		sf::Texture t = texturesWhite[i].loadFromFile("resources/white_fig.jpg");
		if (!texturesWhite[i].loadFromFile("resources\\white_fig.png", rctFig))
			return EXIT_FAILURE;
		spritesWhite.push_back(sf::Sprite(texturesWhite[i]));
		spritesWhite[i].setOrigin(sf::Vector2f(texturesWhite[i].getSize()) / 2.f);
		spritesWhite[i].setPosition(spritesWhite[i].getOrigin());

		texturesBlack.push_back(sf::Texture());
		//texturesWhite[i] = sf::Texture();		sf::Texture t = texturesWhite[i].loadFromFile("resources/white_fig.jpg");
		if (!texturesBlack[i].loadFromFile("resources\\black_fig.png", rctFig))
			return EXIT_FAILURE;
		spritesBlack.push_back(sf::Sprite(texturesBlack[i]));
		spritesBlack[i].setOrigin(sf::Vector2f(texturesBlack[i].getSize()) / 2.f);
		spritesBlack[i].setPosition(spritesBlack[i].getOrigin());
	}

	spriteBack->setOrigin(sf::Vector2f(textureBack.getSize()) / 2.f);
	spriteBack->setPosition(spriteBack->getOrigin());
	SFMLView = std::make_unique<sf::RenderWindow>(Window);

	return 0;
}

int Graphon::reInit(HWND Window)
{
	spriteBack->setOrigin(sf::Vector2f(textureBack.getSize()) / 2.f);
	spriteBack->setPosition(spriteBack->getOrigin());
	SFMLView = std::make_unique<sf::RenderWindow>(Window);
	return 0;
}

void Graphon::draw(sf::RenderTarget& target, sf::RenderStates states)
{

}

void Graphon::drawBack(void)
{
	//SFMLView = std::make_unique<sf::RenderWindow>(window);
	SFMLView->clear();
	SFMLView->draw(*spriteBack);
	/*for (int i = 0; i < ARRAY_PLAYERS_SIZE; i++)
	{
		SFMLView->draw(spritesWhite[i]);
		SFMLView->draw(spritesBlack[i]);

	}*/
	SFMLView->display();
}
