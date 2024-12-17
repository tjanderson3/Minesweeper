#ifndef UNTITLED8_LEADERBOARD_H
#define UNTITLED8_LEADERBOARD_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

class Leaderboard{
private:
    struct boardData{
        string name;
        int minutes;
        int seconds;
    };
    sf::Font font;
    vector<boardData> boardList;
    bool isOpen;
public:
    Leaderboard(){
        isOpen = false;
        font.loadFromFile("files/font.ttf");
        ifstream file("files/leaderboard.txt");
        string singleLine;
        while(getline(file, singleLine)){
            istringstream stream(singleLine);
            string t, n;
            getline(stream, t, ',');
            getline(stream, n, ',');
            int minutes = stoi(t.substr(0, 2));
            int seconds = stoi(t.substr(3,2));
            boardData data = {n, minutes, seconds};
            boardList.push_back(data);
        }
    }
    void updateLeaderboard(string name, int time){
        boardData data ={name+"*", time/60, time%60};
        boardList.push_back(data);
        sort(boardList.begin(), boardList.end(), [](boardData& a, boardData& b){return (a.minutes *60 + a.seconds)< (b.minutes*60 +b.seconds);});
        boardList.pop_back();
        saveLeaderboard();
    }
    void saveLeaderboard(){
        ofstream file("files/leaderboard.txt");
        for(auto& i :boardList){
            file << setfill('0') << setw(2) << i.minutes << ":"<< setfill('0') << setw(2) << i.seconds << "," << i.name << "\n";
        }
    }
    void display(int cols, int rows){
        int width = cols*16;
        int height = rows *16 +50;
        sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);
        sf::Text header_text("LEADERBOARD", font, 20);
        header_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        sf::FloatRect header_rect = header_text.getLocalBounds();
        header_text.setOrigin(header_rect.left + header_rect.width/2.0f,header_rect.top  + header_rect.height/2.0f);
        header_text.setPosition(width/2.0f, height/2.0f - 120);
        string dataText;
        stringstream ss;
        for(int i =0; i < 5; i++){
            ss << i+1 << "." << "\t" << setfill('0') << setw(2) << to_string(boardList[i].minutes) << ":" << setfill('0')<<setw(2)<< to_string(boardList[i].seconds) << "\t" << boardList[i].name << "\n\n";
        }
        dataText = ss.str();
        sf::Text leaderboardText(dataText, font, 18);
        leaderboardText.setStyle(sf::Text::Bold);
        leaderboardText.setFillColor(sf::Color::White);
        sf::FloatRect textRect = leaderboardText.getLocalBounds();
        leaderboardText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        leaderboardText.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f + 20));
        while (window.isOpen()){
            isOpen = true;
            sf::Event event;
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed) {
                    window.close();
                    isOpen = false;
                }
            }
            window.clear(sf::Color::Blue);
            window.draw(header_text);
            window.draw(leaderboardText);
            window.display();
        }
    }
    bool opened(){
        return isOpen;
    }
};



#endif //UNTITLED8_LEADERBOARD_H
