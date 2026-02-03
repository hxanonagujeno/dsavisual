#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Button.hpp>
#include <Globals.hpp>

struct Controls {
    std::vector<Button> buttons;

    Controls() {
        buttons.emplace_back(sf::Vector2f{0.f, 0.f}, sf::Vector2f{100.f, 100.f});
        buttons.emplace_back(sf::Vector2f{100.f, 0.f}, sf::Vector2f{100.f, 100.f});
        buttons.emplace_back(sf::Vector2f{200.f, 0.f}, sf::Vector2f{100.f, 100.f});
        buttons.emplace_back(sf::Vector2f{300.f, 0.f}, sf::Vector2f{100.f, 100.f});
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