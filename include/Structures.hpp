#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Linkedlist.hpp>
#include <Linearprobing.hpp>
#include <Twothreefour.hpp>
#include <Trie.hpp>
#include <Kruskal.hpp>
#include <Dijkstra.hpp>
#include <Animations.hpp>

struct Structures {
    Graph graph, graph2;
    std::vector<Graph> graphs;
    Animations animations;
    Linkedlist linkedlist;
    Linearprobing linearprobing;
    Twothreefour twothreefour;
    Kruskal kruskal;
    Dijkstra dijkstra;
    Trie trie;
    Data* datapnt;
    int curtype = 2;

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
                animations.load(graph, graph2, animationtime);
            }
        } else {
            animations.tick();
            if (!animating) {
                graph.copy(graph2);
                if (!graphs.empty()) {
                    graph2.copy(graphs.back());
                    graphs.pop_back();
                    animations.load(graph, graph2, animationtime);
                }
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
        } else {
            linkedlist.clear();
        }
        if (structuremode == 3) {
            linearprobing.load(*datapnt, graph, graph2, graphs);
        } else {
            linearprobing.clear();
        }
        if (structuremode == 4) {
            twothreefour.load(*datapnt, graph, graph2, graphs);
        } else {
            twothreefour.clear();
        }
        if (structuremode == 5) {
            trie.load(*datapnt, graph, graph2, graphs);
        } else {
            trie.clear();
        }
        if (structuremode == 6) {
            kruskal.load(*datapnt, graph, graph2, graphs);
        } else {
            kruskal.clear();
        }
        if (structuremode == 7) {
            dijkstra.load(*datapnt, graph, graph2, graphs);
        } else {
            dijkstra.clear();
        }
    }
};