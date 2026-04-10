#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Textform.hpp>

struct Datagen {
    std::vector<Textform> textforms;

    std::map<std::string, int> genvis;
    std::vector<char> col[30];
    std::string nxtgenerated;
    
    void genstring() {
        genvis.clear();
        bool hasdig = 0;
        bool hasabc = 0;
        for (int i = 0; i < 30; i++) {
            col[i].clear();
        }
        for (const Textform& t: textforms) {
            int sz = (int)t.text.size();
            for (int i = 0; i < sz; i++) {
                const char& x = t.text[i];
                col[i].emplace_back(x);
                if ('0' <= x && x <= '9') {
                    hasdig = 1;
                } 
                if ('a' <= x && x <= 'z') {
                    hasabc = 1;
                }
            }
            col[sz].emplace_back('#');
            genvis[t.text] = 1;
        }

        do {
            nxtgenerated = "";
            std::vector<char>& pul = (hasdig? (hasabc? chrtpb: chrdig): chrabc);
            for (int i = 0; i < 30; i++) {
                col[i].emplace_back((i < rani(3, 10)? pul[rani(0, (int)pul.size() - 1)]: '#'));
            }
            for (int i = 0; i < 30; i++) {
                char x = col[i][rani(0, (int)col[i].size() - 1)];
                if (x != '#') {
                    if (x != ' ' || nxtgenerated.empty() || nxtgenerated.back() != ' ') {
                        nxtgenerated += x;
                    }
                } else {
                    break;
                }
            }
        } while (genvis[nxtgenerated]);
    }

    void gennumber() {
        genvis.clear();
        for (int i = 0; i < 30; i++) {
            col[i].clear();
        }
        for (const Textform& t: textforms) {
            int sz = (int)t.text.size();
            for (int i = 0; i < sz; i++) {
                const char& x = t.text[i];
                if (!('0' <= x && x <= '9')) {
                    break;
                }
                col[i].emplace_back(x);
            }
            col[sz].emplace_back('#');
            genvis[t.text] = 1;
        }

        do {
            nxtgenerated = "";
            std::vector<char>& pul = chrdig;
            for (int i = 0; i < 30; i++) {
                col[i].emplace_back((i < rani(3, 10)? pul[rani(0, (int)pul.size() - 1)]: '#'));
            }
            for (int i = 0; i < 30; i++) {
                char x = col[i][rani(0, (int)col[i].size() - 1)];
                if (x != '#') {
                    nxtgenerated += x;
                } else {
                    break;
                }
            }
        } while (genvis[nxtgenerated]);
    }

    std::unordered_map<int, int> cnt;
    std::map<std::pair<int, int>, int> edgvis;
    int minu, maxu;
    int minw, maxw;

    void genedge() {
        minu = INT_MAX;
        maxu = INT_MIN;
        minw = INT_MAX;
        maxw = INT_MIN;
        cnt.clear();
        edgvis.clear();
        for (const Textform& T: textforms) {
            auto t = parse(T.text);
            for (int i = 0; i < std::min(2, (int)t.size()); i++) {
                int u = t[i];
                mxz(maxu, u);
                mnz(minu, u);
                ++cnt[u];
            }
            if ((int)t.size() <= 1) continue;
            if (t[0] == t[1]) continue;
            edgvis[{std::min(t[0], t[1]), std::max(t[0], t[1])}] = 1;
            int w = ((int)t.size() <= 2? 1: t[2]);
            mxz(maxw, w);
            mnz(minw, w);
        }

        if (minw == INT_MAX) {
            int u = rani(1, 99), v;
            do {
                v = rani(1, 99);
            } while (u == v);
            nxtgenerated = std::to_string(u) + ' ' + std::to_string(v) + ' ' + std::to_string(ranlg(1, 999));
            return;
        }

        std::vector<std::pair<int, int>> col;
        for (const auto& x: cnt) {
            col.emplace_back(x);
        }

        {
            int u;
            do {
                u = ranlg(std::max(1, minu / 2 - 2), std::min(999999999, maxu * 2 + 2));
            } while (cnt.count(u));
            col.emplace_back(u, 3);
            cnt[u] = 1;
        }

        std::sort(col.begin(), col.end(), [](const std::pair<int, int>& x, const std::pair<int, int>& y) {
            return x.second > y.second;
        });

        int u, v, w;
        do {
            u = col[rani(0, rani(0, (int)col.size() - 1))].first;
            v = col[rani(0, rani(0, (int)col.size() - 1))].first;
            if (u > v) std::swap(u, v);
        } while (u == v || edgvis.count({u, v}));
        w = ranlg(std::max(1, minw / 2 - 2), std::min(999999999, maxw * 2 + 2));
        nxtgenerated = std::to_string(u) + ' ' + std::to_string(v) + ' ' + std::to_string(w);
    }

    void generate() {
        if (structuremode == 2 || structuremode == 5) {
            genstring();
            return;
        }

        if (structuremode == 3) {
            if (rand() & 1) {
                genstring();
            } else {
                nxtgenerated = "";
            }
            return;
        }
        
        if (structuremode == 4) {
            gennumber();
            return;
        }
        
        if (structuremode == 6) {
            genedge();
            return;
        }
        
        if (structuremode == 7) {
            genedge();
            return;
        }
    }
};