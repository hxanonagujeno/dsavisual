#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Graph.hpp>

struct Linkedlist {
    std::vector<std::string> nodes;
    std::vector<std::vector<int>> dp;

    void clear() {
        nodes.clear();
    }

    void preload(const Data& data, const Graph& f, Graph& g) {
        g.clear();
        nodes.clear();
        int n = (int)data.textforms.size();
        for (const Textform& x: data.textforms) {
            nodes.emplace_back(x.text);
        }
        float currentpos = 240.0f;
        float spacing = 600.0f / (n + 1);
        for (int i = 0; i < n; i++) {
            currentpos += spacing;
            g.gnodes.emplace_back(nodes[i], sf::Vector2f{currentpos, 300.0f});
        }
        for (int i = 0; i + 1 < n; i++) {
            g.gedges.emplace_back(g.gnodes[i], g.gnodes[i + 1]);
        }

        int m = f.gnodes.size();
        dp.assign(m, std::vector<int>(n, 0));
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) {
            dp[i][j] = (i && j? dp[i - 1][j - 1]: 0) + (f.gnodes[i].text == g.gnodes[j].text);
            if (i) mxz(dp[i][j], dp[i - 1][j]);
            if (j) mxz(dp[i][j], dp[i][j - 1]);
        }
        for (int i = m - 1, j = n - 1; i >= 0 && j >= 0;) {
            if (i && dp[i][j] == dp[i - 1][j]) {
                i--; continue;
            }
            if (j && dp[i][j] == dp[i][j - 1]) {
                j--; continue;
            }
            if (dp[i][j] == (i && j? dp[i - 1][j - 1]: 0) + 1) {
                g.gnodes[j].id = f.gnodes[i].id;
            }
            i--; j--;
        }
    }

    void load(const Data& data, const Graph& f, Graph& g, std::vector<Graph>& graphs) {
        preload(data, f, g);
        graphs.clear();
        graphs.emplace_back(); graphs.back().copy(g);
        int m = f.gnodes.size(), n = g.gnodes.size();
        for (Gnode& t: g.gnodes) t.pos += {0, gnodesize * -1.5f};
        graphs.emplace_back(); graphs.back().copy(g);
        
        for (int i = m - 1, j = n - 1; i >= 0 && j >= 0;) {
            if (i && dp[i][j] == dp[i - 1][j]) {
                g.gnodes.emplace(g.gnodes.begin() + j + 1, f.gnodes[i]);
                g.gnodes[j + 1].pos += {0, gnodesize * 1.5f};
                g.gedges.clear();
                int sz = (int)g.gnodes.size();
                for (int k = 0; k + 1 < sz; k++) if (k != j + 1 && k != j) {
                    g.gedges.emplace_back(g.gnodes[k], g.gnodes[k + 1]);
                }
                graphs.emplace_back(); graphs.back().copy(g);
                i--; continue;
            }
            if (j && dp[i][j] == dp[i][j - 1]) {
                g.gnodes.erase(g.gnodes.begin() + j);
                g.gedges.clear();
                int sz = (int)g.gnodes.size();
                for (int k = 0; k + 1 < sz; k++) {
                    g.gedges.emplace_back(g.gnodes[k], g.gnodes[k + 1]);
                }
                graphs.emplace_back(); graphs.back().copy(g);
                j--; continue;
            }
            i--; j--;
        }

        if (stepbystep) {
            reverse(graphs.begin(), graphs.end());
        }
    }
};