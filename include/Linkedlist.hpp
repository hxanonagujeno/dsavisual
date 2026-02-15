#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Graph.hpp>

struct Linkedlist {
    std::vector<std::string> nodes;
    std::vector<std::vector<int>> dp;

    void load(const Data& data, const Graph& f, Graph& g) {
        g.clear();
        nodes.clear();
        int n = (int)data.textforms.size();
        for (const Textform& x: data.textforms) {
            nodes.emplace_back(x.text);
        }
        float currentpos = 240.0f + 1.5f * gnodesize;
        float spacing = (n == 1? 0.0f: (480.0f - 3 * gnodesize) / (n - 1));
        for (int i = 0; i < n; i++) {
            g.gnodes.emplace_back(nodes[i], sf::Vector2f{currentpos, 240.0f});
            currentpos += spacing;
        }
        for (int i = 0; i + 1 < n; i++) {
            g.gedges.emplace_back(g.gnodes[i], g.gnodes[i + 1]);
        }
        int N = f.gnodes.size();
        dp.assign(N, std::vector<int>(n, 0));
        for (int i = 0; i < N; i++) for (int j = 0; j < n; j++) {
            dp[i][j] = (i && j? dp[i - 1][j - 1]: 0) + (f.gnodes[i].text == g.gnodes[j].text);
            if (i) mxz(dp[i][j], dp[i - 1][j]);
            if (j) mxz(dp[i][j], dp[i][j - 1]);
        }
        for (int i = N - 1, j = n - 1; i >= 0 && j >= 0;) {
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
};