#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Graph.hpp>

struct Dijkstra {
    std::vector<std::string> parse(const std::string& s) {
        std::vector<std::string> res;
        std::string tmp = "";
        for (char c: s) {
            if (isspace(c)) {
                if (!tmp.empty()) {
                    res.emplace_back(tmp);
                    tmp = "";
                }
            } else tmp += c;
        }
        if (!tmp.empty()) res.emplace_back(tmp);
        if ((int)res.size() != 3) return {};
        return res;
    }

    Dijkstra() {
        clear();
    }

    void clear() {
    }

    void add(Graph& g, std::vector<Graph>& graphs, const std::string& s) {
    }

    void del(Graph& g, std::vector<Graph>& graphs, const std::string& s) {
    }

    void recreate(Graph& g) {
    }

    void load(const Data& data, const Graph& f, Graph& g, std::vector<Graph>& graphs) {
    }
};