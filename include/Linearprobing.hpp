#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Graph.hpp>

struct Linearprobing {
    int n = 0;
    std::vector<std::string> vals;
    bool resized = 0;

    int hash(const std::string& s) {
        int val = 0;
        for (char t: s) {
            val += (t + 1) * 293;
            val %= n;
        }
        return val;
    }

    int add(const std::string& s) {
		int i = hash(s);
		while (!vals[i].empty() && vals[i][0] != '#') {
			i = (i + 1) % n;
		}
		vals[i] = s;
        return i;
	}
	
	int del(const std::string& s) {
		int i = hash(s);
		for (int j = 0; j < n; j++) {
			if (vals[i] == s) return vals[i] = "#", i;
			if (vals[i].empty()) return -1;
			i = (i + 1) % n;
		}
        return -1;
	}

    int animatedadd(Graph& g, std::vector<Graph>& graphs, const std::string& s) {
		int i = hash(s);
        for (int j = 0; j < n; j++) {
            g.gnodes[i].color = sf::Color::Yellow;
            graphs.emplace_back(); graphs.back().copy(g);
            g.gnodes[i].color = silver;
            if (vals[i].empty() || vals[i][0] == '#') break;
            i = (i + 1) % n;
        }
        g.gnodes[i].text = s;
        graphs.emplace_back(); graphs.back().copy(g);
		vals[i] = s;
        return i;
	}
	
	int animateddel(Graph& g, std::vector<Graph>& graphs, const std::string& s) {
		int i = hash(s);
		for (int j = 0; j < n; j++) {
            g.gnodes[i].color = sf::Color::Yellow;
            graphs.emplace_back(); graphs.back().copy(g);
            g.gnodes[i].color = silver;
			if (vals[i] == s) {
                g.gnodes[i].text = "#";
                graphs.emplace_back(); graphs.back().copy(g);
                vals[i] = "#";
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
        float currentpos = 240.0f + 1.5f * gnodesize;
        float spacing = (n == 1? 0.0f: (480.0f - 3 * gnodesize) / (n - 1));
        g.gnodes.clear();
        for (int i = 0; i < n; i++) {
            g.gnodes.emplace_back(vals[i], sf::Vector2f{currentpos, 240.0f});
            currentpos += spacing;
        }
        reedge(g);
    }

    std::map<std::string, int> cnv;
    void preload(const Data& data, const Graph& f, Graph& g) {
        resized = (n != (int)data.textforms.size());
        if (resized) {
            n = (int)data.textforms.size();
            vals.assign(n, "");
            for (const Textform& t: data.textforms) {
                if (!t.text.empty()) add(t.text);
            }
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
        }
        recreate(g);
        if (!resized) return;
        for (int i = 0; i < n; i++) {
            if (g.gnodes[i].text == f.gnodes[i].text) {
                g.gnodes[i].id = f.gnodes[i].id;
            }
        }
    }

    void load(const Data& data, const Graph& f, Graph& g, std::vector<Graph>& graphs) {
        graphs.clear();
        resized = (n != (int)data.textforms.size());
        n = (int)data.textforms.size();
        if (resized) {
            vals.assign(n, "");
            recreate(g);
            for (const Textform& t: data.textforms) {
                if (!t.text.empty()) {
                    animatedadd(g, graphs, t.text);
                }
            }
        } else {
            cnv.clear();
            for (const std::string& t: vals) {
                if (!t.empty() && t[0] != '#') cnv[t] -= 1;
            }
            for (const Textform& t: data.textforms) {
                if (!t.text.empty() && t.text[0] != '#') cnv[t.text] += 1;
            }
            for (const auto& x: cnv) {
                for (int i = 0; i > x.second; i--) {
                    animateddel(g, graphs, x.first);
                }
            }
            for (const auto& x: cnv) {
                for (int i = 0; i < x.second; i++) {
                    animatedadd(g, graphs, x.first);
                }
            }
        }
        reverse(graphs.begin(),graphs.end());
        if (!stepbystep) { 
            while ((int)graphs.size() > 1) {
                graphs.pop_back();
            }
            if (!resized) {
                for (int i = 0; i < n; i++) {
                    if (graphs[0].gnodes[i].text != f.gnodes[i].text) {
                        graphs[0].gnodes[i].id = rani();
                    }
                }
            }
            return;
        }
    }
};