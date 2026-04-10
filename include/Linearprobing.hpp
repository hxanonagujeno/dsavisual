#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Graph.hpp>

struct Linearprobing {
    int n = -1;
    std::vector<std::string> vals;
    bool resized = 0;

    void clear() {
        n = -1;
    }

    int hash(const std::string& s) {
        int val = 0;
        for (char t: s) {
            val += (t + 1) * 293;
            val %= n;
        }
        return val;
    }

    int add(Graph& g, std::vector<Graph>& graphs, const std::string& s) {
		int i = hash(s);
        for (int j = 0; j < n; j++) {
            g.gnodes[i].color = sf::Color::Yellow;
            graphs.emplace_back(); graphs.back().copy(g, 1);
            g.gnodes[i].color = defnodecol;
            if (vals[i].empty() || vals[i][0] == '#') break;
            i = (i + 1) % n;
        }
        g.gnodes[i].text = s;
        graphs.emplace_back(); graphs.back().copy(g, 1);
		vals[i] = s;
        return i;
	}
	
	int del(Graph& g, std::vector<Graph>& graphs, const std::string& s) {
		int i = hash(s);
		for (int j = 0; j < n; j++) {
            g.gnodes[i].color = sf::Color::Yellow;
            graphs.emplace_back(); graphs.back().copy(g, 2);
            g.gnodes[i].color = defnodecol;
			if (vals[i] == s) {
                g.gnodes[i].text = "#";
                graphs.emplace_back(); graphs.back().copy(g, 2);
                vals[i] = "#";
                return i;
            }
			if (vals[i].empty()) break;
			i = (i + 1) % n;
		}
        return -1;
	}

    int find(Graph& g, std::vector<Graph>& graphs, const std::string& s) {
		int i = hash(s);
		for (int j = 0; j < n; j++) {
            g.gnodes[i].color = sf::Color::Yellow;
            graphs.emplace_back(); graphs.back().copy(g, 3);
            g.gnodes[i].color = defnodecol;
			if (vals[i] == s) {
                g.gnodes[i].color = sf::Color::Cyan;
                graphs.emplace_back(); graphs.back().copy(g, 3);
                g.gnodes[i].color = defnodecol;
                graphs.emplace_back(); graphs.back().copy(g, 3);
                return i;
            }
			if (vals[i].empty()) break;
			i = (i + 1) % n;
		}
        return -1;
	}

    void reedge(Graph& g) {
        g.gedges.clear();
        for (int i = 0; i + 1 < n; i++) {
            g.gedges.emplace_back(g.gnodes[i], g.gnodes[i + 1]);
        }
    }

    void recreate(Graph& g) {
        float currentpos = 240.0f;
        float spacing = 600.0f / (n + 1);
        g.gnodes.clear();
        for (int i = 0; i < n; i++) {
            currentpos += spacing;
            g.gnodes.emplace_back(vals[i], sf::Vector2f{currentpos, 300.0f});
        }
        reedge(g);
    }

    std::map<std::string, int> cnv;

    void load(const Data& data, const Graph& f, Graph& g, std::vector<Graph>& graphs) {
        graphs.clear();
        resized = (n != (int)data.textforms.size());
        n = (int)data.textforms.size();
        if (resized) {
            vals.assign(n, "");
            recreate(g);
            graphs.emplace_back(); graphs.back().copy(g, 0);
            for (const Textform& t: data.textforms) {
                if (!t.text.empty()) {
                    add(g, graphs, t.text);
                }
            }
        } else {
            graphs.emplace_back(); graphs.back().copy(g, 0);
            cnv.clear();
            for (const std::string& t: vals) {
                if (!t.empty() && t[0] != '#') cnv[t] -= 1;
            }
            for (const Textform& t: data.textforms) {
                if (!t.text.empty() && t.text[0] != '#') cnv[t.text] += 1;
            }
            for (const auto& x: cnv) {
                for (int i = 0; i > x.second; i--) {
                    del(g, graphs, x.first);
                }
            }
            for (const auto& x: cnv) {
                for (int i = 0; i < x.second; i++) {
                    add(g, graphs, x.first);
                }
            }
        }

        if (data.lstfocus != -1) {
            const std::string& x = data.textforms[data.lstfocus].text;
            if (!x.empty()) {
                find(g, graphs, x);
            }
        }
        
        if (!stepbystep) {
            reverse(graphs.begin(), graphs.end());
        }
    }
};