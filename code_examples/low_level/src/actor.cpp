//
// Created by Nils Enric Canut Taugbøl on 07/01/2025.
//

#include "precomp.h"
#include "box.h"

// Hole //

Hole::Hole(const arma::vec2& pos, const int mass, const float radius) {
    this->pos = pos;
    this->mass = mass;
    this->radius = radius;
    vel = {0., 0.};
}

Hole::Hole(const arma::vec2& pos, const arma::vec2& vel, const int mass, const float radius) {
    this->pos = pos;
    this->mass = mass;
    this->radius = radius;
    this->vel = vel;
}

// Particle //

Particle::Particle(const arma::vec2& pos, const arma::vec2& vel, int mass) {
    this->pos = pos;
    this->vel = vel;
    this->mass = mass;
}

bool Particle::update() {
    // update position using Heun's method
    arma::vec2 temp_pos = pos + dt/2. * ( vel + vel + dt*acceleration() );
    vel = vel + dt/2. * (acceleration() + acceleration(pos + dt * vel));
    pos = temp_pos;

    // check if it is either outside the box or in a hole
    // if outside the box make reappear on other end
    // if in a hole -> regenerate at the start with new conditions
}

arma::vec2 Particle::acceleration(const arma::vec2& positionOverride) {
    arma::vec2 position = positionOverride.is_empty() ? pos : positionOverride;

    arma::vec2 acceleration = {0., 0.};

    // find the force from the holes onto the particle
    for (const Hole* actor : Box::holes) {
        arma::vec2 direction = actor->pos - position;
        double dist = norm(direction);
        arma::vec2 total_force = G * actor->mass * mass / std::pow(dist, 2) * normalise(direction);
        acceleration += total_force / (float) mass;
    }

    return acceleration;
}



