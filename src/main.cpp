#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Button.hpp>
#include <Controls.hpp>
#include <Textform.hpp>
#include <Data.hpp>
#include <Graph.hpp>
#include <Animations.hpp>
#include <Background.hpp>

sf::RenderWindow window(sf::VideoMode(720, 480), "dsavisual", sf::Style::Titlebar | sf::Style::Close);
sf::Event event;
sf::Font font;

Background background;
Controls controls;
Data data;
Graph graph;
Graph graph2;
Animations animations;

void init() {
    srand(time(0));
    font.loadFromFile("assets/segoeui.ttf");
    graph.randomize();
    graph2.randomize();
    for (int i = 0; i < std::min((int)graph.gnodes.size(), (int)graph2.gnodes.size()); i++) {
        graph2.gnodes[i].id = graph.gnodes[i].id;
    }
}

void check() {
    controls.check();
    data.check();
    graph.check();
    graph2.check();
}

void tick() {
    controls.tick();
    data.tick();
    graph.tick();
    graph2.tick();
    if (rand() & 1) {
        animations.tick(graph, graph2, 2.0f);
    } else {
        animations.tick(graph2, graph, 2.0f);
    }
}

void display() {
    window.clear();
    background.display();
    controls.display();
    data.display();
    if (animating) {
        animations.display();
    } else {
        graph.display();
        graph2.display();
    }
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