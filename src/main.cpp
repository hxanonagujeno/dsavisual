#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Button.hpp>
#include <Textform.hpp>

sf::RenderWindow window(sf::VideoMode(720, 480), "dsavisual", sf::Style::Titlebar | sf::Style::Close);
sf::Event event;
sf::Font font;

Button button;
Textform textform;

void init() {
    font.loadFromFile("assets/segoeui.ttf");
}

void check() {
    button.check();
    textform.check();
}

void tick() {
    button.tick();
    textform.tick();
}

void display() {
    window.clear();
    button.display();
    textform.display();
    window.display();
}

int main() {
    init();
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
            check();
            tick(); 
            display(); 
        }   
    }
    return 0;
}