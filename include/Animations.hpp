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
        int N = 0, M = 0;
        
        for (const Gnode& t: G.gnodes) {
            reid[t.id] = N++;
        }
        for (const Gnode& t: H.gnodes) {
            if (!reid.count(t.id)) reid[t.id] = N++;
        }
        g.gnodes.assign(N, Gnode("", {480.0f, -240.0f}, {128, 128, 128, 0}));
        h.gnodes.assign(N, Gnode("", {480.0f, 720.00f}, {128, 128, 128, 0}));
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
        g.gedges.assign(M, Gedge(g.gnodes[0], g.gnodes[0], 1, {128, 128, 128, 0}));
        h.gedges.assign(M, Gedge(h.gnodes[0], h.gnodes[0], 1, {128, 128, 128, 0}));
        F.gedges.assign(M, Gedge(F.gnodes[0], F.gnodes[0], 1, {128, 128, 128, 0}));
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
            F.gnodes[i].color.r = (R * g.gnodes[i].color.r + r * h.gnodes[i].color.r);
            F.gnodes[i].color.g = (R * g.gnodes[i].color.g + r * h.gnodes[i].color.g);
            F.gnodes[i].color.b = (R * g.gnodes[i].color.b + r * h.gnodes[i].color.b);
            F.gnodes[i].color.a = (R * g.gnodes[i].color.a + r * h.gnodes[i].color.a);
        }
        for (int i = 0; i < M; i++) {
            F.gedges[i].color.r = (R * g.gedges[i].color.r + r * h.gedges[i].color.r);
            F.gedges[i].color.g = (R * g.gedges[i].color.g + r * h.gedges[i].color.g);
            F.gedges[i].color.b = (R * g.gedges[i].color.b + r * h.gedges[i].color.b);
            F.gedges[i].color.a = (R * g.gedges[i].color.a + r * h.gedges[i].color.a);
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
        tick();
    }
    
    void display() {
        tick();
        if (animating) {
            F.display();
        }
    }
};
