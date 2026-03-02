#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Graph.hpp>

struct Twothreefour {
    int customtoi(const std::string& s) {
        int sgn = 0;
        int val = 0;
        for (char x: s) {
            if (x == ' ') continue;
            if (x == '-' || x == '+') {
                if (sgn != 0) return inf;
                sgn = (x == '-'? -1: 1);
                continue;
            }
            if ('0' <= x && x <= '9') {
                val = val * 10 + x - '0';
                continue;
            }
            return inf;
        }
        if (sgn == 0) sgn = 1;
        return sgn * val;
    }
    
    std::string customtos(const std::vector<int>& cur) {
        std::string tmp = "";
        for (int t: cur) {
            tmp += std::to_string(t);
            tmp += '|';
        }
        tmp.pop_back();
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
    int rut;

    Twothreefour() {
        clear();
    }

    int newnode() {
        nodes.emplace_back();
        return (int)nodes.size() - 1;
    }

    int newnode(int x, int _par = -1) {
        nodes.emplace_back(x, _par);
        return (int)nodes.size() - 1;
    }

    void clear() {
        nodes.clear();
        rut = newnode();
    }

    void split(int p) {
        assert(0 <= p && p < (int)nodes.size());
        std::cout << "splitting " << p << " begins" << std::endl;
        if (nodes[p].par == -1) nodes[p].par = rut = newnode();
        newnode(nodes[p].val[3], nodes[p].par);
        Node& cur = nodes[p];
        Node& anc = nodes[cur.par == -1? cur.par = rut: cur.par];
        anc.child.emplace_back(p);
        // Node& niu = nodes[(int)nodes.size()];
        std::cout << "splitting " << p << " step 1" << std::endl;
        int m = (int)anc.val.size();
        for (int i = 0; i <= m; i++) {
            std::cout << "splitting " << p << " step 1." << i << std::endl;
            std::cout << (i == 0? -inf: anc.val[i - 1]) << std::endl;
            std::cout << "splitting " << p << " step 1." << i << " A" << std::endl;
            std::cout << (i == m? inf: anc.val[i]) << std::endl;
            std::cout << "splitting " << p << " step 1." << i << " B" << std::endl;
            std::cout << cur.val[2] << std::endl;
            if ((i == 0? -inf: anc.val[i - 1]) <= cur.val[2] && cur.val[2] < (i == m? inf: anc.val[i])) {
                std::cout << "confirmed " << i << std::endl;
                anc.val.emplace(anc.val.begin() + i, cur.val[2]);
                std::cout << "confirmed " << i << std::endl;
                anc.child.emplace(anc.child.begin() + i + 1, (int)nodes.size() - 1);
                std::cout << "confirmed " << i << std::endl;
                break;
            }
        }
        std::cout << "splitting " << p << " step 2" << std::endl;
        cur.val.pop_back(); cur.val.pop_back();
        if (anc.val.size() == 4) split(cur.par);
        std::cout << "splitting " << p << " ends" << std::endl;
    }

    int add(int p, int t) {
        Node& cur = nodes[p];
        int m = (int)cur.val.size();
        if (cur.child.empty()) {
            cur.val.emplace_back(t);
            sort(cur.val.begin(), cur.val.end());
            if (m == 3) split(p);
            std::cout << p << " is the modified node" << std::endl;
            return p;
        }
        assert((int)cur.child.size() == m + 1);
        for (int i = 0; i <= m; i++) {
            if ((i == 0? -inf: cur.val[i - 1]) <= t && t < (i == m? inf: cur.val[i])) {
                return add(cur.child[i], t);
            }
        }
        return -1;
    }

    void add(int t) {
        add(rut, t);
        // ++nodes[add(rut, t)].cnt;
    }

    void recreate(Graph& g) {
        std::cout << "recreate starts" << std::endl;
        g.clear();
        int m = (int)nodes.size();
        std::vector<int> depth(m, -1);
        std::queue<int> q;
        std::cout << "root is " << rut << ", number of nodes is " << m << std::endl;
        depth[rut] = 0;
        q.push(rut);
        int maxd = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v: nodes[u].child) {
                std::cout << u << ": " << v << std::endl;
                depth[v] = depth[u] + 1;
                maxd = std::max(maxd, depth[v]);
                q.push(v);
            }
        }
        std::vector<std::vector<int>> layers(maxd + 1);
        for (int i = 0; i < m; i++) {
            layers[depth[i]].push_back(i);
        }
        std::cout << "recreate bfs done" << std::endl;

        float currenty = 0.0f;
        float dy = 480.0f / (maxd + 2);
        std::vector<sf::Vector2f> pos(m);
        for (int d = 0; d <= maxd; d++) {
            currenty += dy;
            int k = (int)layers[d].size();
            float currentx = 240.0f;
            float dx = 480.0f / (k + 1);
            for (int i = 0; i < k; i++) {
                currentx += dx;
                pos[layers[d][i]] = sf::Vector2f(currentx, currenty);
            }
        }
        std::cout << "recreate spacing done" << std::endl;

        g.gnodes.clear();
        for (int i = 0; i < m; i++) {
            g.gnodes.emplace_back(customtos(nodes[i].val), pos[i]);
        }
        std::cout << "recreate ends" << std::endl;
    }

    void load(const Data& data, const Graph& f, Graph& g, std::vector<Graph>& graphs) {
        graphs.clear();
        clear();
        for (const Textform& t: data.textforms) {
            int tmp = customtoi(t.text);
            if (tmp == inf) continue;
            std::cout << tmp << " starts" << std::endl;
            add(tmp);
            std::cout << tmp << " halfway" << std::endl;
            recreate(g);
            std::cout << tmp << " ends" << std::endl;
            graphs.emplace_back(g);
        }

        std::cout << "adding done" << std::endl;
        reverse(graphs.begin(), graphs.end());
        if (!stepbystep) {
            std::cout << "removing extra steps starts" << std::endl;
            while ((int)graphs.size() > 1) {
                graphs.pop_back();
            }
            std::cout << "removing extra steps ends" << std::endl;
        }
    }
};