#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

struct Button {
    sf::Vector2f pos;
    sf::Vector2f sz;
    sf::Color color;
    int id;
    bool hover;
    bool click;
    bool hold;

    Button(const sf::Vector2f& _pos = zero2f, const sf::Vector2f& _sz = sf::Vector2f{100.0f, 100.0f}, int _id = 0) {
        pos = _pos;
        sz = _sz;
        id = _id;
        hover = 0;
        click = 0;
        hold = 0;
    }

    sf::Vector2i mpos;
    void check() {
        mpos = sf::Mouse::getPosition(window);
        hover = 0;
        click = 0;
        if (pos.x <= mpos.x && mpos.x <= pos.x + sz.x && pos.y <= mpos.y && mpos.y <= pos.y + sz.y) {
            hover = 1;
            if (!hold && event.type == sf::Event::MouseButtonPressed) {
                click = 1;
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                hold = 0;
            }
        }
    }

    void tick() {
        color = {192, 192, 192};
        if (hover) {
            color = {160, 160, 160};
            if (click) {
                color = {128, 128, 128};
                if (!hold) {
                    buttonevent[id] = 1;
                }
                hold = 1;
            }
        }
    }

    sf::RectangleShape box;
    void display() {
        box.setPosition(pos);
        box.setSize(sz);
        box.setFillColor(color);
        window.draw(box);
    }
};