//
// Created by Nils Enric Canut Taugbøl on 24/10/2025.
//

#ifndef BOXED_PARTICLES_PARTICLE_H
#define BOXED_PARTICLES_PARTICLE_H

#pragma once
#include "precomp.h"

struct Particles {
    std::vector<arma::vec2> pos;
    std::vector<arma::vec2> vel;
    std::vector<double> mass;
    std::vector<float> radius;
    std::vector<arma::vec2> accelerationPre;
    std::vector<arma::vec2> accelerationPost;
    std::vector<std::unique_ptr<sf::CircleShape>> shapes;


    // calling size() on a Particles struct should give the number of particles in the struct.
    [[nodiscard]] size_t size() const{return pos.size();}

    // this is a comment saying you don't need to comment for functions as below
    void add(const arma::vec2& pos_in, const arma::vec2& vel_in, double mass_in, float radius_in);
private:
    arma::vec2 startSide(int start);
};

#endif //BOXED_PARTICLES_PARTICLE_H