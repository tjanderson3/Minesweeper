#ifndef UNTITLED8_TILES_H
#define UNTITLED8_TILES_H
#include <vector>
#include "textures.h"

class Tile{
private:
    bool hasMine;
    bool flagged;
    bool revealed;
    vector<Tile*> adjTiles;
    sf::Sprite sprite;
    sf::Sprite tilerev;
    sf::Sprite minetile;
    int row;
    int col;
public:
    Tile(TextureManager& textures, int row, int col){
        hasMine = false;
        flagged = false;
        revealed = false;
        adjTiles = vector<Tile*>();
        sprite.setTexture(textures.getTexture("hidden"));
        tilerev.setTexture(textures.getTexture("reveal"));
        minetile.setTexture(textures.getTexture("mine"));
        this->col = col;
        this->row = row;
        tilerev.setPosition(col*32, row *32);
        sprite.setPosition(col*32, row*32);
    }
    void addAdjTile(Tile* t){
        adjTiles.push_back(t);
    }
    int getAdjMines(){
        int adjMines = 0;
        for(auto& adjTile : adjTiles){
            if(adjTile->mineTile()){
                adjMines++;
            }
        }
        return adjMines;
    }
    sf::Sprite getSprite(){
        if(revealed){
            return tilerev;
        }
        else{
            return sprite;
        }
    }
    sf::Sprite pauseMode(){
        return tilerev;
    }
    void reveal(){
        revealed = true;
        if(hasMine){
            return;
        }
        else if(this->getAdjMines()==0){
            for(auto tile : adjTiles){
                if(!tile->hasMine && !tile->revealed){
                    tile->reveal();
                }
            }
        }
    }
    void hide(){
        revealed = false;
    }
    void flag(){
        flagged= true;
    }
    void removeflag(){
        flagged = false;
    }
    void setMine(){
        hasMine = true;
    }
    bool mineTile() const{
        return hasMine;
    }
    bool revealedtile() const{
        return revealed;
    }
    bool hasFlag() const{
        return flagged;
    }
    void reset(){
        hasMine = false;
        flagged = false;
        revealed = false;
    }
};

#endif //UNTITLED8_TILES_H
