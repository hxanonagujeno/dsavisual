#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>

struct Gnode {
    sf::Vector2f pos;
    sf::Color color;
    std::string text;
    bool focus;
    int id;

    Gnode(const std::string& _text = "", const sf::Vector2f& _pos = zero2f, const sf::Color& _color = silver) {
        pos = _pos;
        color = _color;
        text = _text;
        focus = 0;
        id = rani();
    }

    void copy(const Gnode& x, bool copyid = 1) {
        pos = x.pos;
        color = x.color;
        text = x.text;
        if (copyid) id = x.id;
    }

    sf::Vector2i mpos;
    sf::Vector2i mdis;
    void check() {
        mpos = sf::Mouse::getPosition(window);
        if (focus) {
            if (event.type == sf::Event::MouseButtonReleased) {
                focus = 0;
            }
            return;
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            mdis = mpos - sf::Vector2i(pos);
            if (sqrlen(mdis) <= sqr(gnodesize)) {
                focus = 1;
            }
        }
    }

    void tick() {
        if (focus) {
            pos = sf::Vector2f(mpos - mdis);
        }
        mxz(pos.x, 240.0f + gnodesize);
        mnz(pos.x, 720.0f - gnodesize);
        mxz(pos.y, 0.000f + gnodesize);
        mnz(pos.y, 480.0f - gnodesize);
    }

    sf::CircleShape box;
    sf::Text chars;
    void display() {
        box.setOrigin({1.0f * gnodesize, 1.0f * gnodesize});
        box.setPosition(pos);
        box.setRadius(gnodesize);
        box.setFillColor(color);
        
        chars.setFont(font);
        chars.setCharacterSize((2.0f * gnodesize - 10.0f) / text.size());
        chars.setFillColor({36, 36, 36});
        chars.setString(text);
        chars.setPosition(pos + sf::Vector2f{0.0f, -2.0f} - 0.5f * sizes(chars.getLocalBounds()));

        window.draw(box);
        window.draw(chars);
    }
};