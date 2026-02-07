#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Gnode.hpp>

struct Gedge {
    Gnode* a; Gnode* b;
    int weight;
    sf::Color color;
    int id;

    Gedge(Gnode& _a, Gnode& _b) {
        a = &_a, b = &_b;
        weight = 1;
        color = {128, 128, 128};
        ends[0].color = {36, 36, 36};
        ends[1].color = {36, 36, 36};
        id = rani();
    }

    void copy(const Gedge &x, bool copyid = 1) {
        a = x.a;
        b = x.b;
        weight = x.weight;
        color = x.color;
        if (copyid) id = x.id;
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
        
        chars.setFont(font);
        chars.setCharacterSize((2.0f * gnodesize - 10.0f) / (floor(log10(std :: max(1, abs(weight))))));
        chars.setFillColor({36, 36, 36});
        chars.setString(std::to_string(weight));
        chars.setPosition(0.5f * (ends[0].position + ends[1].position));

        window.draw(ends, 2, sf::Lines);
        window.draw(chars);
    }
};