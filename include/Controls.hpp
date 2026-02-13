#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Button.hpp>

struct Controls {
    std::vector<Button> buttons;

    Controls() {
        buttons.emplace_back(sf::Vector2f{0.00f, 0.00f}, sf::Vector2f{240.0f, 60.0f}, "ANIMATE", 1, 36);
        buttons.emplace_back(sf::Vector2f{0.00f, 60.0f}, sf::Vector2f{80.00f, 60.0f}, "LINKED\nLIST", 2, 16);
        buttons.emplace_back(sf::Vector2f{80.0f, 60.0f}, sf::Vector2f{80.00f, 60.0f}, "LINEAR\nPROBING", 3, 16);
        buttons.emplace_back(sf::Vector2f{160.f, 60.0f}, sf::Vector2f{80.00f, 60.0f}, "2-3-4", 4, 20);
        buttons.emplace_back(sf::Vector2f{0.00f, 120.f}, sf::Vector2f{80.00f, 60.0f}, "TRIE", 5, 20);
        buttons.emplace_back(sf::Vector2f{80.0f, 120.f}, sf::Vector2f{80.00f, 60.0f}, "KRUSKAL", 6, 18);
        buttons.emplace_back(sf::Vector2f{160.f, 120.f}, sf::Vector2f{80.00f, 60.0f}, "DIJKSTRA", 7, 18);
    }

    void check() {
        for (Button& t: buttons) {
            t.check();
        }
    }

    void tick() {
        for (Button& t: buttons) {
            t.tick();
        }
    }

    void display() {
        for (Button& t: buttons) {
            t.display();
        }
    }
};