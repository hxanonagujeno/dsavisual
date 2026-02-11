#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

struct Button {
    sf::Vector2f pos;
    sf::Vector2f sz;
    sf::Color color;
    std::string text;
    int id;
    bool hover;
    bool click;
    bool hold;

    Button(const sf::Vector2f& _pos = zero2f, const sf::Vector2f& _sz = sf::Vector2f{100.0f, 100.0f}, const std::string& _text = "", int _id = 0) {
        pos = _pos;
        sz = _sz;
        text = _text;
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
        color = silver;
        if (hover) {
            color = slate;
            if (click) {
                color = gray;
                if (!hold) {
                    buttonevent[id] = 1;
                }
                hold = 1;
            }
        }
    }

    sf::RectangleShape box;
    sf::Text chars;
    void display() {
        box.setPosition(pos);
        box.setSize(sz);
        box.setFillColor(color);

        chars.setFont(font);
        chars.setCharacterSize((1.0f * sz.x - 10.0f) / text.size());
        chars.setString(text);
        chars.setPosition(pos - 0.5f * sizes(chars.getLocalBounds()) - poses(chars.getLocalBounds()) + 0.5f * sz);
        chars.setFillColor(onyx);

        window.draw(box);
        window.draw(chars);
    }
};