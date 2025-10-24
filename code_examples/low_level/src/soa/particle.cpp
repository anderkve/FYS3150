//
// Created by Nils Enric Canut Taugbøl on 24/10/2025.
//

#include "soa/box.h"

void Particles::add(const arma::vec2& pos_in, const arma::vec2& vel_in, double mass_in, float radius_in) {
    pos.push_back(pos_in);
    vel.push_back(vel_in);
    mass.push_back(mass_in);
    radius.push_back(radius_in);
    accelerationPre.push_back({0., 0.});
    accelerationPost.push_back({0., 0.});

    auto s = std::make_unique<sf::CircleShape>(radius_in);
    s->setOrigin({radius_in, radius_in});
    s->setPosition(sf::Vector2f{(float) (pos_in(0)), (float) (pos_in(1))});
    s->setFillColor(sf::Color::Yellow);
    shapes.push_back(std::move(s));
}