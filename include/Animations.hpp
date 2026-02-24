#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Graph.hpp>

struct Animations {
    clock_t start, duration;
    Graph g, h, F;

    std::unordered_map<int, int> reid;
    void load(const Graph& G, const Graph& H) {
        reid.clear();
        int N = 0, M = 0;
        
        for (const Gnode& t: G.gnodes) {
            reid[t.id] = N++;
        }
        for (const Gnode& t: H.gnodes) {
            if (!reid.count(t.id)) reid[t.id] = N++;
        }
        g.gnodes.assign(N, Gnode("", {480.0f, -120.0f}, charcoal - solid));
        h.gnodes.assign(N, Gnode("", {480.0f, 600.00f}, charcoal - solid));
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
            reid[t.a->id ^ t.b->id] = M++;
        }
        for (const Gedge& t: H.gedges) {
            if (!reid.count(t.a->id ^ t.b->id)) reid[t.a->id ^ t.b->id] = M++;
        }
        g.gedges.assign(M, Gedge(g.gnodes[0], g.gnodes[0], 1, charcoal - solid));
        h.gedges.assign(M, Gedge(h.gnodes[0], h.gnodes[0], 1, charcoal - solid));
        F.gedges.assign(M, Gedge(F.gnodes[0], F.gnodes[0], 1, charcoal - solid));
        for (const Gedge& t: G.gedges) {
            int p = reid[t.a->id ^ t.b->id];
            F.gedges[p].a = &F.gnodes[reid[t.a->id]];
            F.gedges[p].b = &F.gnodes[reid[t.b->id]];
            g.gedges[p].color.a = 255;
        }
        for (const Gedge& t: H.gedges) {
            int p = reid[t.a->id ^ t.b->id];
            F.gedges[p].a = &F.gnodes[reid[t.a->id]];
            F.gedges[p].b = &F.gnodes[reid[t.b->id]];
            h.gedges[p].color.a = 255;
        }
    }

    void load(const Graph& G, const Graph& H, float t) {
        animating = 1;
        load(G, H);
        start = clock();
        duration = t * CLOCKS_PER_SEC;
        buttonevent[1] = 0;
        tick();
    }

    void tick() {
        float r = 1.0f * (clock() - start) / duration;
        if (r > 1) {
            animating = 0;
            return;
        }
        r *= r * (3 - r * 2);
        float R = 1.0f - r;
        int N = (int)F.gnodes.size(), M = (int)F.gedges.size();
        for (int i = 0; i < N; i++) {
            F.gnodes[i].pos = (R * g.gnodes[i].pos + r * h.gnodes[i].pos);
            F.gnodes[i].color = R * g.gnodes[i].color + r * h.gnodes[i].color;
        }
        for (int i = 0; i < M; i++) {
            F.gedges[i].color = R * g.gedges[i].color + r * h.gedges[i].color;
        }
    }
    
    void display() {
        if (!animating) return;
        F.display();
    }
};
