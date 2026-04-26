#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <CustomDraws.hpp>

struct Background {
    std::vector<sf::RectangleShape> panels;
    std::vector<sf::RectangleShape> groupers;
    std::vector<sf::RectangleShape> separators;
    std::vector<sf::Texture> icons;
    std::vector<sf::Sprite> icondraws;
    std::vector<sf::Text> labels;

    void init() {
        panels.resize(3);
        panels[0].setSize({240, 600});
        panels[0].setPosition({0, 0});
        panels[0].setFillColor(Wwhite2);
        panels[1].setSize({600, 600});
        panels[1].setPosition({240, 0});
        panels[1].setFillColor(sf::Color::White);
        panels[2].setSize({240, 600});
        panels[2].setPosition({840, 0});
        panels[2].setFillColor(Wwhite2);

        groupers.resize(3);
        groupers[0].setSize({210, 63});
        groupers[0].setPosition({15, 15});
        groupers[0].setFillColor(Wwhite2);
        groupers[1].setSize({210, 92});
        groupers[1].setPosition({15, 93});
        groupers[1].setFillColor(Wwhite2);
        groupers[2].setSize({210, 388});
        groupers[2].setPosition({15, 200});
        groupers[2].setFillColor(Wwhite2);

        separators.resize(2);
        separators[0].setSize({1, 600});
        separators[0].setPosition({240, 0});
        separators[0].setFillColor(Wsilver);
        separators[1].setSize({1, 600});
        separators[1].setPosition({840, 0});
        separators[1].setFillColor(Wsilver);

        icons.resize(3);
        icons[0].loadFromFile("assets/animation.png");
        icons[0].setSmooth(1);
        icons[1].loadFromFile("assets/structures.png");
        icons[1].setSmooth(1);
        icons[2].loadFromFile("assets/data.png");
        icons[2].setSmooth(1);
        int iconn = (int)icons.size();
        icondraws.resize(iconn);
        icondraws[0].setPosition(sf::Vector2f{26.5f, 26.5f});
        icondraws[0].setScale(sf::Vector2f{0.125f, 0.125f});
        icondraws[1].setPosition(sf::Vector2f{26.5f, 119.0f});
        icondraws[1].setScale(sf::Vector2f{0.25f, 0.25f});
        icondraws[2].setPosition(sf::Vector2f{26.5f, 212.5f});
        icondraws[2].setScale(sf::Vector2f{0.125f, 0.125f});
        for (int i = 0; i < iconn; i++) {
            icondraws[i].setTexture(icons[i]);
        }
        labels.resize(iconn);
        labels[0].setString("Animations");
        labels[1].setString("Structures");
        labels[2].setString("Data");
        for (int i = 0; i < iconn; i++) {
            labels[i].setFont(font);
            labels[i].setCharacterSize(10);
            labels[i].setFillColor(Wonyx);
            labels[i].setPosition(icondraws[i].getPosition() + sf::Vector2f{17.0f, 34.0f} - 0.5f * sizes(labels[i].getLocalBounds()));
        }
    }
    
    void display() {
        window.clear();
        for (const auto& panel: panels) {
            window.draw(panel);
        }
        for (const auto& grouper: groupers) {
            sf::Vector2f A = grouper.getPosition(), B = A + grouper.getSize();
            roundedRectangle(A + sf::Vector2f{-1, -1}, B + sf::Vector2f{1, 1}, Wslate, 6);
            roundedRectangle(A, B, grouper.getFillColor(), 5);
        }
        for (const auto& separator: separators) {
            window.draw(separator);
        }
        for (int i = 1; i < 16; i++) {
            sf::RectangleShape lne;
            lne.setSize({1, 600});
            lne.setPosition({240 + 600.0f * i / 16.0f, 0});
            lne.setFillColor(Wwhite);
            window.draw(lne);
        }
        for (int i = 1; i < 16; i++) {
            sf::RectangleShape lne;
            lne.setSize({600, 1});
            lne.setPosition({240, 600.0f * i / 16.0f});
            lne.setFillColor(Wwhite);
            window.draw(lne);
        }
        for (const auto& icondraw: icondraws) {
            window.draw(icondraw);
        }
        for (const auto& label: labels) {
            window.draw(label);
        }
    }
};