#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using namespace std;

class TextureManager
{
    static unordered_map<string, sf::Texture> textures;
    static unordered_map<string, sf::Sprite> sprite;
public:
    static void LoadTexture(const string& fileName);
    static void LoadTexture(const string& fileName, sf::IntRect &rect);
    static sf::Texture& GetTexture(const string& textureName);
    static void LoadSprite(const string& fileName);
    static sf::Sprite& GetSprite(const string& textureName);
    static void Clear();
};
