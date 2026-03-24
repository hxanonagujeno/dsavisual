#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>

sf::ConvexShape shape(20);

void roundedRectangle(sf::Vector2f A, sf::Vector2f B, sf::Color col, float radius = 10) {
    assert(A.x <= B.x);
    assert(A.y <= B.y);
    radius = std::min(radius, std::min(B.x - A.x, B.y - A.y) * 0.5f);
    for (int i = 0; i <= 3; i++) {
        sf::Vector2f CPoint((i <= 1? A.x + radius: B.x - radius), (i == 0 || i == 3? A.y + radius: B.y - radius));
        float CAngle = pi * -0.5f - i * pi * 0.5f;
        for (int j = 0; j <= 4; ++j) {
            shape.setPoint(i * 5 + j, {CPoint.x + radius * std::cos(CAngle), CPoint.y + radius * std::sin(CAngle)});
            CAngle -= pi * 0.125f;
        }
    }
    shape.setFillColor(col);
    window.draw(shape);
}

sf::ConvexShape bottomshape(12);

void roundedRectangleBottom(sf::Vector2f A, sf::Vector2f B, sf::Color col, float radius) {
    assert(A.x <= B.x);
    assert(A.y <= B.y);
    radius = std::min(radius, std::min(B.x - A.x, B.y - A.y) * 0.5f);
    bottomshape.setPoint(0, {B.x, 0.5f * (A.y + B.y)});
    bottomshape.setPoint(1, {A.x, 0.5f * (A.y + B.y)});
    for (int i = 1; i <= 2; i++) {
        sf::Vector2f CPoint((i <= 1? A.x + radius: B.x - radius), (i == 0 || i == 3? A.y + radius: B.y - radius));
        float CAngle = pi * -0.5f - i * pi * 0.5f;
        for (int j = 0; j <= 4; ++j) {
            bottomshape.setPoint(i * 5 + j - 3, {CPoint.x + radius * std::cos(CAngle), CPoint.y + radius * std::sin(CAngle)});
            CAngle -= pi * 0.125f;
        }
    }
    bottomshape.setFillColor(col);
    window.draw(bottomshape);
}

void customButton(sf::RectangleShape shape){
    sf::Vector2f A = shape.getPosition(), B = A + shape.getSize();
    sf::Color col = shape.getFillColor();
    roundedRectangle(A + sf::Vector2f{-1, -1}, B + sf::Vector2f{1, 1}, Wonyx, 6);
    roundedRectangle(A, B, Wwhite, 5);
    roundedRectangle(A + sf::Vector2f{1, 1}, B + sf::Vector2f{-1, -1}, col, 4);
    roundedRectangleBottom(A + sf::Vector2f{1, 1}, B + sf::Vector2f{-1, -1}, {0, 0, 0, 20}, 4);
}

void customButtonHighlight(sf::RectangleShape shape){
    sf::Vector2f A = shape.getPosition(), B = A + shape.getSize();
    sf::Color col = shape.getFillColor();
    roundedRectangle(A + sf::Vector2f{-1, -1}, B + sf::Vector2f{1, 1}, Wdarkcyan, 6);
    roundedRectangle(A, B, Wcyan, 5);
    roundedRectangle(A + sf::Vector2f{1, 1}, B + sf::Vector2f{-1, -1}, col, 4);
    roundedRectangleBottom(A + sf::Vector2f{1, 1}, B + sf::Vector2f{-1, -1}, {0, 255, 255, 20}, 4);
}