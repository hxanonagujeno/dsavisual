#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

struct Textform {
    sf::Vector2f pos;
    sf::Vector2f sz;
    sf::Color color;
    bool focus;
    std::string text;
    int lim;
    char buf;

    Textform(const sf::Vector2f &_pos = sf::Vector2f{0.f, 0.f}) {
        pos = _pos;
        sz = {200, 20};
        focus = 0;
        lim = 1.2f * sz.x / sz.y - 1;
        text = "";
    }

    sf::Vector2i mpos;
    void checkfocus() {
        mpos = sf::Mouse::getPosition(window);
        if (event.type == sf::Event::MouseButtonPressed) {
            if (pos.x <= mpos.x && mpos.x <= pos.x + sz.x && pos.y <= mpos.y && mpos.y <= pos.y + sz.y) {
                focus = 1;
            } else {
                focus = 0;
            }
        }
    }

    void checktype() {
        buf = 0;
        if (!focus) return;
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Backspace) {
                buf = -1;
                return;
            }
        }
        if (event.type == sf::Event::TextEntered) {
            char x = static_cast<char>(event.text.unicode);
            if (std::isdigit(x) || std::isalpha(x) || x == ' ') {
                if (std::islower(x)) {
                    x += 'A' - 'a';
                }
                buf = x;
            }
            return;
        }
    }

    void check() {
        checkfocus();
        checktype();
    }

    void tickcolor() {
        if (focus) {
            color = {210, 210, 210};
        } else {
            color = {240, 240, 240};
        }
    }

    void ticktext() {
        if (buf == 0) return;
        if (buf == -1) {
            if (text.size()) {
                text.pop_back();
            }
            return;
        }
        if ((int)text.size() == lim) return;
        if (buf == ' ') {
            if (!text.empty() && text.back() != ' ') {
                text += ' ';
            }
            return;
        }
        text += buf;
        return;
    }

    void tick() {
        tickcolor();
        ticktext();
    }

    void display() {
        sf::RectangleShape box;
        box.setPosition(pos);
        box.setSize(sz);
        box.setFillColor(color);
        sf::Text chars;
        chars.setPosition(pos + sf::Vector2f{0.0f, -2.0f});
        chars.setFont(font);
        chars.setCharacterSize(sz.y);
        chars.setFillColor({36, 36, 36});
        chars.setString(text);
        window.draw(box);
        window.draw(chars);
    }
};