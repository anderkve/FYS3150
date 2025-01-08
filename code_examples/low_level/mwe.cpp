//
// Created by Nils Enric Canut Taugbøl on 08/01/2025.
//

#include "precomp.h"

int main() {
    Box box;
    box.Init();

    while (Box::window.isOpen()) {
        while (const std::optional event = Box::window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                Box::window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    Box::window.close();
            }
        }
        Box::window.clear();
        box.update();
        Box::window.display();
    }
}
