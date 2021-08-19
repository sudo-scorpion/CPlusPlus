#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include "Random.h"
#include "TextureManager.h"

using namespace std;

class Board {
    // board configuration data
    static int width;
    static int height;
    static int numOfMine;
    // grid space's neighbor coordinates
    static const int xCor[8];
    static const int yCor[8];
public:
    class Tile {
        int _x;
        int _y;
        // number of adj mines
        int _adjMine;
        bool _isClicked;
        bool _isMine;
        bool _isFlag;
    public:
        // default tile constructor
        explicit Tile(int x = 0, int y = 0);

        // set number of mines are adjacent to a tile space
        void SetNumOfAdjMines(vector<vector<Tile>> &board, int x, int y);

        // set click
        void SetClicked();

        // set mines takes a boolean value
        void SetMine(bool isMine);

        // set flag
        void SetFlag();

        // set flag takes a boolean value
        void SetFlag(bool isFlag);

        // return value of x coordinates
        int GetValueX() const;

        // return value of y coordinate
        int GetValueY() const;

        // return mu,ber of adjacent mines
        int GetNumOfAdjMines() const;

        // return a boolean value of click
        bool IsClicked() const;

        // return a boolean value of mine
        bool IsMine() const;

        // return a boolean value of flag
        bool IsFlagged() const;
    };

public:
    // return board width
    static int GetWidth();

    // return board height
    static int GetHeight();

    // read configuration file and sets configuration data
    static void ReadConfigFile(const string &fileName);

    // read test file data
    static void ReadTestFile(const string &fileName, vector<vector<string>> &testFileVec);

    // setting number value attached to all tiles if 0 then empty if -1 then mine
    static void SettingNumbers(vector<vector<Tile>> &board);

    // setting tiles
    static void SettingTiles(vector<vector<Tile>> &board);

    // setting mines
    static void SettingMines(vector<vector<Tile>> &board, vector<vector<string>> &fileVec);

    // setting hidden tiles
    static void SettingHiddenTiles(vector<vector<Tile>> &board, sf::RenderWindow &window);

    // setting flags
    static void SettingFlags(sf::Event &event, vector<vector<Tile>> &board, bool &isValid);

    // setting button actions
    static void ButtonClick(sf::Event &event, vector<vector<Tile>> &board, bool &isMineValid, bool &isDefeat);

    // setting buttons
    static void Buttons(sf::RenderWindow &window);

    // return total mines - flags
    static int TotalMines(vector<vector<Tile>> &board, sf::RenderWindow &window, bool &isMineValid, bool &isDefeat);

    // inserting number values in the board
    static void PlacingNumValues(vector<vector<Tile>> &board, sf::RenderWindow &window);

    // displaying counter digits at the left bottom corner
    static void DisplayDigits(sf::RenderWindow &window, int value, int position);

    // setting faces and change according to the game like if defeat sets lose_face
    static void SettingFaces(vector<vector<Tile>> &board, sf::RenderWindow &window, bool &isDefeat, bool &isMineValid);

    // checks neighbor for mines and coordinates validity
    static bool CheckNeighbor(vector<vector<Board::Tile>> &board, int x, int y);

    // checks grid space bounds to execute a specific action when it's clicked on that texture
    static bool CheckTextureBounds(const string &sprite, int x, int y);

    // sets neighbor
    static void SetNeighbor(vector<vector<Tile>> &board, int x, int y);

    // sets the test board configuration
    static void TestBoard(vector<vector<Tile>> &board, int testOption);

    // resets the board
    static void RestartBoard(vector<vector<Tile>> &board);

    // check for victory total tiles - number of mines
    static bool IsVictory(vector<vector<Tile>> &board);

};