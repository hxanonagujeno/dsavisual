#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Gnode.hpp>
#include <Gedge.hpp>

struct Graph {
    std::vector<Gnode> gnodes;
    std::vector<Gedge> gedges;
    int codesection;

    Graph() {
        gnodes.clear();
        gedges.clear();
        codesection = 0;
    }
    
    void checkgnodes() {
        if (animating || showsteps) return;
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
            t.display();
        }
    }

    void clear() {
        gnodes.clear();
        gedges.clear();
    }

    std::unordered_map<Gnode*, int> reid;
    void copy(Graph& g, int _codesection = -1) {
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
        codesection = (_codesection >= 0? _codesection: g.codesection);
    }
};