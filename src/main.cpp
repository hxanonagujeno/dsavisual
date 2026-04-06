#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Controls.hpp>
#include <Data.hpp>
#include <Background.hpp>
#include <Structures.hpp>
#include <Codedisplay.hpp>

sf::RenderWindow window(sf::VideoMode(1080, 600), "DSAvisual", sf::Style::Titlebar | sf::Style::Close);
sf::Event event;
sf::Font font;

Background background;
Controls controls;
Data data;
Structures structures;
Codedisplay codedisplay;

void init() {
    srand(time(0));
    font.loadFromFile("assets/segoeui.ttf");
    font.setSmooth(0);
    background.init();
    data.import("assets/example.txt");
    structures.load(data);
    structuremode = 2;
    memset(buttonevent, 0, sizeof(buttonevent));
}

void check() {
    controls.check();
    data.check();
    structures.check();
    codedisplay.check();
}

void tick() {
    reglobe();
    controls.tick();
    data.tick();
    structures.tick();
    codedisplay.tick();
}

void display() {
    window.clear();
    background.display();
    controls.display();
    data.display();
    structures.display();
    codedisplay.display();
    
    window.display();
}

bool polled;
int main() {
    init();
    while (window.isOpen()) {
        polled = 0;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
            check();
            tick();
            display();
            polled = 1;
        }
        if (!polled) {
            tick();
            display();
        }
    }
    return 0;
}