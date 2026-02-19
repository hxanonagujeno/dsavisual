#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Graph.hpp>

struct Linearprobing {
    int n = 0;
    std::vector<std::string> vals;

    int hash(const std::string& s) {
        int val = 0;
        for (char t: s) {
            val += (t + 1) * 293;
            val %= n;
        }
        return val;
    }

    void add(const std::string& s) {
		int i = hash(s);
        std::cout << i << std::endl;
		while (!vals[i].empty() && vals[i][0] != '#') {
            if (vals[i] == s) return;
			i = (i + 1) % n;
		}
		vals[i] = s;
	}
	
	void del(const std::string& s) {
		int i = hash(s);
		for (int j = 0; j < n; j++) {
			if (vals[i] == s) return vals[i] = "#", void();
			if (vals[i].empty()) return;
			i = (i + 1) % n;
		}
	}

    void recreate(Graph& g) {
        float currentpos = 240.0f + 1.5f * gnodesize;
        float spacing = (n == 1? 0.0f: (480.0f - 3 * gnodesize) / (n - 1));
        g.gnodes.clear();
        for (int i = 0; i < n; i++) {
            g.gnodes.emplace_back(vals[i], sf::Vector2f{currentpos, 240.0f});
            currentpos += spacing;
        }
        for (int i = 0; i + 1 < n; i++) {
            g.gedges.emplace_back(g.gnodes[i], g.gnodes[i + 1]);
        }
    }

    std::map<std::string, int> cnv;
    void preload(const Data& data, const Graph& f, Graph& g) {
        if (n != (int)data.textforms.size()) {
            n = (int)data.textforms.size();
            vals.assign(n, "");
            for (const Textform& t: data.textforms) {
                std::cout << t.text << std::endl;
                if (!t.text.empty()) add(t.text);
            }
            recreate(g);
        } else {
            cnv.clear();
            for (const std::string& t: vals) {
                if (!t.empty()) cnv[t] |= 1;
            }
            for (const Textform& t: data.textforms) {
                if (!t.text.empty()) cnv[t.text] |= 2;
            }
            for (const auto& x: cnv) {
                if (x.second == 1) del(x.first);
            }
            for (const auto& x: cnv) {
                if (x.second == 2) add(x.first);
            }
            recreate(g);
            for (int i = 0; i < n; i++) {
                if (g.gnodes[i].text == f.gnodes[i].text) {
                    g.gnodes[i].id = f.gnodes[i].id;
                }
            }
        }
    }

    void load(const Data& data, const Graph& f, Graph& g, std::vector<Graph>& graphs) {
        preload(data, f, g);
        graphs.clear();
        graphs.emplace_back(); graphs.back().copy(g);
        if (!stepbystep) return;
    }
};