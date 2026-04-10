#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Graph.hpp>

struct Gengine {
    std::set<std::pair<std::pair<int, int>, int>> edges;
    std::map<int, sf::Vector2f> pos;
    std::map<int, std::set<std::pair<int, int>>> con;
    std::map<int, int> cnvid;
    std::map<int, int> tmp;

    Gengine() {
        Gclear();
    }

    void Gclear() {
        edges.clear();
        pos.clear();
        con.clear();
        cnvid.clear();
        tmp.clear();
    }

    sf::Vector2f getmov1(sf::Vector2f a, sf::Vector2f b) {
        a -= b;
        float x = std::max(sqrlen(a), 1e-6f);
        a = pow(x, -1.5) * a;
        return a;
    }

    sf::Vector2f getmov2(sf::Vector2f a, sf::Vector2f b) {
        a -= b;
        float x = sqrt(sqrlen(a));
        return a * ((x - 100) / std::max(x, 1e-4f)) * -0.03f;
    }

    sf::Vector2f getmov(int t, float k = 1.2e4) {
        sf::Vector2f cur = pos[t];
        sf::Vector2f total(0, 0);
        for (const auto& z: pos) {
            if (z.first != t) total += getmov1(cur, z.second);
        }
        total = 3 * total;
        for (int i = 0; i < 15; i++) {
            float x = 240.0f + (i + 0.5f) * (600.0f / 15);
            total += getmov1(cur, sf::Vector2f{x, 0.0f});
            total += getmov1(cur, sf::Vector2f{x, 600.0f});
        }
        for (int i = 0; i < 15; i++) {
            float y = (i + 0.5f) * (600.0f / 15);
            total += getmov1(cur, sf::Vector2f{240.0f, y});
            total += getmov1(cur, sf::Vector2f{840.0f, y});
        }
        total = k * total;
        for (const auto& z: con[t]) {
            if (z.first != t) {
                total += getmov2(cur, pos[z.first]);
            }
        }
        float len = sqrt(sqrlen(total));
        if (len > 50) total = total * (50.0f / len);
        return total;
    }

    void recreate(Graph& g, bool regraph = 0) {
        if (regraph) {
            for (int reps = 500; reps >= 1; reps--) {
                for (auto& z: pos) {
                    z.second += getmov(z.first, (reps + 36) * 50.0f);
                    if (_isnan(z.second.x) || _isnan(z.second.y)) {
                        z.second.x = 1.f * rani(240 + gnodesize, 840 - gnodesize);
                        z.second.y = 1.f * rani(gnodesize, 600 - gnodesize);
                    }
                    mxz(z.second.x, 240.0f + gnodesize);
                    mnz(z.second.x, 840.0f - gnodesize);
                    mxz(z.second.y, 0.000f + gnodesize);
                    mnz(z.second.y, 600.0f - gnodesize);
                }
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
                    g.gedges.back().weight = z.second;
                }
            }
        }
    }
};