#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Button.hpp>

struct Controls {
    std::vector<Button> buttons;

    Controls() {
        buttons.emplace_back(sf::Vector2f{0.000f, 0.0f}, sf::Vector2f{100.0f, 100.0f});
        buttons.emplace_back(sf::Vector2f{100.0f, 0.0f}, sf::Vector2f{100.0f, 100.0f});
        buttons.emplace_back(sf::Vector2f{200.0f, 0.0f}, sf::Vector2f{100.0f, 100.0f});
        buttons.emplace_back(sf::Vector2f{300.0f, 0.0f}, sf::Vector2f{100.0f, 100.0f});
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