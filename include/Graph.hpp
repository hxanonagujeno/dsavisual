#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Gnode.hpp>
#include <Gedge.hpp>

struct Graph {
    std::vector<Gnode> gnodes;
    std::vector<Gedge> gedges;

    Graph() {
        gnodes.emplace_back(std::to_string(1), sf::Vector2f{150, 150});
        gnodes.emplace_back(std::to_string(2), sf::Vector2f{200, 200});
        gedges.emplace_back(gnodes[0], gnodes[1]);
    }
    
    void checkgnodes() {
        for (Gnode& t: gnodes) {
            t.check();
            if (t.focus) {
                break;
            }
        }
    }

    void check() {
        checkgnodes();
    }

    void tick() {
        for (Gnode& t: gnodes) {
            t.tick();
        }
        for (Gedge& t: gedges) {
            t.tick();
        }
    }

    void display() {
        for (Gnode& t: gnodes) {
            t.display();
        }
        for (Gedge& t: gedges) {
            t.display();
        }
    }
};