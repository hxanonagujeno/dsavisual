#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

struct button {
    sf::Vector2f pos;
    sf::Vector2f sz;
    sf::Color color;
    bool hover;
    bool click;
    button() {
        pos = {0, 0};
        sz = {100, 100};
        color = {64, 64, 64};
        hover = 0;
        click = 0;
    }
    sf::Vector2i mpos;
    void checkMouse() {
        mpos = sf::Mouse::getPosition(window);
        hover = 0;
        click = 0;
        if (pos.x <= mpos.x && mpos.x <= pos.x + sz.x && pos.y <= mpos.y && mpos.y <= pos.y + sz.y) {
            hover = 1;
            if (event.type == sf::Event::MouseButtonPressed) {
                click = 1;
            }
        }
    }
    void tick() {
        color = {67, 67, 67};
        if (hover) {
            color = {57, 57, 57};
            if (click) {
                color = {47, 47, 47};
            }
        }
    }
    void display() {
        sf::RectangleShape box;
        box.setPosition(pos);
        box.setSize(sz);
        box.setFillColor(color);
        window.draw(box);
    }
};