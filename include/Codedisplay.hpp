#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Textform.hpp>

struct Codedisplay {
    int prevstructuremode = 0;
    std::vector<Textform> textforms;
    std::bitset<128> highlight[8][8];
    
    Codedisplay() {
        textforms.emplace_back(sf::Vector2f{862.0f, 20.0f});
        file.open("assets/highlight.txt");
        int i = 0, j = 0, k = 0;
        char x; int tmp;
        while (file >> x >> tmp) {
            if (x == 'i') {
                i = tmp;
            } else 
            if (x == 'j') {
                j = tmp;
            } else 
            if (x == 'k') {
                k = tmp;
                highlight[i][j][k] = 1;
            }
        }
        for (int i = 0; i < 8; i++) {
            highlight[1][i] = highlight[2][i];
        }
        file.close();
    }

    void check() {
    }

    void tickstructure() {
        if (prevstructuremode == structuremode) return;

        if (structuremode <= 2) {
            import("assets/linkedlist.txt");
        } else 
        if (structuremode == 3) {
            import("assets/linearprobing.txt");
        } else
        if (structuremode == 4) {
            import("assets/twothreefour.txt");
        } else 
        if (structuremode == 5) {
            import("assets/trie.txt");
        } else 
        if (structuremode == 6) {
            import("assets/prim.txt");
        } else 
        if (structuremode == 7) {
            import("assets/dijkstra.txt");
        }
        
        if (textforms.empty()) {
            textforms.emplace_back(sf::Vector2f{862.0f, 20.0f});
        }

        prevstructuremode = structuremode;
    }

    void tick() {
        tickstructure();
    }

    std::ifstream file;
    std::string line;
    void import(const char f[]) {
        file.open(f);
        int cnt = 0;
        textforms.clear();
        while (std::getline(file, line)) {
            textforms.emplace_back(sf::Vector2f{862.0f, 20.0f + 15.0f * cnt}, line);
            ++cnt;
        }
        file.close();
    }
    
    sf::RectangleShape box;
    void display() {
        box.setPosition(textforms[0].pos - sf::Vector2f{2.0f, 2.0f});
        sf::Vector2f tmp = sf::Vector2f{862.0f, 20.0f + 15.0f * (highlight[structuremode][codesection].count() - 1)};
        box.setSize(tmp + textforms[0].sz - textforms[0].pos + sf::Vector2f{4.0f, 4.0f});
        customButton(box);

        int cnt = 0;
        for (int i = 0; i < (int)textforms.size(); i++) {
            if (highlight[structuremode][codesection][i + 1]) {
                textforms[i].pos.y = 20.0f + 15.0f * cnt;
                textforms[i].color = sf::Color::White;
                textforms[i].display();
                ++cnt;
            }
        }
    }
};