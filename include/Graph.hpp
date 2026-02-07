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

    void randomize() {
        std::cerr << "RANDOMIZE() CALLED" << std::endl;
        gnodes.clear();
        gedges.clear();
        int N = rani(2, 6);
        int M = rani(0, rani(1, N * (N - 1) / 2));
        for (int i = 1; i <= N; i++) {
            int x = rani(240 + gnodesize, 720 - gnodesize), y = rani(gnodesize, 480 - gnodesize);
            gnodes.emplace_back(std::to_string(i), sf::Vector2f{1.0f * x, 1.0f * y});
        }
        for (int i = 1; i <= M; i++) {
            gedges.emplace_back(gnodes[rani(0, N - 1)], gnodes[rani(0, N - 1)]);
        }
        std::cerr << N << " " << M << std::endl;
    }
};