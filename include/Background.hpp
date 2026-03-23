#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>

struct Background {
    sf::RectangleShape graphpanel;
    sf::RectangleShape controlpanel;
    sf::RectangleShape infopanel;
    sf::RectangleShape separator;

    Background() {
        controlpanel.setSize({240, 600});
        controlpanel.setPosition({0, 0});
        controlpanel.setFillColor(Wwhite);
        graphpanel.setSize({600, 600});
        graphpanel.setPosition({240, 0});
        graphpanel.setFillColor(sf::Color::White);
        separator.setSize({1, 600});
        separator.setPosition({240, 0});
        separator.setFillColor(Wsilver);
    }
    
    void display() {
        window.clear();
        window.draw(controlpanel);
        window.draw(graphpanel);
        window.draw(separator);
    }
};