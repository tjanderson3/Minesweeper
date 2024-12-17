#ifndef UNTITLED8_TEXTURES_H
#define UNTITLED8_TEXTURES_H
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class TextureManager{
private:
    map<string, sf::Texture> textures;
public:
    TextureManager(){
        sf::Texture debug, digits, happy, lose, win, flag, leader, mine, hidden, reveal, n1, n2, n3, n4, n5, n6, n7, n8, pause, play;
        debug.loadFromFile("files/images/debug.png");
        textures["debug"] = debug;
        digits.loadFromFile("files/images/digits.png");
        textures["digits"] = digits;
        happy.loadFromFile("files/images/face_happy.png");
        textures["happy"] = happy;
        lose.loadFromFile("files/images/face_lose.png");
        textures["lose"] = lose;
        win.loadFromFile("files/images/face_win.png");
        textures["win"] = win;
        flag.loadFromFile("files/images/flag.png");
        textures["flag"] = flag;
        leader.loadFromFile("files/images/leaderboard.png");
        textures["leader"] = leader;
        mine.loadFromFile("files/images/mine.png");
        textures["mine"] = mine;
        hidden.loadFromFile("files/images/tile_hidden.png");
        textures["hidden"] = hidden;
        reveal.loadFromFile("files/images/tile_revealed.png");
        textures["reveal"] = reveal;
        n1.loadFromFile("files/images/number_1.png");
        textures["n1"] = n1;
        n2.loadFromFile("../files/images/number_2.png");
        textures["n2"] = n2;
        n3.loadFromFile("files/images/number_3.png");
        textures["n3"] = n3;
        n4.loadFromFile("files/images/number_4.png");
        textures["n4"] = n4;
        n5.loadFromFile("files/images/number_5.png");
        textures["n5"] = n5;
        n6.loadFromFile("files/images/number_6.png");
        textures["n6"] = n6;
        n7.loadFromFile("files/images/number_7.png");
        textures["n7"] = n7;
        n8.loadFromFile("files/images/number_8.png");
        textures["n8"] = n8;
        play.loadFromFile("files/images/play.png");
        textures["play"] = play;
        pause.loadFromFile("files/images/pause.png");
        textures["pause"] = pause;
    }
    sf::Texture& getTexture(const string& name){
        return textures[name];
    }
};


#endif //UNTITLED8_TEXTURES_H
