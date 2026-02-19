#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Linkedlist.hpp>
#include <Linearprobing.hpp>
#include <Animations.hpp>

struct Structures {
    Graph graph, graph2;
    std::vector<Graph> graphs;
    Animations animations;
    Linkedlist linkedlist;
    Linearprobing linearprobing;
    Data* datapnt;

    Structures() {
        structuremode = 1;
        datapnt = nullptr;
        graphs.clear();
    }
    
    void check() {
        graph.check();
    }

    void tick() {
        if (!animating) {
            if (buttonevent[1]) {
                load(*datapnt);
            }
            if (!graphs.empty()) {
                graph2.copy(graphs.back());
                graphs.pop_back();
                animations.load(graph, graph2, 1.5f);
            }
        } else {
            animations.tick();
            if (!animating) {
                graph.copy(graph2);
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
        if (structuremode == 1) {
            linkedlist.load(*datapnt, graph, graph2, graphs);
            graphs.clear();
            graph.copy(graph2);
        }
        if (structuremode == 2) {
            linkedlist.load(*datapnt, graph, graph2, graphs);
        }
        if (structuremode == 3) {
            linearprobing.load(*datapnt, graph, graph2, graphs);
        }
    }
};