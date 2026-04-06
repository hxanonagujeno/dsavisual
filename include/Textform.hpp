#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>

struct Textform {
    sf::Vector2f pos;
    sf::Vector2f sz;
    sf::Color color;
    bool focus;
    std::string text;
    int lim;
    char buf;

    Textform(const sf::Vector2f& _pos = zero2f, const std::string& _text = "") {
        pos = _pos;
        sz = {196, 15};
        focus = 0;
        lim = 18;
        text = _text;
        buf = 0;
    }

    sf::Vector2i mpos;
    void checkfocus() {
        mpos = sf::Mouse::getPosition(window);
        if (event.type == sf::Event::MouseButtonPressed) {
            if (pos.x <= mpos.x && mpos.x < pos.x + sz.x && pos.y <= mpos.y && mpos.y < pos.y + sz.y) {
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
        if (animating || showsteps) return;
        checkfocus();
        checktype();
    }

    void tickcolor() {
        if (focus) {
            color = Wivory;
        } else {
            color = sf::Color::White;
        }
    }

    void ticktext() {
        if (buf == 0) return;
        if (buf == -1) {
            if (text.size()) {
                text.pop_back();
                keyboardvis[sf::Keyboard::Backspace] = 1;
            }
            buf = 0;
            return;
        }
        if ((int)text.size() >= 24 || (chars.setString(text + buf), chars.getLocalBounds().getSize().x >= sz.x)) {
            buf = 0;
            return;
        }
        if (buf == ' ') {
            if (!text.empty() && text.back() != ' ') {
                text += ' ';
            }
            buf = 0;
            return;
        }
        text += buf;
        buf = 0;
        return;
    }

    void tick() {
        if (animating || showsteps) {
            color = Wsilver;
            return;
        }
        tickcolor();
        ticktext();
    }

    sf::RectangleShape box;
    sf::Text chars;
    void display() {
        box.setPosition(pos);
        box.setSize(sz);
        box.setFillColor(color);
        
        chars.setPosition(pos + sf::Vector2f{1.0f, -1.0f});
        chars.setFont(font);
        chars.setCharacterSize(12);
        chars.setFillColor(onyx);
        chars.setString(text);
        
        window.draw(box);
        window.draw(chars);
    }
};