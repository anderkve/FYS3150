//
// Created by Nils Enric Canut Taugbøl on 07/01/2025.
//

#ifndef BOX_H
#define BOX_H

#pragma once
#include "../precomp.h"
#include "actor.h"

class Box
{
public:
    void Init();
    void update(double dt);
    void render();
    arma::vec2 startSide(int start);
    std::shared_ptr<Hole> generateHole();
    std::shared_ptr<Particle> generateParticle();

    // static data, for global access
    static inline std::vector<std::shared_ptr<Actor>> actorPool;
    static inline std::vector<std::shared_ptr<Hole>> holes;
    static inline arma::vec2 upperBounds = {SCRNWIDTH, SCRNHEIGHT};
    static inline arma::vec2 lowerBounds = {0., 0.};
    static inline sf::RenderWindow window;
    int particlesOnScreen = 0;
    float frameTimeAvg = 10.0f; // estimate of average time spent per frame in ms
};

#endif //BOX_H
