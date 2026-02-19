#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

struct Button {
    sf::Vector2f pos;
    sf::Vector2f sz;
    sf::Color color;
    std::string text;
    int id;
    int fontsz;
    bool hover;
    bool click;
    bool hold;
    sf::Color colormod;

    Button(const sf::Vector2f& _pos = zero2f, const sf::Vector2f& _sz = sf::Vector2f{100.0f, 100.0f}, const std::string& _text = "", int _id = 0, int _fontsz = -1) {
        pos = _pos;
        sz = _sz;
        color = silver;
        text = _text;
        id = _id;
        hover = 0;
        click = 0;
        hold = 0;
        fontsz = _fontsz;
        colormod = nocolor;
    }

    sf::Vector2i mpos;
    void check() {
        if (animating) return;
        mpos = sf::Mouse::getPosition(window);
        hover = 0;
        click = 0;
        if (pos.x <= mpos.x && mpos.x < pos.x + sz.x && pos.y <= mpos.y && mpos.y < pos.y + sz.y) {
            hover = 1;
            if (!hold && event.type == sf::Event::MouseButtonPressed) {
                click = 1;
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                hold = 0;
            }
        }
    }

    void tickspecials() {
        if (id == 8) {
            if (stepbystep) {
                if (text.back() == 'F') {
                    text.erase(text.end() - 2, text.end());
                    text += 'N';
                }
            } else {
                if (text.back() == 'N') {
                    text.pop_back();
                    text += "FF";
                }
            }
            return;
        }
        if (2 <= id && id <= 7) {
            if (structuremode == id) {
                color = slate;
            } else {
                color = silver;
            }
        }
    }

    void tick() {
        tickspecials();
        if (animating) {
            colormod = silver - gray;
            hover = 0;
            click = 0;
            hold = 0;
            return;
        }
        colormod = nocolor;
        if (hover) {
            colormod = silver - slate;
            if (click) {
                colormod = silver - gray;
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
        box.setFillColor(color - colormod);

        chars.setFont(font);
        chars.setCharacterSize(fontsz > 0? fontsz: (1.2f * sz.x) / (int)text.size());
        chars.setString(text);
        chars.setPosition(pos - 0.5f * sizes(chars.getLocalBounds()) - poses(chars.getLocalBounds()) + 0.5f * sz);
        chars.setFillColor(onyx);

        window.draw(box);
        window.draw(chars);
    }
};