#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Gnode.hpp>

struct Gedge {
    Gnode* a; Gnode* b;
    int weight;
    sf::Color color;

    Gedge(Gnode& _a, Gnode& _b, int _weight = 1, const sf::Color& _color = silver) {
        a = &_a;
        b = &_b;
        weight = _weight;
        color = _color;
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

    sf::Vertex ends[2];
    sf::Text chars;
    void display() {
        ends[0].position = a->pos;
        ends[1].position = b->pos;
        ends[0].color = color;
        ends[1].color = color;
        
        chars.setFont(font);
        chars.setCharacterSize((2.0f * gnodesize - 10.0f) / (floor(log10(std :: max(1, abs(weight))))));
        chars.setFillColor({36, 36, 36});
        chars.setString(std::to_string(weight));
        chars.setPosition(0.5f * (ends[0].position + ends[1].position));

        window.draw(ends, 2, sf::Lines);
        window.draw(chars);
    }
};