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
        gnodes.clear();
        gedges.clear();
    }
    
    void checkgnodes() {
        if (animating) return;
        for (auto t = gnodes.rbegin(); t != gnodes.rend(); t++) {
            t->check();
            if (t->focus) break;
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
        for (Gedge& t: gedges) {
            t.display();
        }
        for (Gnode& t: gnodes) {
            if (t.color == orange) {
                std::cout << "wow" << std::endl;
            }
            t.display();
        }
    }

    void randomize() {
        gnodes.clear();
        gedges.clear();
        int n = rani(2, 6);
        int m = rani(0, rani(1, n * (n - 1) / 2));
        for (int i = 1; i <= n; i++) {
            int x = rani(240 + gnodesize, 720 - gnodesize), y = rani(gnodesize, 480 - gnodesize);
            gnodes.emplace_back(std::to_string(i), sf::Vector2f{1.0f * x, 1.0f * y});
        }
        for (int i = 1; i <= m; i++) {
            gedges.emplace_back(gnodes[rani(0, n - 1)], gnodes[rani(0, n - 1)]);
        }
    }

    void clear() {
        gnodes.clear();
        gedges.clear();
    }

    std::unordered_map<Gnode*, int> reid;
    void copy(Graph& g) {
        gnodes = g.gnodes;
        gedges.clear();
        reid.clear();
        int n = (int)g.gnodes.size();
        for (int i = 0; i < n; i++) {
            reid[&g.gnodes[i]] = i;
        }
        for (const Gedge& t: g.gedges) {
            gedges.emplace_back(gnodes[reid[t.a]], gnodes[reid[t.b]]);
            gedges.back().color = t.color;
            gedges.back().weight = t.weight;
        }
    }
};