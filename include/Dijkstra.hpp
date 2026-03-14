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

    int rut;
    std::set<std::pair<std::pair<int, int>, int>> edges;
    std::unordered_map<int, sf::Vector2f> pos;
    std::unordered_map<int, std::set<std::pair<int, int>>> con;
    std::unordered_map<int, int> cnvid;
    std::unordered_map<int, int> tmp;

    Dijkstra() {
        clear();
    }

    void clear() {
        edges.clear();
        pos.clear();
        con.clear();
        cnvid.clear();
    }

    sf::Vector2f getmov1(sf::Vector2f a, sf::Vector2f b) {
        a -= b;
        float x = sqrlen(a);
        a = pow(x, -1.5) * a;
        return a;
    }

    sf::Vector2f getmov2(sf::Vector2f a, sf::Vector2f b) {
        a -= b;
        float x = sqrt(sqrlen(a));
        return a * ((x - 100) / x) * -0.05f;
    }

    sf::Vector2f getmov(int t, float k = 3.6e4) {
        sf::Vector2f cur = pos[t];
        sf::Vector2f total(0, 0);
        for (const auto& z: pos) {
            if (z.first != t) total += getmov1(cur, z.second);
        }
        total = 3 * total;
        for (int i = 0; i < 12; i++) {
            float x = 240.0f + (i + 0.5f) * (600.0f / 12);
            total += getmov1(cur, sf::Vector2f{x, 0.0f});
            total += getmov1(cur, sf::Vector2f{x, 600.0f});
        }
        for (int i = 0; i < 12; i++) {
            float y = (i + 0.5f) * (600.0f / 12);
            total += getmov1(cur, sf::Vector2f{240.0f, y});
            total += getmov1(cur, sf::Vector2f{840.0f, y});
        }
        total = k * total;
        for (const auto& z: con[t]) {
            if (z.first != t) total += getmov2(cur, pos[z.first]);
        }
        float len = sqrt(sqrlen(total));
        if (len > 50) total = total * (50.0f / len);
        return total;
    }

    void recreate(Graph& g) {
        for (int reps = 720; reps >= 1; reps--) {
            for (auto& z: pos) {
                z.second += getmov(z.first, (reps + 36) * 50.0f);
            }
        }

        int tmpn = -1;
        tmp.clear();
        g.gnodes.clear();
        for (const auto& z: pos) {
            g.gnodes.emplace_back(std::to_string(z.first), z.second);
            g.gnodes.back().id = cnvid[z.first];
            tmp[z.first] = ++tmpn;
        }

        g.gedges.clear();
        for (const auto& t: con) {
            for (const auto& z: t.second) {
                if (t.first > z.first) {
                    g.gedges.emplace_back(g.gnodes[tmp[t.first]], g.gnodes[tmp[z.first]]);
                }
            }
        }
    }

    void load(const Data& data, const Graph& f, Graph& g, std::vector<Graph>& graphs) {
        graphs.clear();
        tmp.clear();
        for (auto& x: con) {
            tmp[x.first] = 1;
            x.second.clear();
        }
        for (const Textform& T: data.textforms) {
            auto t = parse(T.text);
            for (int i = 0; i < std::min(2, (int)t.size()); i++) {
                int u = t[i];
                if (pos.find(u) == pos.end()) {
                    pos[u] = sf::Vector2f{
                        1.f * rani(240 + gnodesize, 840 - gnodesize), 1.f * rani(gnodesize, 600 - gnodesize)
                    };
                    con[u] = {};
                    cnvid[u] = rani();
                } else {
                    std::string num = std::to_string(u);  
                    for (const Gnode& x: f.gnodes) {
                        if (x.text == num) {
                            pos[u] = x.pos;
                            break;
                        }
                    }
                }
                tmp[u] = 0;
            }
            if ((int)t.size() <= 1) continue;
            if (t[0] == t[1]) continue;
            int u = t[0], v = t[1], w = ((int)t.size() <= 2? 1: t[2]);
            con[u].insert({v, w});
            con[v].insert({u, w});
        }
        for (auto& x: tmp) {
            if (x.second) {
                int i = x.first;
                pos.erase(i);
                con.erase(i);
                cnvid.erase(i);
            }
        }
        for (auto &u: con) {
            for (auto& z: u.second) {
                int v = z.first;
                if (pos.find(v) == pos.end()) {
                    u.second.erase(z);
                }
            }
        }
        for (auto &x: pos) {
            std::cout << x.first << " " << x.second.x << " " << x.second.y << std::endl;
        }

        recreate(g);
        graphs.emplace_back(); graphs.back().copy(g);
        reverse(graphs.begin(), graphs.end());
    }
};