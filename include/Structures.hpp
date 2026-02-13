#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Linkedlist.hpp>
#include <Animations.hpp>

struct Structures {
    Graph graph, graph2;
    Animations animations;
    int mode;
    Linkedlist linkedlist;
    Data* datapnt;

    Structures() {
        mode = 2;
        datapnt = nullptr;
    }
    
    void check() {
        graph.check();
    }

    void tick() {
        if (!animating) {
            load(*datapnt);
            if (buttonevent[1]) {
                animations.load(graph, graph2, 1.5f);
            }
        } else {
            animations.tick();
            if (!animating) {
                graph = graph2;
            }
        }
        graph.tick();
    }

    void display() {
        if (animating) {
            animations.display();
        } else {
            graph.display();
        }
    }

    void load(Data& data) {
        if (!datapnt) datapnt = &data;
        graph2.clear();
        if (mode == 2) {
            linkedlist.load(*datapnt, graph2);
        }
    }
};