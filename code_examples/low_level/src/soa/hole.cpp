//
// Created by Nils Enric Canut Taugbøl on 24/10/2025.
//

#include "soa/hole.h"

void Holes::add(const arma::vec2& pos_in, double mass_in, float radius_in) {
    pos.push_back(pos_in);
    mass.push_back(mass_in);
    radius.push_back(radius_in);
    auto s = std::make_unique<sf::CircleShape>(radius_in);
    s->setOrigin({radius_in, radius_in});
    s->setPosition(sf::Vector2f{(float) (pos_in(0)), (float) (pos_in(1))});
    s->setFillColor(sf::Color::Transparent);
    s->setOutlineColor(sf::Color::Cyan);
    s->setOutlineThickness(1.);
    shapes.push_back(std::move(s));
}