//
// Created by Nils Enric Canut Taugbøl on 08/01/2025.
//

#include "precomp.h"
#include "include/box.h"

int main() {
    Box box;
    box.Init();

    Timer t;
    double accTime = 0.0;

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
        accTime = 0.0;
        while (accTime <= 1000/60.) {
            box.update(dt);
            accTime += t.elapsed()*1000;    // time elapsed in ms
        }

        box.render();
    }
}
