#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include "textures.h"
#include "board.h"

using namespace std;

class WelcomeWindow{
    unsigned int height;
    unsigned int width;
    sf::Font font;
    string _playerName;
public:
    string getName(){
        return _playerName;
    }
    WelcomeWindow(const string& cols, const string& rows){
        int col_num = stoi(cols);
        int row_num = stoi(rows);
        width = col_num * 32;
        height = (row_num *32) + 100;
        sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);
        font.loadFromFile("files/font.ttf");
        sf::Text header_text("WELCOME TO MINESWEEPER!", font, 24);
        header_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        sf::FloatRect header_rect = header_text.getLocalBounds();
        header_text.setOrigin(header_rect.left + header_rect.width/2.0f,header_rect.top  + header_rect.height/2.0f);
        header_text.setPosition(width/2.0f, height/2.0f - 150);
        sf::Text instr_text("Enter your name:", font, 20);
        instr_text.setStyle(sf::Text::Bold);
        sf::FloatRect instr_rect = instr_text.getLocalBounds();
        instr_text.setOrigin(instr_rect.left + instr_rect.width/2.0f, instr_rect.top + instr_rect.height/2.0f);
        instr_text.setPosition(width/2.0f, height/2.0f - 75);
        sf::Text user_text("|", font, 18);
        user_text.setFillColor(sf::Color::Yellow);
        user_text.setStyle(sf::Text::Bold);
        string playerName;
        while(window.isOpen()){
            sf::Event events;
            while(window.pollEvent(events)){
                if(events.type == sf::Event::Closed){
                    window.close();
                }
                else if(events.type == sf::Event::TextEntered && playerName.size() < 10){
                    if(isalpha(events.text.unicode)){
                        char letter = (char)(events.text.unicode);
                        playerName += letter;
                        user_text.setString(playerName + "|");
                    }
                }
                else if(events.type == sf::Event::KeyPressed){
                    if(events.key.code == sf::Keyboard::BackSpace && !playerName.empty()){
                        playerName.pop_back();
                        user_text.setString(playerName + "|");
                    }
                    else if(events.key.code ==sf::Keyboard::Enter && !playerName.empty()){
                        playerName[0] = toupper(playerName[0]);
                        for(int i = 1; i < playerName.size(); i++){
                            playerName[i] = tolower(playerName[i]);
                        }
                        window.close();
                        _playerName = playerName;
                    }
                }
            }
            sf::FloatRect user_rect = user_text.getLocalBounds();
            user_text.setOrigin(user_rect.left + user_rect.width/2.0f,user_rect.top  + user_rect.height/2.0f);
            user_text.setPosition(width/2.0f, height/2.0f - 45);
            window.clear(sf::Color::Blue);
            window.draw(header_text);
            window.draw(instr_text);
            window.draw(user_text);

            window.display();
        }
    }
};



int main()
{
    ifstream board_spec("files/board_config.cfg");
    string cols;
    string rows;
    string mines;
    getline(board_spec, cols);
    getline(board_spec, rows);
    getline(board_spec, mines);
    WelcomeWindow t = WelcomeWindow(cols, rows);
    if(!t.getName().empty()) {
        sf::RenderWindow window(sf::VideoMode(stoi(cols)
        *32, (stoi(rows) * 32) + 100), "Minesweeper", sf::Style::Close);
        window.clear(sf::Color::White);
        Board board(stoi(cols), stoi(rows), stoi(mines), t.getName());


        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::MouseButtonPressed) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        board.updateBoard(1, window, sf::Mouse::getPosition(window));
                    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                        board.updateBoard(2, window, sf::Mouse::getPosition(window));
                    }
                }
            }
            window.clear(sf::Color::White);
            board.drawBoard(window);
            board.drawBottom(window);
            board.drawTimer(window);
            window.display();
        }
    }
    return 0;
}
