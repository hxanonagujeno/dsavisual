#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Graph.hpp>

struct Animations {
    clock_t start, duration;
    Graph g, h, F;

    std::unordered_map<int, int> reid;
    void play(const Graph& G, const Graph& H) {
        reid.clear();
        int N = 0;
        F.gedges.clear();
        for (const Gnode& t: G.gnodes) {
            reid[t.id] = N++;
        }
        for (const Gnode& t: H.gnodes) {
            if (!reid.count(t.id)) reid[t.id] = N++;
        }
        g.gnodes.assign(N, Gnode("", {480.0f, -240.0f}, {128, 128, 128, 255}));
        h.gnodes.assign(N, Gnode("", {480.0f, 720.00f}, {128, 128, 128, 255}));
        F.gnodes.resize(N);
        for (const Gnode& t: G.gnodes) {
            int p = reid[t.id];
            F.gnodes[p].text = t.text;
            g.gnodes[p].copy(t);
        }
        for (const Gnode& t: H.gnodes) {
            int p = reid[t.id];
            F.gnodes[p].text = t.text;
            h.gnodes[p].copy(t);
        }
        for (const Gedge& t: G.gedges) {
            int u = reid[t.a->id], v = reid[t.b->id];
            F.gedges.emplace_back(F.gnodes[u], F.gnodes[v]);
        }
    }

    void tick(const Graph& G, const Graph& H, float t) {
        if (!animating) {
            if (buttonevent[1]) {
                animating = 1;
                play(G, H);
                start = clock();
                duration = t * CLOCKS_PER_SEC;
                buttonevent[1] = 0;
            }
            return;
        }
        float r = 1.0f * (clock() - start) / duration;
        if (r > 1) {
            animating = 0;
            return;
        }
        // std::cerr << "PROGRESS: " << r << std::endl;
        float R = 1.0f - r;
        int N = (int)F.gnodes.size();
        for (int i = 0; i < N; i++) {
            F.gnodes[i].pos = (r * g.gnodes[i].pos + R * h.gnodes[i].pos);
            F.gnodes[i].color.r = (r * g.gnodes[i].color.r + R * h.gnodes[i].color.r);
            F.gnodes[i].color.g = (r * g.gnodes[i].color.g + R * h.gnodes[i].color.g);
            F.gnodes[i].color.b = (r * g.gnodes[i].color.b + R * h.gnodes[i].color.b);
            F.gnodes[i].color.a = (r * g.gnodes[i].color.a + R * h.gnodes[i].color.a);
        }
    }
    
    void display() {
        if (animating) {
            F.display();
        }
    }
};
