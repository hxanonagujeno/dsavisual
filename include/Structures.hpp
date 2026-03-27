#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Linkedlist.hpp>
#include <Linearprobing.hpp>
#include <Twothreefour.hpp>
#include <Trie.hpp>
#include <Prim.hpp>
#include <Dijkstra.hpp>
#include <Animations.hpp>

struct Structures {
    Graph graph, graph2;
    std::vector<Graph> graphs;
    Animations animations;
    Linkedlist linkedlist;
    Linearprobing linearprobing;
    Twothreefour twothreefour;
    Prim prim;
    Dijkstra dijkstra;
    Trie trie;
    Data* datapnt;
    int curtype = 2;
    int curframe = 0;
    bool nxtframe = 0, prvframe = 0, allframe = 0;

    Structures() {
        structuremode = 1;
        datapnt = nullptr;
        graphs.clear();
    }
    
    void check() {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) {
                prvframe = 1;
            } else 
            if (event.key.code == sf::Keyboard::Right) {
                nxtframe = 1;
            } else 
            if (event.key.code == sf::Keyboard::Enter) {
                allframe = 1;
            }
        }
        graph.check();
    }

    void tick() {
        if (!stepbystep) {
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
        } else {
            if (buttonevent[1]) {
                load(*datapnt);
                graph2.copy(graphs[curframe = 0]);
                animations.load(graph, graph2, animationtime);
            }
            if (animating || showsteps) {
                if (allframe) {
                    reverse(graphs.begin(), graphs.end());
                    for (int i = 0; i <= curframe; i++) {
                        if (!graphs.empty()) {
                            graphs.pop_back();
                        }
                    }
                    stepbystep = 0;
                    showsteps = 0;
                } else {
                    if (!showsteps) {
                        animations.tick();
                        if (nxtframe || prvframe) {
                            animating = 0;
                        }
                        if (!animating) {
                            graph.copy(graph2);
                            showsteps = 1;
                        }
                    } else {
                        if (!animating) {
                            if (nxtframe) {
                                if (curframe + 1 < (int)graphs.size()) {
                                    graph2.copy(graphs[++curframe]);
                                    animations.load(graph, graph2, animationtime);
                                    showsteps = 0;
                                } else {
                                    graphs.clear();
                                    showsteps = 0;
                                    animating = 0;
                                }
                            } else
                            if (prvframe) {
                                if (curframe - 1 >= 0) {
                                    graph2.copy(graphs[--curframe]);
                                    animations.load(graph, graph2, animationtime);
                                    showsteps = 0;
                                }
                            }
                        } else {
                            showsteps = 0;
                        }
                    }
                }
            }
        }
        nxtframe = 0;
        prvframe = 0;
        allframe = 0;
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
            prim.load(*datapnt, graph, graph2, graphs);
        } else {
            prim.clear();
        }
        if (structuremode == 7) {
            dijkstra.load(*datapnt, graph, graph2, graphs);
        } else {
            dijkstra.clear();
        }
    }
};