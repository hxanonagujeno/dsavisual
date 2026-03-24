#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Button.hpp>

struct Controls {
    std::vector<Button> buttons;

    Controls() {
        buttons.emplace_back(sf::Vector2f{84.0f, 18.0f}, sf::Vector2f{72.00f, 24.0f}, "Animate!", 1, 12);
        buttons.emplace_back(sf::Vector2f{24.0f, 78.0f}, sf::Vector2f{72.00f, 24.0f}, "Steps off", 8, 12);
        buttons.emplace_back(sf::Vector2f{144.f, 78.0f}, sf::Vector2f{72.00f, 24.0f}, "x1", 9, 12);
        buttons.emplace_back(sf::Vector2f{4.00f, 138.f}, sf::Vector2f{72.00f, 24.0f}, "Linked list", 2, 12);
        buttons.emplace_back(sf::Vector2f{84.0f, 138.f}, sf::Vector2f{72.00f, 24.0f}, "L. probing", 3, 12);
        buttons.emplace_back(sf::Vector2f{164.f, 138.f}, sf::Vector2f{72.00f, 24.0f}, "2-3-4", 4, 12);
        buttons.emplace_back(sf::Vector2f{4.00f, 198.f}, sf::Vector2f{72.00f, 24.0f}, "Trie", 5, 12);
        buttons.emplace_back(sf::Vector2f{84.0f, 198.f}, sf::Vector2f{72.00f, 24.0f}, "Prim", 6, 12);
        buttons.emplace_back(sf::Vector2f{164.f, 198.f}, sf::Vector2f{72.00f, 24.0f}, "Dijkstra", 7, 12);
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