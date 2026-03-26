#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <CustomDraws.hpp>

struct Gnode {
    sf::Vector2f pos;
    sf::Color color;
    std::string text;
    bool focus;
    int id;

    Gnode(const std::string& _text = "", const sf::Vector2f& _pos = zero2f, const sf::Color& _color = defnodecol) {
        pos = _pos;
        color = _color;
        text = _text;
        focus = 0;
        id = rani();
    }

    Gnode(const Gnode& x) {
        pos = x.pos;
        color = x.color;
        text = x.text;
        focus = x.focus;
        id = x.id;
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
        mnz(pos.x, 840.0f - gnodesize);
        mxz(pos.y, 0.000f + gnodesize);
        mnz(pos.y, 600.0f - gnodesize);
    }

    sf::CircleShape box;
    sf::Text chars;
    void display() {
        box.setRadius(gnodesize);
        box.setOrigin({1.0f * gnodesize, 1.0f * gnodesize});
        box.setPosition(pos);
        box.setFillColor(color);
        
        chars.setFont(font);
        chars.setCharacterSize(std::max(9.0f, (4.0f * gnodesize) / (3 + (int)text.size())));
        chars.setString(text);
        chars.setPosition(pos - 0.5f * sizes(chars.getLocalBounds()) - poses(chars.getLocalBounds()));
        chars.setFillColor(onyx);

        customNode(box);
        window.draw(chars);
    }
};