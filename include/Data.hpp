#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Textform.hpp>
#include <Globals.hpp>

struct Data {
    std::vector<Textform> textforms;
    bool focus;
    bool add;
    bool del;

    Data() {
        textforms.emplace_back(sf::Vector2f{0.0f, 100.0f});
        focus = 0;
        add = 0;
        del = 0;
    }

    void checktextforms() {
        focus = 0;
        for (Textform& t: textforms) {
            t.check();
            focus |= t.focus;
        }
    }

    void checkkey() {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                add = 1;
                return;
            }
            if (event.key.code == sf::Keyboard::Delete) {
                del = 1;
                return;
            }
        }
    }

    void check() {
        checktextforms();
        checkkey();
    }

    void tick() {
        for (Textform& t: textforms) {
            t.tick();
        }
        if (!focus) return;
        if (add) {
            textforms.emplace_back(sf::Vector2f{0.0f, 100.0f + 20.0f * textforms.size()});
            add = 0;
            return;
        }
        if (del) {
            textforms.pop_back();
            del = 0;
            return;
        }
    }

    void display() {
        for (Textform& t: textforms) {
            t.display();
        }
    }
};