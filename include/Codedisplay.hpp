#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Textform.hpp>

struct Codedisplay {
    int prevstructuremode = 0;
    std::vector<Textform> textforms;
    std::bitset<32> highlight[8][32];
    
    Codedisplay() {
        textforms.emplace_back(sf::Vector2f{870.0f, 30.0f});
        file.open("assets/highlight.txt");
        int i = 0, j = 0, k = 0;
        char x; int tmp;
        file >> x >> tmp;
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
        for (int i = 0; i < 32; i++) {
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
            textforms.emplace_back(sf::Vector2f{870.0f, 30.0f});
        }

        prevstructuremode = structuremode;
    }

    void tickhighlight() {
        int n = (int)textforms.size();
        for (int i = 0; i < n; i++) {
            if (highlight[structuremode][codesection][i]) {
                textforms[i].color = Wwhite2;
            } else {
                textforms[i].color = Wivory;
            }
        }
    }

    void tick() {
        tickstructure();
        tickhighlight();
    }

    std::ifstream file;
    std::string line;
    void import(const char f[]) {
        file.open(f);
        int cnt = 0;
        textforms.clear();
        while (std::getline(file, line)) {
            textforms.emplace_back(sf::Vector2f{870.0f, 30.0f + 15.0f * cnt}, line);
            cnt++;
        }
        file.close();
    }
    
    sf::RectangleShape box;
    void display() {
        box.setPosition(textforms[0].pos - sf::Vector2f{2.0f, 2.0f});
        box.setSize(textforms.back().pos + textforms.back().sz - textforms[0].pos + sf::Vector2f{4.0f, 4.0f});
        customButton(box);

        for (Textform& t: textforms) {
            t.display();
        }
    }
};