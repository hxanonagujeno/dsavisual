#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>

struct Background {
    sf::RectangleShape graphpanel;
    sf::RectangleShape controlpanel;
    sf::RectangleShape infopanel;
    std::vector<sf::RectangleShape> separators;

    Background() {
        controlpanel.setSize({240, 600});
        controlpanel.setPosition({0, 0});
        controlpanel.setFillColor(Wwhite);
        graphpanel.setSize({600, 600});
        graphpanel.setPosition({240, 0});
        graphpanel.setFillColor(sf::Color::White);
        infopanel.setSize({240, 600});
        infopanel.setPosition({840, 0});
        infopanel.setFillColor(Wwhite);
        separators.resize(2);
        separators[0].setSize({1, 600});
        separators[0].setPosition({240, 0});
        separators[0].setFillColor(Wsilver);
        separators[1].setSize({1, 600});
        separators[1].setPosition({840, 0});
        separators[1].setFillColor(Wsilver);
    }
    
    void display() {
        window.clear();
        window.draw(controlpanel);
        window.draw(graphpanel);
        window.draw(infopanel);
        for (const auto& separator: separators) {
            window.draw(separator);
        }
    }
};