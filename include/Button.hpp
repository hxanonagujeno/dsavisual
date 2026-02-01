#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

struct Button {
    sf::Vector2f pos;
    sf::Vector2f sz;
    sf::Color color;
    bool hover;
    bool click;

    Button() {
        pos = {0, 0};
        sz = {100, 100};
        hover = 0;
        click = 0;
    }

    sf::Vector2i mpos;
    void check() {
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
        color = {192, 192, 192};
        if (hover) {
            color = {160, 160, 160};
            if (click) {
                color = {128, 128, 128};
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