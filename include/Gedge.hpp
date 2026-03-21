#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Gnode.hpp>

struct Gedge {
    Gnode* a; Gnode* b;
    int weight;
    sf::Color color;

    Gedge(Gnode& _a, Gnode& _b, int _weight = 1, const sf::Color& _color = charcoal) {
        a = &_a;
        b = &_b;
        weight = _weight;
        color = _color;
        tline.setPointCount(4);
        chars.setFont(font);
        chars.setFillColor(onyx);
    }

    void copy(const Gedge &x) {
        a = x.a;
        b = x.b;
        weight = x.weight;
        color = x.color;
    }

    void check() {
    }

    void tick() {
    }

    sf::ConvexShape tline;
    sf::Text chars;
    float charsize;
    void display() {
        sf::Vector2f ab = b->pos - a->pos;
        float len = gedgesize / sqrtl(ab.x * ab.x + ab.y * ab.y);
        sf::Vector2f normal = sf::Vector2f(-ab.y * len, ab.x * len);
        tline.setPoint(0, a->pos + normal);
        tline.setPoint(1, a->pos - normal);
        tline.setPoint(2, b->pos - normal);
        tline.setPoint(3, b->pos + normal);
        tline.setFillColor(color);
        window.draw(tline);

        if (structuremode != 6 && structuremode != 7) return;
        charsize = (3 * gnodesize - 10.0f) / (3 + floor(log10(std :: max(1, abs(weight)))));
        chars.setCharacterSize(charsize);
        chars.setString(std::to_string(weight));
        chars.setOrigin(0.5f * sizes(chars.getLocalBounds()));
        chars.setPosition(0.5f * (a->pos + b->pos) + charsize * (normal.y < 0? 1: -1) * normal);
        window.draw(chars);
    }
};