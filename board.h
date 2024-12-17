#ifndef UNTITLED8_BOARD_H
#define UNTITLED8_BOARD_H
#include <chrono>
#include "tiles.h"
#include "random.h"
#include "leaderboard.h"
class Board{
    vector<vector<Tile>> board;
    TextureManager t;
    int cols;
    int rows;
    int numMines;
    int numFlags;
    int tilesRemaining;
    bool paused;
    bool win;
    bool lose;
    bool debugMode;
    string name;
    sf::Sprite digits[11];
    sf::Sprite smileySprite;
    sf::Sprite loseSprite;
    sf::Sprite winSprite;
    sf::Sprite debugSprite;
    sf::Sprite pauseSprite;
    sf::Sprite playSprite;
    sf::Sprite leaderBoard;
    sf::Sprite minetile;
    sf::Sprite numTile;
    sf::Sprite flag;
    sf::Sprite negcount;
    chrono::time_point<chrono::high_resolution_clock> startTime;
    chrono::duration<int> time;
    chrono::time_point<chrono::high_resolution_clock> pauseStart;
    chrono::duration<int> lastTime;
    chrono::duration<int> winTime;
    Leaderboard l;
public:
    Board(int col, int row, int mines, string _name){
        cols = col;
        rows = row;
        name = _name;
        numMines = mines;
        numFlags = mines;
        tilesRemaining = cols*rows - numMines;
        win = false;
        lose = false;
        paused = false;
        debugMode = false;
        startTime = chrono::high_resolution_clock::now();
        time = chrono::duration<int>(0);
        lastTime = chrono::duration<int>(0);
        for(int m = 0; m < 11; m++){
            sf::Sprite dig(t.getTexture("digits"));
            dig.setTextureRect(sf::IntRect(m*21, 0, 21, 32));
            digits[m] = dig;
        }
        negcount = digits[10];
        negcount.setPosition(12, 32*(rows+0.5f)+16);
        flag.setTexture(t.getTexture("flag"));
        minetile.setTexture(t.getTexture("mine"));
        smileySprite.setTexture(t.getTexture("happy"));
        smileySprite.setPosition((cols/2.0)*32 - 32,(rows+0.5f)*32);
        winSprite.setTexture(t.getTexture("win"));
        winSprite.setPosition((cols/2.0)*32 - 32,(rows+0.5f)*32);
        loseSprite.setTexture(t.getTexture("lose"));
        loseSprite.setPosition((cols/2.0)*32 - 32,(rows+0.5f)*32);
        playSprite.setTexture(t.getTexture("play"));
        playSprite.setPosition(cols*32 - 240, (rows+0.5f) *32);
        pauseSprite.setTexture(t.getTexture("pause"));
        pauseSprite.setPosition(cols*32 - 240, (rows+0.5f) *32);
        debugSprite.setTexture(t.getTexture("debug"));
        debugSprite.setPosition(cols*32 - 304, (rows+0.5f) *32);
        leaderBoard.setTexture(t.getTexture("leader"));
        leaderBoard.setPosition(cols*32 - 176, (rows+0.5f) *32);
        vector<Tile> temp;
        for(int i = 0; i < rows; i++){
            temp.clear();
            for(int j = 0; j < cols; j++){
                Tile tile(t,i, j);
                temp.push_back(tile);
            }
            board.push_back(temp);
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                Tile& tile = board[i][j];
                for (int k = i-1; k <= i+1; k++) {
                    for (int l = j-1; l <= j+1; l++) {
                        if (k >= 0 && k < rows && l >= 0 && l < cols && (k != i || l != j)) {
                            Tile& adjTile = board[k][l];
                            tile.addAdjTile(&adjTile);
                        }
                    }
                }
            }
        }

        for(int j = 0; j < numMines; j++){
            int mRow = Random::Int(0, rows-1);
            int mCol = Random::Int(0, cols-1);
            if(board[mRow][mCol].mineTile()){
                j--;
            }
            else{
                board[mRow][mCol].setMine();
            }
        }
    }
    void resetBoard(){
        win = false;
        lose = false;
        debugMode = false;
        numFlags = numMines;
        startTime = chrono::high_resolution_clock::now();
        pauseStart = startTime;
        lastTime = chrono::seconds(0);
        paused = false;
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                board[i][j].reset();
            }
        }
        for(int k = 0; k < numMines; k++){
            int mRow = Random::Int(0, rows-1);
            int mCol = Random::Int(0, cols-1);
            if(board[mRow][mCol].mineTile()){
                k--;
            }
            else{
                board[mRow][mCol].setMine();
            }
        }
    }

    void drawBoard(sf::RenderWindow& window){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                window.draw(board[i][j].getSprite());
                if(win && board[i][j].mineTile()){
                    board[i][j].flag();
                    flag.setPosition(j*32, i *32);
                    window.draw(flag);
                    numFlags = 0;
                }
                else if(lose && board[i][j].mineTile()){
                    board[i][j].reveal();
                    window.draw(board[i][j].getSprite());
                    minetile.setPosition(j*32, i*32);
                    window.draw(minetile);
                }
                else if(debugMode && board[i][j].mineTile()){
                    minetile.setPosition(j*32, i*32);
                    window.draw(minetile);
                }
                else if(paused && !win && !lose){
                    window.draw(board[i][j].pauseMode());
                }
                else if(board[i][j].hasFlag() && !board[i][j].revealedtile()){
                    flag.setPosition(j*32, i*32);
                    window.draw(flag);
                }
                else if(board[i][j].mineTile() && board[i][j].revealedtile()){
                    minetile.setPosition(j*32, i*32);
                    window.draw(minetile);
                }
                else{
                    int num = board[i][j].getAdjMines();
                    if(board[i][j].revealedtile() && num != 0){
                        numTile.setTexture(t.getTexture("n" + to_string(num)));
                        numTile.setPosition(j*32, i*32);
                        window.draw(numTile);
                    }
                }
            }
        }
    }
    void updateBoard(int LoR, sf::RenderWindow& window, sf::Vector2i pos){
        int x = pos.x / 32;
        int y = pos.y / 32;
        if(LoR == 1){
            if(smileySprite.getGlobalBounds().contains(pos.x, pos.y)){
                resetBoard();
            }
            else if(pauseSprite.getGlobalBounds().contains(pos.x,pos.y)&& !win && !lose){
                pauseplay();
            }
            else if(debugSprite.getGlobalBounds().contains(pos.x, pos.y) && !paused && ! win && !lose){
                if (!debugMode){
                    debugMode = true;
                }
                else{
                    debugMode = false;
                }
            }
            else if(leaderBoard.getGlobalBounds().contains(pos.x, pos.y)){
                int num =0;
                if(!paused){
                    pauseplay();
                    num = 1;
                }
                drawBoard(window);
                window.display();
                l.display(cols, rows);
                if(num == 1){
                    pauseplay();
                }
            }
            else if(x < cols && y < rows && !paused && !board[y][x].hasFlag() && !win && !lose && !board[y][x].revealedtile()){
                board[y][x].reveal();
                if(!board[y][x].mineTile()){
                    if(checkWin()){
                        win = true;
                        pauseplay();
                        winTime = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - startTime);
                        l.updateLeaderboard(name, winTime.count());
                        l.display(cols, rows);
                    }
                }
                else{
                    lose = true;
                    pauseplay();
                }
            }
        }
        else if(LoR == 2){
            if (x < cols && y < rows && !board[y][x].revealedtile() && !paused && !win && !lose){
                if(board[y][x].hasFlag()){
                    board[y][x].removeflag();
                    numFlags++;
                }
                else{
                    board[y][x].flag();
                    numFlags--;
                }
            }
        }
    }
    void drawBottom(sf::RenderWindow& window){
        auto count1 = digits[abs(numFlags/10)];
        auto count2 = digits[abs(numFlags%10)];
        count1.setPosition(33, 32*(rows+0.5f)+16);
        count2.setPosition(54, 32*(rows+0.5f)+16);
        if(!win && !lose){
            window.draw(smileySprite);
        }
        else if(win){
            window.draw(winSprite);
        }
        else if(lose){
            window.draw(loseSprite);
        }
        if(paused && !win && !lose){
            window.draw(playSprite);
        }
        else{
            window.draw(pauseSprite);
        }
        if(numFlags < 0){
            window.draw(negcount);
        }
        window.draw(count1);
        window.draw(count2);
        window.draw(debugSprite);
        window.draw(leaderBoard);
    }
    void drawTimer(sf::RenderWindow& window){
        auto currentTime = chrono::high_resolution_clock::now() - startTime;
        if(paused){
            currentTime = lastTime;
        }
        time = chrono::duration_cast<chrono::seconds>(currentTime);
        int tens_minutes = (time.count() / 60) / 10;
        int minutes = (time.count() / 60) % 10;
        int tens_seconds = (time.count() % 60) / 10;
        int seconds = (time.count() % 60) % 10;
        sf::Sprite tens = digits[tens_minutes];
        tens.setPosition(cols * 32 - 97, 32 * (rows + 0.5f) + 16);
        sf::Sprite mins = digits[minutes];
        mins.setPosition(cols * 32 - 76, 32 * (rows + 0.5f) + 16);
        sf::Sprite tensec = digits[tens_seconds];
        tensec.setPosition(cols * 32 - 54, 32 * (rows + 0.5f) + 16);
        sf::Sprite secs = digits[seconds];
        secs.setPosition(cols * 32 - 33, 32 * (rows + 0.5f) + 16);
        window.draw(tens);
        window.draw(mins);
        window.draw(tensec);
        window.draw(secs);
    }
    void pauseplay(){
        if(!paused){
            paused = true;
            pauseStart = chrono::high_resolution_clock::now();
            lastTime = chrono::duration_cast<chrono::seconds>(pauseStart - startTime);
        }
        else{
            paused = false;
            auto now = chrono::high_resolution_clock::now();
            startTime += now - pauseStart;
        }
    }
    bool checkWin(){
        int numRevealed = 0;
        for(int i = 0; i < rows; i++){
            for(int j = 0; j<cols; j++){
                if(board[i][j].revealedtile()){
                    numRevealed +=1;
                }
            }
        }
        if(tilesRemaining == numRevealed){
            return true;
        }
        else{
            return false;
        }
    }
};
//very incomplete, testing rn
#endif //UNTITLED8_BOARD_H
