#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

sf::Vector2f zero2f = {0.0f, 0.0f};
sf::Color silver = {192, 192, 192};

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

int sqr(int x) {
    return x * x;
}

int sqrdis(const sf::Vector2i& a, const sf::Vector2i& b) {
    return sqr(a.x - b.x) + sqr(a.y - b.y);
}

int sqrlen(const sf::Vector2i& a) {
    return sqr(a.x) + sqr(a.y);
}

sf::Vector2f sizes(const sf::FloatRect& a) {
    return sf::Vector2f(a.width, a.height);
}

int gnodesize = 24;

extern sf::RenderWindow window;
extern sf::Event event;
extern sf::Font font;