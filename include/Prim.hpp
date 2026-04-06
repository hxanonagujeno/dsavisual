#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Graph.hpp>
#include <Gengine.hpp>

struct Prim: Gengine {
    std::vector<int> dis;
    std::vector<int> par;
    std::set<std::pair<int, int>> mstedges;

    void clear() {
        Gclear();
        dis.clear();
        par.clear();
        mstedges.clear();
    }

    void reedge(Graph& g) {
        for (Gedge& t: g.gedges) {
            if (!t.a || !t.b) continue;
            int u = tmp[stoi(t.a->text)], v = tmp[stoi(t.b->text)];
            if (u > v) std::swap(u, v);
            t.color = (mstedges.count({u, v})? orange: charcoal);
        }
    }

    void prm(Graph& g, std::vector<Graph>& graphs, int _rut = -1) {
        int rut = INT_MAX;
        if (_rut == -1) {
            for (const auto& x: pos) {
                mnz(rut, x.first);
            }
        } else {
            rut = _rut;
        }

        int n = (int)pos.size();
        dis.assign(n, INT_MAX);
        par.assign(n, -1);
        mstedges.clear();

        std::priority_queue<std::array<int, 3>, std::vector<std::array<int, 3>>, std::greater<std::array<int, 3>>> q;
        q.push({dis[tmp[rut]] = 0, rut, rut});
        mstedges.clear();
        std::set<std::pair<int, int>> col;

        while (!q.empty()) {
            int u = q.top()[1], p = q.top()[2], U = tmp[u]; q.pop();
            if (par[U] != -1) continue;
            col.erase({dis[U], u});
            par[U] = p;
            mstedges.insert({std::min(U, tmp[p]), std::max(U, tmp[p])});
            reedge(g);
            g.gnodes[U].color = sf::Color::Yellow;
            graphs.emplace_back(); graphs.back().copy(g, 2);
            g.gnodes[U].color = sf::Color::Green;
            graphs.emplace_back(); graphs.back().copy(g, 2);
            for (const std::pair<int, int>& t: con[u]) {
                int v = t.first, w = t.second, V = tmp[v];
                if (v == par[U] || par[V] != -1) continue;
                col.erase({dis[V], v});
                mnz(dis[V], w);
                col.insert({dis[V], v});
                g.gnodes[V].color = sf::Color::Green;
                graphs.emplace_back(); graphs.back().copy(g, 3);
                q.push({w, v, u});
                float cur = 0.9f;
                for (const std::pair<int, int>& t: col) {
                    if (g.gnodes[tmp[t.second]].color == defnodecol) continue;
                    float r = 1.0f / (cur *= 1.75f);
                    g.gnodes[tmp[t.second]].color = r * sf::Color::Yellow + (1.0f - r) * slate;
                }
                graphs.emplace_back(); graphs.back().copy(g, 3);
            }
            g.gnodes[U].color = sf::Color::Yellow;
            graphs.emplace_back(); graphs.back().copy(g, 2);
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
        
        mstedges.clear(); 
        recreate(g, 1);
        reedge(g); 
        graphs.emplace_back(); graphs.back().copy(g, 0);
        int rut = -1;
        if (data.lstfocus != -1) {
            std::vector<int> tmp = parse(data.textforms[data.lstfocus].text);
            if (!tmp.empty()) {
                rut = tmp[0];
            }
        }
        prm(g, graphs, rut);
        graphs.emplace_back(); graphs.back().copy(g, 0);
        mstedges.clear(); 
        recreate(g); 
        reedge(g); 
        graphs.emplace_back(); graphs.back().copy(g, 0);
        if (!stepbystep) { 
            reverse(graphs.begin(), graphs.end());
        }
    }
};