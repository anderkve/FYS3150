//
// Created by Nils Enric Canut Taugbøl on 24/10/2025.
//

#ifndef BOXED_PARTICLES_BOX_H
#define BOXED_PARTICLES_BOX_H

#pragma once
#include "precomp.h"
#include "particle.h"
#include "hole.h"

class Box
{
public:
    void Init();
    void update(double dt);
    void render();

    static arma::vec2 startSide(int start);

    void generateParticle();
    void generateHole();

    void updateParticles(double dt);
    void deleteParticle(int index);

    Particles particles;
    Holes holes;

    // static data, for global access
    static inline arma::vec2 upperBounds = {SCRNWIDTH, SCRNHEIGHT};
    static inline arma::vec2 lowerBounds = {0., 0.};
    static inline sf::RenderWindow window;
    float frameTimeAvg = 10.0f; // estimate of average time spent per frame in ms
};

#endif //BOXED_PARTICLES_BOX_H