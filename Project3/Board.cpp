#include "Board.h"

int Board::width = 0;
int Board::height = 0;
int Board::numOfMine = 0;
const int Board::xCor[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int Board::yCor[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

int Board::GetWidth() {
    return width;
}

int Board::GetHeight() {
    return height;
}

Board::Tile::Tile(int x, int y) {
    _x = x;
    _y = y;
    _adjMine = 0;
    _isFlag = false;
    _isMine = false;
    _isClicked = false;
}

int Board::Tile::GetValueX() const {
    return _x;
}

int Board::Tile::GetValueY() const {
    return _y;
}

void Board::Tile::SetNumOfAdjMines(vector<vector<Tile>> &board, int x, int y) {
    int adjMine = 0;
    if (board[x][y].IsMine())
        adjMine = -1;
    else {
        for (int i = 0; i < 8; ++i) {
            if (CheckNeighbor(board, x + xCor[i], y + yCor[i]) && board[x + xCor[i]][y + yCor[i]].IsMine())
                adjMine++;
        }
    }
    _adjMine = adjMine;
}

int Board::Tile::GetNumOfAdjMines() const {
    return _adjMine;
}

bool Board::Tile::IsClicked() const {
    return _isClicked;
}

void Board::Tile::SetClicked() {
    _isClicked = true;
}

bool Board::Tile::IsFlagged() const {
    return _isFlag;
}

bool Board::Tile::IsMine() const {
    return _isMine;
}

void Board::Tile::SetMine(bool isMine) {
    _isMine = isMine;
}

void Board::Tile::SetFlag() {
    _isFlag = !_isFlag;
}

void Board::Tile::SetFlag(bool isFlag) {
    _isFlag = isFlag;
}

void Board::ReadConfigFile(const string &fileName) {
    vector<int> configData;
    configData.clear();

    string path = "boards/";
    path += fileName + ".cfg";
    string line;
    ifstream inputFile(path);

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            configData.push_back(stoi(line));
        }
        inputFile.close();
    } else
        cout << "Could not open the file " << fileName << endl;

    width = configData[0];
    height = configData[1];
    numOfMine = configData[2];
}

void Board::ReadTestFile(const string &fileName, vector<vector<string>> &testFileVec) {
    testFileVec.clear();

    string path = "boards/";
    path += fileName + ".brd";
    string line;
    ifstream inputFile(path);

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            vector<string> data;
            for (unsigned int i = 0; i < line.length(); i++)
                data.push_back(line.substr(i, 1));
            testFileVec.push_back(data);
        }
        inputFile.close();
    } else
        cout << "Could not open the file " << fileName << endl;
}

void Board::SettingNumbers(vector<vector<Tile>> &board) {
    for (unsigned int i = 0; i < board.size(); i++) {
        for (unsigned int j = 0; j < board[0].size(); j++) {
            board[i][j].SetNumOfAdjMines(board, (int) i, (int) j);
        }
    }
}

void Board::SettingTiles(vector<vector<Tile>> &board) {
    board.clear();

    for (int i = 0; i < height * 32; i += 32) {
        vector<Tile> tileVec;
        for (int j = 0; j < width * 32; j += 32) {
            Tile tile = Tile(j, i);
            tileVec.push_back(tile);
        }
        board.push_back(tileVec);
    }
}

void Board::SettingMines(vector<vector<Tile>> &board, vector<vector<string>> &fileVec) {
    for (unsigned int i = 0; i < fileVec.size(); i++) {
        for (unsigned int j = 0; j < fileVec[0].size(); j++) {
            if (fileVec[i][j] == "1")
                board[i][j].SetMine(true);
        }
    }
}

void Board::SettingHiddenTiles(vector<vector<Tile>> &board, sf::RenderWindow &window) {
    for (unsigned int i = 0; i < board.size(); i++) {
        for (unsigned int j = 0; j < board[0].size(); j++) {
            TextureManager::GetSprite("tile_hidden").setPosition((float) board[i][j].GetValueX(),
                                                                 (float) board[i][j].GetValueY());
            window.draw(TextureManager::GetSprite("tile_hidden"));
        }
    }
}

void Board::SettingFlags(sf::Event &event, vector<vector<Tile>> &board, bool &isValid) {
    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Right) {
            isValid = !isValid;
            if (!board[(event.mouseButton.y + 1) / 32][(event.mouseButton.x + 1) / 32].IsClicked())
                board[(event.mouseButton.y + 1) / 32][(event.mouseButton.x + 1) / 32].SetFlag();
        }
    }
}

void Board::ButtonClick(sf::Event &event, vector<vector<Tile>> &board, bool &isMine, bool &isDefeat) {

    if (Board::CheckNeighbor(board, (event.mouseButton.y + 1) / 32, (event.mouseButton.x + 1) / 32) &&
        board[(event.mouseButton.y + 1) / 32][(event.mouseButton.x + 1) / 32].IsFlagged())
        return;

    if (!isDefeat)
        Board::SetNeighbor(board, (event.mouseButton.y + 1) / 32, (event.mouseButton.x + 1) / 32);

    if (Board::CheckNeighbor(board, (event.mouseButton.y + 1) / 32, (event.mouseButton.x + 1) / 32) &&
        board[(event.mouseButton.y + 1) / 32][(event.mouseButton.x + 1) / 32].IsMine()) {
        isMine = true;
        isDefeat = true;
    }
    if (Board::CheckTextureBounds("debug", event.mouseButton.x, event.mouseButton.y))
        isMine = !isMine;

    if (Board::CheckTextureBounds("test_1", event.mouseButton.x, event.mouseButton.y)) {
        Board::TestBoard(board, 1);
        isMine = true;
        isDefeat = false;
    }

    if (Board::CheckTextureBounds("test_2", event.mouseButton.x, event.mouseButton.y)) {
        Board::TestBoard(board, 2);
        isMine = true;
        isDefeat = false;
    }

    if (Board::CheckTextureBounds("test_3", event.mouseButton.x, event.mouseButton.y)) {
        Board::TestBoard(board, 3);
        isMine = true;
        isDefeat = false;
    }

    if (Board::CheckTextureBounds("face_happy", event.mouseButton.x, event.mouseButton.y)) {
        if (isDefeat) {
            isDefeat = false;
            isMine = false;
        }
        Board::RestartBoard(board);
    }
}

void Board::Buttons(sf::RenderWindow &window) {
    TextureManager::GetSprite("face_happy").setPosition((float) (width * 32) / 2 - 64, (float) height * 32);
    window.draw(TextureManager::GetSprite("face_happy"));
    TextureManager::GetSprite("debug").setPosition((float) width * 32 - 4 * 64, (float) height * 32);
    window.draw(TextureManager::GetSprite("debug"));
    TextureManager::GetSprite("test_1").setPosition((float) width * 32 - 3 * 64, (float) height * 32);
    window.draw(TextureManager::GetSprite("test_1"));
    TextureManager::GetSprite("test_2").setPosition((float) width * 32 - 2 * 64, (float) height * 32);
    window.draw(TextureManager::GetSprite("test_2"));
    TextureManager::GetSprite("test_3").setPosition((float) width * 32 - 64, (float) height * 32);
    window.draw(TextureManager::GetSprite("test_3"));
}

int Board::TotalMines(vector<vector<Tile>> &board, sf::RenderWindow &window, bool &isMine, bool &isDefeat) {
    int flags = 0;
    int mines = 0;
    for (unsigned int i = 0; i < board.size(); i++) {
        for (unsigned int j = 0; j < board[0].size(); j++) {
            if (isDefeat)
                board[i][j].SetFlag(false);
            if (board[i][j].IsFlagged()) {
                TextureManager::GetSprite("flag").setPosition((float) board[i][j].GetValueX(),
                                                              (float) board[i][j].GetValueY());
                window.draw(TextureManager::GetSprite("flag"));
                flags++;
            }
            if (board[i][j].IsMine()) {
                TextureManager::GetSprite("mine").setPosition((float) board[i][j].GetValueX(),
                                                              (float) board[i][j].GetValueY());
                if (isMine) {
                    TextureManager::GetSprite("tile_revealed").setPosition((float) board[i][j].GetValueX(),
                                                                           (float) board[i][j].GetValueY());
                    window.draw(TextureManager::GetSprite("tile_revealed"));
                    window.draw(TextureManager::GetSprite("mine"));
                }
                mines++;
            }
        }
    }
    return mines - flags;
}

void Board::PlacingNumValues(vector<vector<Tile>> &board, sf::RenderWindow &window) {
    for (unsigned int i = 0; i < board.size(); i++) {
        for (unsigned int j = 0; j < board[0].size(); j++) {
            if (board[i][j].IsClicked()) {
                TextureManager::GetSprite("tile_revealed").setPosition((float) board[i][j].GetValueX(),
                                                                       (float) board[i][j].GetValueY());
                window.draw(TextureManager::GetSprite("tile_revealed"));
                for (unsigned int k = 1; k <= 8; k++) {
                    if (board[i][j].GetNumOfAdjMines() == k) {
                        TextureManager::GetSprite("number_" + to_string(k)).setPosition((float) board[i][j].GetValueX(),
                                                                                        (float) board[i][j].GetValueY());
                        window.draw(TextureManager::GetSprite("number_" + to_string(k)));
                    }
                }
            }
        }
    }
}

void Board::SettingFaces(vector<vector<Tile>> &board, sf::RenderWindow &window, bool &isDefeat, bool &isMineValid) {
    if (isDefeat) {
        TextureManager::GetSprite("face_lose").setPosition((float) (width * 32) / 2 - 64, (float) height * 32);
        window.draw(TextureManager::GetSprite("face_lose"));
        for (unsigned int i = 0; i < board.size(); i++) {
            for (unsigned int j = 0; j < board[0].size(); j++) {
                if (board[i][j].IsMine()) {
                    isMineValid = true;
                }
            }
        }
    } else if (!isDefeat && Board::IsVictory(board)) {
        TextureManager::GetSprite("face_win").setPosition(((float) width * 32) / 2 - 64, (float) height * 32);
        window.draw(TextureManager::GetSprite("face_win"));
        for (unsigned int i = 0; i < board.size(); i++) {
            for (unsigned int j = 0; j < board[0].size(); j++) {
                if (board[i][j].IsMine()) {
                    isMineValid = false;
                    board[i][j].SetFlag(true);
                }
            }
        }
    }
}

bool Board::CheckNeighbor(vector<vector<Board::Tile>> &board, int x, int y) {
    return x >= 0 && y >= 0 && x < board.size() && y < board[0].size();
}


bool Board::CheckTextureBounds(const string &sprite, int x, int y) {
    return TextureManager::GetSprite(sprite).getGlobalBounds().contains((float) x, (float) y);
}

void Board::SetNeighbor(vector<vector<Tile>> &board, int x, int y) {
    if (CheckNeighbor(board, x, y) && board[x][y].GetNumOfAdjMines() == 0
        && !board[x][y].IsClicked() && !board[x][y].IsFlagged()) {
        board[x][y].SetClicked();
        for (int i = 0; i < 8; ++i) {
            SetNeighbor(board, x + xCor[i], y + yCor[i]);
        }
    } else if (CheckNeighbor(board, x, y) && board[x][y].GetNumOfAdjMines() != 0 &&
               board[x][y].GetNumOfAdjMines() != -1) {
        board[x][y].SetClicked();
    }
}

void Board::TestBoard(vector<vector<Tile>> &board, int testOption) {
    vector<vector<string>> testFileVec;
    board.clear();
    testFileVec.clear();

    if (testOption == 1)
        Board::ReadTestFile("testboard1", testFileVec);
    else if (testOption == 2)
        Board::ReadTestFile("testboard2", testFileVec);
    else if (testOption == 3)
        Board::ReadTestFile("testboard3", testFileVec);

    Board::SettingTiles(board);
    Board::SettingMines(board, testFileVec);
    Board::SettingNumbers(board);
}

void Board::RestartBoard(vector<vector<Tile>> &board) {
    board.clear();
    vector<int> randomVec;
    randomVec.clear();

    Board::SettingTiles(board);

    while (randomVec.size() < numOfMine) {
        randomVec.push_back(Random::IntRand(0, (width * height) - 1));
        sort(randomVec.begin(), randomVec.end());
        randomVec.erase(unique(randomVec.begin(), randomVec.end()), randomVec.end());
    }

    for (int i = 0; i < numOfMine; i++)
        board[randomVec[i] / width][randomVec[i] % width].SetMine(true);

    Board::SettingNumbers(board);
}

bool Board::IsVictory(vector<vector<Tile>> &board) {
    int tileCounter = 0;
    int mineCounter = 0;
    for (unsigned int i = 0; i < board.size(); i++) {
        for (unsigned int j = 0; j < board[0].size(); j++) {
            if (board[i][j].IsClicked())
                tileCounter++;
            else if (board[i][j].IsMine())
                mineCounter++;
        }
    }
    return (tileCounter == (width * height - mineCounter));
}

void Board::DisplayDigits(sf::RenderWindow &window, int value, int position) {
    if (value < 0)
        value *= (-1);
    sf::IntRect rect(21 * value, 0, 21, 32);
    TextureManager::LoadTexture("digits", rect);
    TextureManager::GetSprite("digits").setPosition((float) position, (float) height * 32);
    window.draw(TextureManager::GetSprite("digits"));
}

