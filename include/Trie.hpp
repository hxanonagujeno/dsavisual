#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Graph.hpp>

struct Trie {
    struct Node {
        int nxt[128];
        int cnt;
        char text;
        Node() {
            cnt = 0;
            for (int i = 0; i < 128; i++) {
                nxt[i] = -1;
            }
            text = 0;
        }
    };
    std::vector<Node> nodes;
    std::map<std::string, int> texts;
    std::vector<int> poses;
    std::vector<int> rev;
    std::vector<int> cnvid;

    Trie() {
        clear();
    }

    void clear() {
        nodes.clear();
        nodes.emplace_back(); 
        nodes[0].cnt = 1;
        nodes[0].text = '#';
        texts.clear();
        rev.clear();
        rev.emplace_back(0);
        cnvid.clear();
        cnvid.emplace_back(rani());
    }

    int add(Graph& g, std::vector<Graph>& graphs, const std::string& s) {
        int ogsz = (int)g.gnodes.size();
        int ogani = (int)graphs.size();
        int p = 0;
        poses.clear();
        for (char c: s) {
            if (nodes[p].nxt[(int)c] == -1) {
                nodes[p].nxt[(int)c] = (int)nodes.size();
                nodes.emplace_back();
                nodes.back().text = c;
                cnvid.emplace_back(rani());
            }
            p = nodes[p].nxt[(int)c];
            nodes[p].cnt++;
            recreate(g);
            poses.emplace_back(p);
            if (rev[p] != -1) {
                g.gnodes[rev[p]].color = sf::Color::Yellow;
                graphs.emplace_back(); graphs.back().copy(g);
                g.gnodes[rev[p]].color = defnodecol;
            }
        }
        for (int i: poses) if (rev[i] != -1) {
            g.gnodes[rev[i]].color = sf::Color::Green;
        }
        graphs.emplace_back(); graphs.back().copy(g);
        for (int i: poses) if (rev[i] != -1) {
            g.gnodes[rev[i]].color = defnodecol;
        }
        graphs.emplace_back(); graphs.back().copy(g);
        if (ogsz == (int)g.gnodes.size()) {
            for (int i = (int)graphs.size() - ogani; i >= 1; i--) {
                graphs.pop_back();
            }
        }
        return p;
    }

    int del(Graph& g, std::vector<Graph>& graphs, const std::string& s) {
        int ogsz = (int)g.gnodes.size();
        int ogani = (int)graphs.size();
        int p = 0;
        poses.clear();  
        for (char c: s) {
            if (nodes[p].nxt[(int)c] == -1) return -1;
            p = nodes[p].nxt[(int)c];
            if (!nodes[p].cnt) return -1;
            nodes[p].cnt--;
            poses.emplace_back(p);
            if (rev[p] != -1) {
                g.gnodes[rev[p]].color = sf::Color::Yellow;
                graphs.emplace_back(); graphs.back().copy(g);
                g.gnodes[rev[p]].color = defnodecol;
            }
        }
        for (int i: poses) if (rev[i] != -1) {
            g.gnodes[rev[i]].color = sf::Color::Red;
        }
        graphs.emplace_back(); graphs.back().copy(g);
        recreate(g);
        for (int i: poses) if (rev[i] != -1) {
            g.gnodes[rev[i]].color = defnodecol;
        }
        graphs.emplace_back(); graphs.back().copy(g);
        if (ogsz == (int)g.gnodes.size()) {
            for (int i = (int)graphs.size() - ogani; i >= 1; i--) {
                graphs.pop_back();
            }
        }
        return p;
    }

    void reedge(Graph& g) {
        int m = (int)nodes.size();
        g.gedges.clear();
        for (int u = 0; u < m; u++) {
            for (int c = 0; c < 128; c++) {
                int v = nodes[u].nxt[(int)c];
                if (v != -1 && nodes[u].cnt > 0 && nodes[v].cnt > 0) {
                    g.gedges.emplace_back(g.gnodes[rev[u]], g.gnodes[rev[v]]);
                }
            }
        }
    }

    void recreate(Graph& g) {
        g.clear();
        int m = (int)nodes.size();
        std::vector<int> depth(m, -1);
        std::deque<int> q;
        depth[0] = 0;
        q.push_back(0);
        int maxd = 0;
        std::vector<std::vector<int>> layers;
        while (!q.empty()) {
            int u = q.front(); q.pop_front();
            maxd = std::max(maxd, depth[u]);
            while ((int)layers.size() <= maxd) {
                layers.emplace_back();
            }
            layers[depth[u]].emplace_back(u);
            for (int c = 127; c >= 0; c--) {
                int v = nodes[u].nxt[(int)c];
                if (v != -1 && nodes[v].cnt > 0) {
                    depth[v] = depth[u] + 1;
                    q.push_front(v);
                }
            }
        }

        float currenty = 0.0f;
        float dy = 600.0f / (maxd + 2);
        std::vector<sf::Vector2f> pos(m);
        for (int d = 0; d <= maxd; d++) {
            currenty += dy;
            int k = (int)layers[d].size();
            float currentx = 240.0f;
            float dx = 600.0f / (k + 1);
            for (int i = 0; i < k; i++) {
                currentx += dx;
                pos[layers[d][i]] = sf::Vector2f(currentx, currenty);
            }
        }

        g.gnodes.clear();
        rev.assign(m, -1);
        int sz = 0;
        for (int i = 0; i < m; i++) {
            if (depth[i] != -1) {
                g.gnodes.emplace_back((std::string)("") + nodes[i].text, pos[i]);
                g.gnodes.back().id = cnvid[i];
                rev[i] = sz++;
            }
        }
        reedge(g);
    }

    std::map<std::string, int> dexts;
    void load(const Data& data, const Graph& f, Graph& g, std::vector<Graph>& graphs) {
        graphs.clear();
        dexts.clear();
        if (texts.empty()) {
            for (const Textform& x: data.textforms) {
                dexts[x.text] += 1;
                add(g, graphs, x.text);
            }
        } else {
            for (const auto& x: texts) {
                dexts[x.first] = 0;
            }
            for (const Textform& x: data.textforms) {
                dexts[x.text] += 1;
            }
            for (const auto& x: dexts) {
                for (int i = 0; i < x.second - texts[x.first]; i++) {
                    add(g, graphs, x.first);
                }
            }
            for (const auto& x: dexts) {
                for (int i = 0; i > x.second - texts[x.first]; i--) {
                    del(g, graphs, x.first);
                }
            }
        }
        texts = dexts;

        if (!stepbystep) { 
            reverse(graphs.begin(), graphs.end());
        }
    }
};