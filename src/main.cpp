#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <Globals.hpp>
#include <Button.hpp>

sf::RenderWindow window(sf::VideoMode(720, 480), "dsavisual", sf::Style::Titlebar | sf::Style::Close);
sf::Event event;

button Button;

int main() {
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
        }
        Button.checkMouse();

        Button.tick();

        window.clear();
        Button.display();
        window.display();
    }

    return 0;
}