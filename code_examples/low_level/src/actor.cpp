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

bool Hole::update() {
    // nothing to update here yet, they stay put
    return true;
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

    // if the particle is outside of the box wrap it back in on the opposite side
    for (int i = 0; i < pos.n_elem; i++) {
        if (pos(i) < Box::lowerBounds(i)) {
            pos(i) = Box::upperBounds(i) - fmod(Box::lowerBounds(i) - pos(i), Box::upperBounds(i) - Box::lowerBounds(i));
        }
        else if (pos(i) >= Box::upperBounds(i)) {
            pos(i) = Box::lowerBounds(i) + fmod(pos(i) - Box::lowerBounds(i), Box::upperBounds(i) - Box::lowerBounds(i));
        }
    }

    // if the particle is in a hole -> delete and generate new particle with new conditions
    for (const Hole* hole : Box::holes) {
        if (norm(hole->pos - pos) < hole->radius) {
            return false;
        }
    }

    return true;
}

arma::vec2 Particle::acceleration(const arma::vec2& positionOverride) {
    arma::vec2 position = positionOverride.is_empty() ? pos : positionOverride;

    arma::vec2 acceleration = {0., 0.};

    // find the force from the holes onto the particle
    for (const Hole* hole : Box::holes) {
        arma::vec2 direction = hole->pos - position;
        double dist = norm(direction);
        arma::vec2 total_force = G * hole->mass * mass / std::pow(dist, 2) * normalise(direction);
        acceleration += total_force / (float) mass;
    }

    return acceleration;
}



