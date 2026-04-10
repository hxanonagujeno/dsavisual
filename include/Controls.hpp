#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Button.hpp>

struct Controls {
    std::vector<Button> buttons;

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