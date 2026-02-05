#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Button.hpp>
#include <Controls.hpp>
#include <Textform.hpp>
#include <Data.hpp>
#include <Graph.hpp>

sf::RenderWindow window(sf::VideoMode(720, 480), "dsavisual", sf::Style::Titlebar | sf::Style::Close);
sf::Event event;
sf::Font font;

Controls controls;
Data data;
Graph graph;

void init() {
    srand(time(0));
    font.loadFromFile("assets/segoeui.ttf");
}

void check() {
    controls.check();
    data.check();
    graph.check();
}

void tick() {
    controls.tick();
    data.tick();
    graph.tick();
}

void display() {
    window.clear();
    controls.display();
    data.display();
    graph.display();
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