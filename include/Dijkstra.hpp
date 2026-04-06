#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Graph.hpp>
#include <Gengine.hpp>

struct Dijkstra: Gengine {
    std::vector<int> dis;
    std::vector<int> par;
    std::set<std::pair<int, int>> djkedges;

    void clear() {
        Gclear();
        dis.clear();
        par.clear();
        djkedges.clear();
    }

    void reedge(Graph& g) {
        for (Gedge& t: g.gedges) {
            if (!t.a || !t.b) continue;
            int u = tmp[stoi(t.a->text)], v = tmp[stoi(t.b->text)];
            if (u > v) std::swap(u, v);
            t.color = (djkedges.count({u, v})? orange: charcoal);
        }
    }

    void djk(Graph& g, std::vector<Graph>& graphs) {
        int rut = INT_MAX;
        for (const auto& x: pos) {
            mnz(rut, x.first);
        }

        g.gnodes[tmp[rut]].color = sf::Color::Yellow;
        graphs.emplace_back(); graphs.back().copy(g, 1);

        int n = (int)pos.size();
        dis.assign(n, INT_MAX);
        par.assign(n, -1);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
        q.emplace(dis[tmp[rut]] = 0, rut);
        djkedges.clear();

        while (!q.empty()) {
            int D = q.top().first, u = q.top().second, U = tmp[u]; q.pop();
            if (D > dis[U]) continue;
            int ographssize = (int)graphs.size();
            bool ok = 0;
            g.gnodes[U].color = sf::Color::Green;
            graphs.emplace_back(); graphs.back().copy(g, 2);
            for (const std::pair<int, int>& t: con[u]) {
                int v = t.first, w = t.second, V = tmp[v];
                if (V == par[U]) continue;
                sf::Color ocolor = g.gnodes[V].color;
                g.gnodes[V].color = sf::Color::Green;
                graphs.emplace_back(); graphs.back().copy(g, 2);
                if (mnz(dis[V], D + w)) {
                    ok = 1;
                    djkedges.erase({std::min(par[V], V), std::max(par[V], V)});
                    q.emplace(dis[V], v);
                    par[V] = U;
                    djkedges.insert({std::min(par[V], V), std::max(par[V], V)});
                    reedge(g);
                    graphs.emplace_back(); graphs.back().copy(g, 2);
                    g.gnodes[V].color = sf::Color::Yellow;
                } else {
                    g.gnodes[V].color = ocolor;
                    graphs.emplace_back(); graphs.back().copy(g, 2);
                }
            }
            g.gnodes[U].color = sf::Color::Yellow;
            graphs.emplace_back(); graphs.back().copy(g, 2);
            if (!ok) {
                while ((int)graphs.size() > ographssize) {
                    graphs.pop_back();
                }
            }
        }
    }

    void find(Graph& g, std::vector<Graph>& graphs, int stt) {
        if (!tmp[stt]) return;
        std::vector<int> pth;
        for (int curr = tmp[stt]; 1; curr = par[curr]) {
            pth.push_back(curr);
            if (par[curr] == -1) {
                break;
            }
            if ((int)pth.size() > 100) {
                return;
            }
        }
        std::reverse(pth.begin(), pth.end());

        for (int t: pth) {
            g.gnodes[t].color = sf::Color::Cyan;
            for (Gedge& t: g.gedges) {
                if (t.a->color == sf::Color::Cyan && t.b->color == sf::Color::Cyan) {
                    t.color = sf::Color::Blue;
                }
            }
            g.gnodes[t].color = sf::Color::Yellow;
            graphs.emplace_back(); graphs.back().copy(g, 3);
            g.gnodes[t].color = sf::Color::Cyan;
            graphs.emplace_back(); graphs.back().copy(g, 3);
        }

        graphs.emplace_back(); graphs.back().copy(g, 3);
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
                tmp.erase(i);
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
        
        djkedges.clear(); 
        recreate(g, 1);
        reedge(g); 
        graphs.emplace_back(); graphs.back().copy(g, 0);
        djk(g, graphs);
        graphs.emplace_back(); graphs.back().copy(g, 0);
        if (data.lstfocus != -1) {
            std::vector<int> tmp = parse(data.textforms[data.lstfocus].text);
            if (!tmp.empty()) {
                find(g, graphs, tmp[0]);
            }
        }
        djkedges.clear(); 
        recreate(g); 
        reedge(g); 
        graphs.emplace_back(); graphs.back().copy(g, 0);
        if (!stepbystep) { 
            reverse(graphs.begin(), graphs.end());
        }
    }
};