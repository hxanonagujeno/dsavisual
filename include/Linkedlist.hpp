#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Graph.hpp>

struct Linkedlist {
    std::vector<std::string> nodes;
    void load(const Data& data, Graph& graph) {
        graph.clear();
        nodes.clear();
        int n = (int)data.textforms.size();
        for (const Textform& x: data.textforms) {
            nodes.emplace_back(x.text);
        }
        float currentpos = 240.0f + 1.5f * gnodesize;
        float spacing = (n == 1? 0.0f: (480.0f - 3 * gnodesize) / (n - 1));
        for (int i = 0; i < n; i++) {
            graph.gnodes.emplace_back(nodes[i], sf::Vector2f{currentpos, 240.0f});
            currentpos += spacing;
        }
    }
};