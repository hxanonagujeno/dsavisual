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
    void display() {
        sf::Vector2f ab = b->pos - a->pos;
        float len = gedgesize / sqrtl(ab.x * ab.x + ab.y * ab.y);
        sf::Vector2f normal = sf::Vector2f(-ab.y * len, ab.x * len);
        tline.setPoint(0, a->pos + normal);
        tline.setPoint(1, a->pos - normal);
        tline.setPoint(2, b->pos - normal);
        tline.setPoint(3, b->pos + normal);
        tline.setFillColor(color);
        
        chars.setFont(font);
        chars.setCharacterSize((2.0f * gnodesize - 10.0f) / (floor(log10(std :: max(1, abs(weight))))));
        chars.setFillColor(onyx);
        chars.setString(std::to_string(weight));
        chars.setPosition(0.5f * (a->pos + b->pos));

        window.draw(tline);
        window.draw(chars);
    }
};