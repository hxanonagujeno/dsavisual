#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

sf::Vector2f zero2f = {0.0f, 0.0f};
sf::Color ivory = {232, 232, 232};
sf::Color silver = {192, 192, 192};
sf::Color slate = {160, 160, 160};
sf::Color gray = {128, 128, 128};
sf::Color charcoal = {96, 96, 96};
sf::Color onyx = {36, 36, 36};
sf::Color transparent = {0, 0, 0, 128};
sf::Color solid = {0, 0, 0, 255};

template<class T> bool mnz(T& x, const T& y) {
    return (x > y? (x = y, 1): 0);
}

template<class T> bool mxz(T& x, const T& y) {
    return (x < y? (x = y, 1): 0);
}

int rani() {
	int s = 0;
	for (int i = 0; i < 3; i++) s ^= rand() << (i * 14);
	return s;
}

int rani(int l, int r) {
    return abs(rani()) % (r - l + 1) + l;
}

int sqr(int x) {
    return x * x;
}

int sqrdis(const sf::Vector2i& a, const sf::Vector2i& b) {
    return sqr(a.x - b.x) + sqr(a.y - b.y);
}

int sqrlen(const sf::Vector2i& a) {
    return sqr(a.x) + sqr(a.y);
}

sf::Vector2f poses(const sf::FloatRect& a) {
    return sf::Vector2f(a.left, a.top);
}

sf::Vector2f sizes(const sf::FloatRect& a) {
    return sf::Vector2f(a.width, a.height);
}

bool animating = 0;
bool stepbystep = 0;

bool buttonevent[128];

bool keyboardvis[256];

int gnodesize = 24;

extern sf::RenderWindow window;
extern sf::Event event;
extern sf::Font font;

void reglobe() {
    if (buttonevent[8]) {
        stepbystep ^= 1;
        buttonevent[8] = 0;
    }
    memset(keyboardvis, 0, sizeof(keyboardvis));
}