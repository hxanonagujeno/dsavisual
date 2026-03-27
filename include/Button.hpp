#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <CustomDraws.hpp>

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
        color = Wwhite;
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
        if (animating || showsteps) return;
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
                text = "By step";
            } else {
                text = "All at once";
            }
            return;
        }
        if (id == 9) {
            text = (char)((int)animationtime + '0');
            text += '.';
            text += (char)(((int)(animationtime * 10)) % 10 + '0');
            text += (char)(((int)(animationtime * 100)) % 10 + '0');
            text += 'S';
            return;
        }
        if (2 <= id && id <= 7) {
            if (structuremode == id) {
                color = Wsilver;
            } else {
                color = Wwhite;
            }
        }
    }

    void tick() {
        tickspecials();
        if (animating || showsteps) {
            colormod = Wwhite - Wslate;
            hover = 0;
            click = 0;
            hold = 0;
            return;
        }
        colormod = nocolor;
        if (hover) {
            colormod = Wwhite - Wsilver;
            if (click) {
                colormod = Wwhite - Wslate;
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
        chars.setPosition(pos + 0.5f * (sz - sizes(chars.getLocalBounds())) - poses(chars.getLocalBounds()));
        chars.setFillColor(onyx);

        if (id == 1) {
            customButtonHighlight(box, Wcyan);
        } else {
            customButton(box);
        }
        window.draw(chars);
    }
};