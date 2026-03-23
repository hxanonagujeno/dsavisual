#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

sf::Vector2f zero2f = {0.0f, 0.0f};
sf::Color orange = {255, 128, 0};
sf::Color ivory = {232, 232, 232};
sf::Color silver = {192, 192, 192};
sf::Color slate = {160, 160, 160};
sf::Color gray = {128, 128, 128};
sf::Color charcoal = {96, 96, 96};
sf::Color onyx = {36, 36, 36};
sf::Color Wwhite = {240, 240, 240};
sf::Color Wivory = {225, 225, 225};
sf::Color Wsilver = {212, 212, 212};
sf::Color Wslate = {198, 198, 198};
sf::Color Wgray = {174, 174, 174};
sf::Color Wonyx = {112, 112, 112};
sf::Color Wdarkcyan = {60, 127, 127};
sf::Color Wcyan = {72, 215, 251};

sf::Color nocolor = {0, 0, 0, 0};
sf::Color transparent = {0, 0, 0, 128};
sf::Color solid = {0, 0, 0, 255};

const int gnodesize = 24;
const int gedgesize = 1;
const int inf = 2e9;

const float pi = 3.14159265358793f;
const float e = 2.718281828459045f;

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

int sqrlen(const sf::Vector2i& a) {
    return sqr(a.x) + sqr(a.y);
}

int sqrdis(const sf::Vector2i& a, const sf::Vector2i& b) {
    return sqr(a.x - b.x) + sqr(a.y - b.y);
}

float sqr(float x) {
    return x * x;
}

float sqrlen(const sf::Vector2f& a) {
    return sqr(a.x) + sqr(a.y);
}

float sqrdis(const sf::Vector2f& a, const sf::Vector2f& b) {
    return sqr(a.x - b.x) + sqr(a.y - b.y);
}

sf::Vector2f poses(const sf::FloatRect& a) {
    return sf::Vector2f(a.left, a.top);
}

sf::Vector2f sizes(const sf::FloatRect& a) {
    return sf::Vector2f(a.width, a.height);
}

sf::Color operator *(float x, sf::Color col) {
    return sf::Color{(unsigned char)(col.r * x), (unsigned char)(col.g * x), (unsigned char)(col.b * x), (unsigned char)(col.a * x)};
}

sf::Vector2f operator *(float x, sf::Vector2f pos) {
    return sf::Vector2f{x * pos.x, x * pos.y};
}


bool animating = 0;
bool stepbystep = 0;

bool buttonevent[128];

bool keyboardvis[256];

int structuremode = 1;

float animationtime = 1.0f;

extern sf::RenderWindow window;
extern sf::Event event;
extern sf::Font font;

void reglobe() {
    for (int i = 2; i <= 7; i++) if (buttonevent[i]) {
        structuremode = i;
        break;
    }
    if (buttonevent[8]) {
        stepbystep ^= 1;
    }
    if (buttonevent[9]) {
        animationtime += (animationtime < 1? 0.25f: 0.5f);
        if (animationtime == 2.5f) animationtime = 0.25f;
    }
    memset(buttonevent, 0, sizeof(buttonevent));
    memset(keyboardvis, 0, sizeof(keyboardvis));
}