#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Button.hpp>

struct Controls {
    std::vector<Button> buttons;
    int deltasize = 0;
    int checkwait = 0;

    Controls() {
        buttons.emplace_back(sf::Vector2f{148.f, 20.0f}, sf::Vector2f{72.00f, 53.0f}, "Animate!", 1, 12);
        buttons.emplace_back(sf::Vector2f{71.0f, 20.0f}, sf::Vector2f{72.00f, 24.0f}, "Steps off", 8, 12);
        buttons.emplace_back(sf::Vector2f{71.0f, 49.0f}, sf::Vector2f{72.00f, 24.0f}, "0.50s", 9, 12);
        buttons.emplace_back(sf::Vector2f{71.0f, 98.0f}, sf::Vector2f{72.00f, 24.0f}, "Linked list", 2, 12);
        buttons.emplace_back(sf::Vector2f{148.f, 98.0f}, sf::Vector2f{72.00f, 24.0f}, "L. probing", 3, 12);
        buttons.emplace_back(sf::Vector2f{71.0f, 127.f}, sf::Vector2f{72.00f, 24.0f}, "2-3-4", 4, 12);
        buttons.emplace_back(sf::Vector2f{148.f, 127.f}, sf::Vector2f{72.00f, 24.0f}, "Trie", 5, 12);
        buttons.emplace_back(sf::Vector2f{71.0f, 156.f}, sf::Vector2f{72.00f, 24.0f}, "Prim", 6, 12);
        buttons.emplace_back(sf::Vector2f{148.f, 156.f}, sf::Vector2f{72.00f, 24.0f}, "Dijkstra", 7, 12);
        buttons.emplace_back(sf::Vector2f{71.0f, 205.f}, sf::Vector2f{72.00f, 24.0f}, "Clear", 10, 12);
        buttons.emplace_back(sf::Vector2f{148.f, 205.f}, sf::Vector2f{72.00f, 24.0f}, "Generate", 11, 12);
        buttons.emplace_back(sf::Vector2f{71.0f, 234.f}, sf::Vector2f{72.00f, 24.0f}, "Clear line", 12, 12);
        buttons.emplace_back(sf::Vector2f{148.f, 234.f}, sf::Vector2f{72.00f, 24.0f}, "Gen line", 13, 12);
    }

    void check() {
        for (Button& t: buttons) {
            t.check();
        }
        if (!checkwait && event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Add || (event.key.code == sf::Keyboard::Equal && event.key.shift)) {
                deltasize = 1;
                checkwait = 1;
            } else 
            if (event.key.code == sf::Keyboard::Hyphen || event.key.code == sf::Keyboard::Subtract) {
                deltasize = -1;
                checkwait = 1;
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            checkwait = 0;
        }
    }

    void tick() {
        for (Button& t: buttons) {
            t.tick();
        }
        gnodesize += deltasize;
        mnz(gnodesize, 30);
        mxz(gnodesize, 10);
        deltasize = 0;
    }

    void display() {
        for (Button& t: buttons) {
            t.display();
        }
    }
};