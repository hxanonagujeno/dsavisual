#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Textform.hpp>
#include <Datagen.hpp>

struct Data: Datagen {
    bool focus;
    bool add;
    bool del;
    bool bsp;
    int arrow;
    int lim;
    int lstfocus, curfocus, idfocus;

    Data() {
        textforms.emplace_back(sf::Vector2f{22.0f, 266.0f});
        focus = 0;
        add = 0;
        del = 0;
        bsp = 0;
        arrow = 0;
        lim = (600 - 263) / 15 - 1;
        lstfocus = -1;
        curfocus = -1;
        idfocus = -1;
    }

    void checktextforms() {
        for (Textform& t: textforms) {
            t.check();
        }
    }

    void checkkey() {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                add = 1;
                return;
            }
            if (event.key.code == sf::Keyboard::Delete) {
                del = 1;
                return;
            }
            if (event.key.code == sf::Keyboard::Backspace) {
                bsp = 1;
                return;
            }
            if (event.key.code == sf::Keyboard::Up) {
                arrow = -1;
                return;
            }
            if (event.key.code == sf::Keyboard::Down) {
                arrow = 1;
                return;
            }
        }
    }

    void check() {
        checktextforms();
        checkkey();
        if (animating) {
            for (Textform& t: textforms) {
                if (!t.text.empty() && t.text.back() == ' ') {
                    t.text.pop_back();
                }
            }
        }
    }

    bool tickspecials() {
        int p = std::max(lstfocus, curfocus);

        if (buttonevent[10]) {
            textforms.clear();
            textforms.emplace_back(sf::Vector2f{22.0f, 266.0f});
            buttonevent[10] = 0;
            return 1;
        }

        if (buttonevent[11]) {
            textforms.clear();
            int t = rani(5, 11);
            for (int i = 0; i < t; i++) {
                generate();
                textforms.emplace_back(sf::Vector2f{22.0f, 266.0f + 15.0f * i}, nxtgenerated);
            }
            buttonevent[11] = 0;
            return 1;
        }

        if (buttonevent[12]) {
            if (p == -1) {
                return 0;
            }
            int n = (int)textforms.size();
            if (n == 1) {
                textforms[0].text = "";
                buttonevent[12] = 0;
                return 1;
            }
            textforms.erase(textforms.begin() + p);
            for (int i = p; i < n - 1; i++) {
                textforms[i].pos += {0.0f, -15.0f};
            }
            p = std::max(0, p - 1);
            if (p < n - 1) {
                textforms[p].focus = 1;
            }
            buttonevent[12] = 0;
            return 1;
        }

        if (buttonevent[13]) {
            int n = (int)textforms.size();
            if (n == lim) return 1;
            if (p == -1) p = n - 1;
            generate();
            if (textforms[p].text.empty() || textforms[p].text[0] == ' ') {
                textforms[p].text = nxtgenerated;
                textforms[p].focus = 1;
                return 1;
            }
            textforms.emplace(textforms.begin() + p + 1, sf::Vector2f{22.0f, 266.0f + 15.0f * p});
            textforms[p + 1].text = nxtgenerated;
            for (int i = p + 1; i <= n; i++) {
                textforms[i].pos += {0.0f, 15.0f};
            }
            textforms[p].focus = 0;
            textforms[p + 1].focus = 1;
            return 1;
        }
        return 0;
    }

    void tick() {
        int n = (int)textforms.size();
        int p = -1;
        for (int i = 0; i < n; i++) {
            textforms[i].tick();
            if (textforms[i].focus) {
                p = i;
            }
        }
        lstfocus = curfocus;
        curfocus = p;
        if (tickspecials()) {
            return;
        }
        if (p == -1) {
            add = 0;
            del = 0;
            bsp = 0;
            arrow = 0;
            return;
        }
        if (keyboardvis[sf::Keyboard::Enter]) add = 0;
        if (keyboardvis[sf::Keyboard::Delete]) del = 0;
        if (keyboardvis[sf::Keyboard::Backspace]) bsp = 0;
        if (add) {
            if (n == lim) {
                add = 0;
                return;
            }
            textforms.emplace(textforms.begin() + p + 1, sf::Vector2f{22.0f, 266.0f + 15.0f * p});
            for (int i = p + 1; i <= n; i++) {
                textforms[i].pos += {0.0f, 15.0f};
            }
            textforms[p].focus = 0;
            textforms[p + 1].focus = 1;
            add = 0;
            return;
        }
        if (del) {
            if (p == n - 1) {
                del = 0;
                return;
            }
            textforms.erase(textforms.begin() + p + 1);
            for (int i = p + 1; i < n - 1; i++) {
                textforms[i].pos += {0.0f, -15.0f};
            }
            del = 0;
            return;
        }
        if (bsp) {
            if (n == 1 || !textforms[p].text.empty()) {
                bsp = 0;
                return;
            }
            textforms.erase(textforms.begin() + p);
            for (int i = p; i < n - 1; i++) {
                textforms[i].pos += {0.0f, -15.0f};
            }
            textforms[std::max(0, p - 1)].focus = 1;
            bsp = 0;
            return;
        }
        if (arrow != 0) {
            textforms[p].focus = 0;
            textforms[std::max(0, std::min(n - 1, p + arrow))].focus = 1;
            arrow = 0;
            return;
        }
    }

    sf::RectangleShape box;
    void display() {
        box.setPosition(textforms[0].pos - sf::Vector2f{2.0f, 2.0f});
        box.setSize(textforms.back().pos + textforms.back().sz - textforms[0].pos + sf::Vector2f{4.0f, 4.0f});
        customButton(box);

        for (int i = 0; i < (int)textforms.size(); i++) {
            if (animating || showsteps) {
                if (i == idfocus || i == lstfocus) {
                    textforms[i].color = Wgray;
                    idfocus = i;
                }
            } else {
                idfocus = -1;
            }
            textforms[i].display();
        }
    }

    std::ifstream file;
    std::string line;
    void import(const char f[]) {
        file.open(f);
        int cnt = 0;
        textforms.clear();
        while (cnt < 18 && std::getline(file, line)) {
            textforms.emplace_back(sf::Vector2f{22.0f, 266.0f + 15.0f * cnt}, line);
            cnt++;
        }
        file.close();
    }
};