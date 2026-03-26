#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Graph.hpp>

struct Twothreefour {
    int customtoi(const std::string& s) {
        int val = 0;
        for (char x: s) {
            if (x == ' ') continue;
            if ('0' <= x && x <= '9') {
                val = val * 10 + x - '0';
                continue;
            }
            return inf;
        }
        return val;
    }
    
    std::string customtos(const std::vector<int>& cur) {
        std::string tmp = "";
        for (int t: cur) {
            if (cnt[t]) {
                tmp += std::to_string(t);
            } else {
                tmp += '(' + std::to_string(t) + ')';
            }
            tmp += ", ";
        }
        if ((int)tmp.size() >= 2) {
            tmp.pop_back(); tmp.pop_back();
        }
        return tmp;
    }

    struct Node {
        std::vector<int> val;
        std::vector<int> child;
        int par;
        int cnt;

        Node() {
            val.clear();
            child.clear();
            par = -1;
            cnt = 1;
        }

        Node(int x, int _par = -1) {
            val.emplace_back(x);
            child.clear();
            par = _par;
            cnt = 1;
        }
    };

    std::vector<Node> nodes;
    std::vector<int> cnvid;
    std::unordered_map<int, int> cnt;
    int rut;

    Twothreefour() {
        clear();
    }

    int newnode() {
        nodes.emplace_back();
        cnvid.emplace_back(rani());
        return (int)nodes.size() - 1;
    }

    int newnode(int x, int _par = -1) {
        nodes.emplace_back(x, _par);
        cnvid.emplace_back(rani());
        return (int)nodes.size() - 1;
    }

    void clear() {
        nodes.clear();
        cnvid.clear();
        cnt.clear();
        rut = newnode();
    }

    void split(Graph& g, std::vector<Graph>& graphs, int p) {
        assert(0 <= p && p < (int)nodes.size());
        bool newrut = (nodes[p].par == -1);
        if (newrut) nodes[p].par = rut = newnode();
        newnode(nodes[p].val[3], nodes[p].par);
        Node& cur = nodes[p];
        Node& anc = nodes[newrut? cur.par = rut: cur.par];
        Node& niu = nodes[(int)nodes.size() - 1];
        if (newrut) anc.child.emplace_back(p);
        int m = (int)anc.val.size();
        for (int i = 0; i <= m; i++) {
            if (cur.val[2] < (i == m? inf: anc.val[i])) {
                anc.val.emplace(anc.val.begin() + i, cur.val[2]);
                anc.child.emplace(anc.child.begin() + i + 1, (int)nodes.size() - 1);
                break;
            }
        }
        cur.val.pop_back(); cur.val.pop_back();
        if (!cur.child.empty()) {
            niu.child.emplace_back(cur.child[3]);
            niu.child.emplace_back(cur.child[4]);
            nodes[cur.child[3]].par = (int)nodes.size() - 1;
            nodes[cur.child[4]].par = (int)nodes.size() - 1;
            cur.child.pop_back(); cur.child.pop_back();
        }
        recreate(g);
        g.gnodes[p].color = sf::Color::Yellow;
        g.gnodes[cur.par].color = sf::Color::Magenta;
        g.gnodes.back().color = sf::Color::Magenta;
        graphs.emplace_back(); graphs.back().copy(g);
        g.gnodes[p].color = defnodecol;
        g.gnodes[cur.par].color = defnodecol;
        g.gnodes.back().color = defnodecol;
        if (anc.val.size() == 4) split(g, graphs, cur.par);
    }

    int add(Graph& g, std::vector<Graph>& graphs, int p, int t) {
        g.gnodes[p].color = sf::Color::Yellow;
        graphs.emplace_back(); graphs.back().copy(g);
        g.gnodes[p].color = defnodecol;
        Node& cur = nodes[p];
        int m = (int)cur.val.size();
        if (cur.child.empty()) {
            cur.val.emplace_back(t);
            sort(cur.val.begin(), cur.val.end());
            if (m == 3) split(g, graphs, p);
            return p;
        }
        assert((int)cur.child.size() == m + 1);
        for (int i = 0; i <= m; i++) {
            if (t < (i == m? inf: cur.val[i])) {
                return add(g, graphs, cur.child[i], t);
            }
        }
        return -1;
    }

    void add_helper(Graph& g, bool& ok, int t) {
        for (int i = 0; i < (int)nodes.size(); i++) {
            for (int _t: nodes[i].val) if (_t == t) {
                g.gnodes[i].color = sf::Color::Green;
                ok = 1;
            }
            if (ok) break;
        }
    }
    void add(Graph& g, std::vector<Graph>& graphs, int t) {
        bool ok = 0;
        add_helper(g, ok, t);
        if (ok) {
            graphs.emplace_back(); graphs.back().copy(g);
            ++cnt[t];
            recreate(g);
            graphs.emplace_back(); graphs.back().copy(g);
            return;
        }
        ++cnt[t];
        add(g, graphs, rut, t);
        recreate(g);
        graphs.emplace_back(); graphs.back().copy(g);
    }

    void del(Graph& g, std::vector<Graph>& graphs, int t) {
        for (int i = 0; i < (int)nodes.size(); i++) {
            bool ok = 0;
            for (int _t: nodes[i].val) if (_t == t) {
                g.gnodes[i].color = sf::Color::Red;
                ok = 1;
            }
            if (ok) break;
        }
        graphs.emplace_back(); graphs.back().copy(g);
        --cnt[t];
        recreate(g);
        graphs.emplace_back(); graphs.back().copy(g);
    }

    void recreate(Graph& g) {
        g.clear();
        int m = (int)nodes.size();
        std::vector<int> depth(m, -1);
        std::queue<int> q;
        depth[rut] = 0;
        q.push(rut);
        int maxd = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v: nodes[u].child) {
                depth[v] = depth[u] + 1;
                maxd = std::max(maxd, depth[v]);
                q.push(v);
            }
        }
        std::vector<std::vector<int>> layers(maxd + 1);
        for (int i = 0; i < m; i++) {
            layers[depth[i]].emplace_back(i);
        }

        float currenty = 0.0f;
        float dy = 600.0f / (maxd + 2);
        std::vector<sf::Vector2f> pos(m);
        for (int d = 0; d <= maxd; d++) {
            currenty += dy;
            int k = (int)layers[d].size();
            for (int i = 0; i < k; i++) for (int j = i + 1; j < k; j++) {
                if (nodes[layers[d][i]].val[0] > nodes[layers[d][j]].val[0]) {
                    std::swap(layers[d][i], layers[d][j]);
                }
            }
            float currentx = 240.0f;
            float dx = 600.0f / (k + 1);
            for (int i = 0; i < k; i++) {
                currentx += dx;
                pos[layers[d][i]] = sf::Vector2f(currentx, currenty);
            }
        }

        g.gnodes.clear();
        for (int i = 0; i < m; i++) {
            g.gnodes.emplace_back(customtos(nodes[i].val), pos[i]);
            g.gnodes[i].id = cnvid[i];
        }
        
        g.gedges.clear();
        for (int i = 0; i < m; i++) {
            for (int t: nodes[i].child) {
                g.gedges.emplace_back(g.gnodes[i], g.gnodes[t]);
            }
        }
    }

    std::unordered_map<int, int> dnt;
    void load(const Data& data, const Graph& f, Graph& g, std::vector<Graph>& graphs) {
        graphs.clear();
        dnt.clear();
        if ((int)nodes.size() > (int)data.textforms.size() + 2) {
            clear();
        }
        if (cnt.empty()) {
            recreate(g);
            graphs.emplace_back(); graphs.back().copy(g);
            for (const Textform& x: data.textforms) {
                int t = customtoi(x.text);
                if (t == inf) continue;
                dnt[t]++;
                add(g, graphs, t);
            }
        } else {
            for (const Node& x: nodes) {
                for (int t: x.val) dnt[t] = 0;
            }
            for (const Textform& x: data.textforms) {
                int t = customtoi(x.text);
                if (t == inf) continue;
                dnt[t]++;
            }
            for (const auto& t: dnt) {
                for (int i = 0; i < t.second - cnt[t.first]; i++) {
                    add(g, graphs, t.first);
                }
                for (int i = 0; i > t.second - cnt[t.first]; i--) {
                    del(g, graphs, t.first);
                }
            }
        }
        cnt = dnt;

        reverse(graphs.begin(), graphs.end());
        if (!stepbystep) {
            while ((int)graphs.size() > 1) {
                graphs.pop_back();
            }
        }
    }
};