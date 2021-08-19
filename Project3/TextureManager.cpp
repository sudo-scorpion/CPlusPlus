#include "TextureManager.h"
#include <iostream>


unordered_map<string, sf::Texture> TextureManager::textures;
unordered_map<string, sf::Sprite> TextureManager::sprite;

void TextureManager::LoadTexture(const string& fileName)
{
    string path = "images/";
    path += fileName + ".png";

    textures[fileName].loadFromFile(path);
}

void TextureManager::LoadTexture(const string& fileName, sf::IntRect &rect)
{
    string path = "images/";
    path += fileName + ".png";

    textures[fileName].loadFromFile(path, rect);
}

sf::Texture& TextureManager::GetTexture(const string& textureName)
{
    if (textures.find(textureName) == textures.end())
    {
        LoadTexture(textureName);
    }
    return textures[textureName];
}


void TextureManager::LoadSprite(const string& fileName)
{

    sprite[fileName].setTexture(TextureManager::GetTexture(fileName));
}

sf::Sprite& TextureManager::GetSprite(const string& textureName)
{
    if (sprite.find(textureName) == sprite.end())
    {
        LoadSprite(textureName);
    }
    return sprite[textureName];
}

void TextureManager::Clear()
{
    textures.clear();
    sprite.clear();
}