#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Graph.hpp>

struct Dijkstra {
    std::vector<int> parse(const std::string& s) {
        std::vector<int> res;
        int tmp = -1;
        for (char c: s) {
            if (isspace(c)) {
                if (tmp != -1) {
                    res.emplace_back(tmp);
                    tmp = -1;
                }
            } else {
                if (isdigit(c)) {
                    if (tmp == -1) tmp = 0;
                    tmp = tmp * 10 + c - '0';
                }
            }
            if ((int)res.size() > 3) return {};
        }
        if (tmp != -1) res.emplace_back(tmp);
        if ((int)res.size() > 3) return {};
        return res;
    }

    std::vector<int> cnvid;
    std::vector<std::vector<std::pair<int, int>>> con;
    std::vector<sf::Vector2f> pos;
    std::unordered_map<int, int> cnv;

    Dijkstra() {
        clear();
    }

    void clear() {
        cnvid.clear();
        con.clear();
        pos.clear();
        cnv.clear();
    }

    void add(Graph& g, std::vector<Graph>& graphs, const std::string& s) {
    }

    void del(Graph& g, std::vector<Graph>& graphs, const std::string& s) {
    }

    sf::Vector2f getmov1(sf::Vector2f a, sf::Vector2f b) {
        a -= b;
        float x = sqrdis(a);
        a = pow(x, -1.5) * a;
        return a;
    }

    sf::Vector2f getmov(int t) {
        sf::Vector2f total(0, 0);
        int n = (int)cnvid.size();
        for (int i = 0; i < n; i++) if (i != t) {
            total += getmov1(pos[t], pos[i]);
        }
        total = 3 * total;
        for (int i = 0; i < 12; i++) {
            float x = 240.0f + (i + 0.5f) * (600.0f / 12);
            total += getmov1(pos[t], sf::Vector2f{x, 0.0f});
            total += getmov1(pos[t], sf::Vector2f{x, 600.0f});
        }
        for (int i = 0; i < 12; i++) {
            float y = (i + 0.5f) * (600.0f / 12);
            total += getmov1(pos[t], sf::Vector2f{240.0f, y});
            total += getmov1(pos[t], sf::Vector2f{840.0f, y});
        }
        total = 3.6e4 * total;
        return total;
    }

    void recreate(Graph& g) {
        int n = (int)cnvid.size();
        for (int reps = 360; reps >= 1; reps--) {
            for (int i = 0; i < n; i++) {
                pos[i] += getmov(i);
            }
        }

        g.gnodes.resize(n);
        for (int i = 0; i < n; i++) {
            g.gnodes[i].id = cnvid[i];
            g.gnodes[i].pos = pos[i];
        }

        g.gedges.clear();
        for (int i = 0; i < n; i++) {
            for (const auto& t: con[i]) {
                if (i > t.first) {
                    g.gedges.emplace_back(g.gnodes[i], g.gnodes[t.first]);
                }
            }
        }
    }

    void load(const Data& data, const Graph& f, Graph& g, std::vector<Graph>& graphs) {
        graphs.clear();
        for (const Textform& x: data.textforms) {
            auto t = parse(x.text);
            if ((int)t.size() == 0) continue;
            if (!cnv.count(t[0])) {
                cnv[t[0]] = (int)cnvid.size();
                cnvid.emplace_back(rani());
                con.emplace_back();
                pos.emplace_back(1.0f * rani(240 + gnodesize, 840 - gnodesize), 1.0f * rani(gnodesize, 600 - gnodesize));
            }
            if ((int)t.size() == 1) continue;
            if (t[0] == t[1]) continue;
            if (!cnv.count(t[1])) {
                cnv[t[1]] = (int)cnvid.size();
                cnvid.emplace_back(rani());
                con.emplace_back();
                pos.emplace_back(1.0f * rani(240 + gnodesize, 840 - gnodesize), 1.0f * rani(gnodesize, 600 - gnodesize));
            }
            int u = cnv[t[0]], v = cnv[t[1]], w = ((int)t.size() == 2? 1: t[2]);
            con[u].emplace_back(v, w);
            con[v].emplace_back(u, w);
        }
        recreate(g);
        graphs.emplace_back(); graphs.back().copy(g);
        reverse(graphs.begin(), graphs.end());
    }
};