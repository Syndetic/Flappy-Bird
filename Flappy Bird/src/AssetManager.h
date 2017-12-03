#pragma once

#include <map>
#include <SFML/Graphics.hpp>

namespace fb
{
	class AssetManager
	{
	public:
		AssetManager() { }
		~AssetManager() { }

		void loadTexture(std::string name, std::string filename);
		sf::Texture& getTexture(std::string name);

		void loadFont(std::string name, std::string filename);
		sf::Font& getFont(std::string name);

	private:
		std::map<std::string, sf::Texture> textures;
		std::map<std::string, sf::Font> fonts;
	};
}