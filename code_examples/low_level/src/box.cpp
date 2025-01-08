//
// Created by Nils Enric Canut Taugbøl on 07/01/2025.
//

#include "precomp.h"

// for the generation of particles and holes
std::random_device rd;
std::mt19937 gen(rd());

std::uniform_real_distribution massDistribution(MIN_MASS, MAX_MASS);
std::uniform_real_distribution posXDistribution(0.f, (float) SCRNWIDTH);
std::uniform_real_distribution posYDistribution(0.f, (float) SCRNHEIGHT);
std::uniform_real_distribution radiusDistribution(MIN_RADIUS, MAX_RADIUS);
std::uniform_real_distribution velocityDistribution(-MAX_START_VEL, MAX_START_VEL);

void Box::Init() {
    // working with smart pointers
    // generate the holes
    for (int i = 0; i < N_HOLES; i++) {
        auto hole = std::make_shared<Hole>(arma::vec2{posXDistribution(gen), posYDistribution(gen)},
                                             massDistribution(gen),
                                             radiusDistribution(gen));

        holes.push_back(std::vector< std::shared_ptr<Hole> >::value_type(hole));
        actorPool.push_back(std::vector< std::shared_ptr<Actor> >::value_type(hole));
    }

    // generate the particles
    for (int i = 0; i < PARTICLE_WAVE; i++) {
        auto particle = std::make_shared<Particle>(arma::vec2{0.5, 0.5},
                                                    arma::vec2{velocityDistribution(gen), velocityDistribution(gen)},
                                                     1);

        actorPool.push_back(std::vector< std::shared_ptr<Actor> >::value_type(particle));
        particlesOnScreen++;
    }

    // set up the view of the screen
    window = sf::RenderWindow(sf::VideoMode({SCRNWIDTH, SCRNHEIGHT}), "Particle Simulation");
    // draw the starting screen
    for (const auto & i : actorPool) {
        window.draw(*i->shape);
    }

    window.display();
}

void Box::update() {
    Timer t;

    // update all actors
    for (int i = 0; i < (int) actorPool.size(); i++) {
        if (!actorPool[i]->update()) {
            // actor got deleted; replace by last actor in list
            // shared_ptr automatically manages the deletion
            std::shared_ptr<Actor> lastActor = actorPool.back();

            // Remove the last actor from the list
            actorPool.pop_back();

            // Replace the deleted particle with the last actor if they are not the same
            if (lastActor != actorPool[i]) {
                actorPool[i] = lastActor;
            }

            particlesOnScreen--;
            i--;    // need to update the one that was just moved to the ith position
        }
    }

    // introduce remaining new particles based on PARTICLE_WAVE but cannot have more than N_PARTICLES on the screen
    for (int i = 0; i < std::min(PARTICLE_WAVE, N_PARTICLES - particlesOnScreen); i++) {
        arma::vec2 start_pos = arma::vec2{0.5, 0.5};
        arma::vec2 start_vel = {velocityDistribution(gen), velocityDistribution(gen)};

        auto particle = std::make_shared<Particle>(start_pos, start_vel, 1);

        actorPool.push_back(std::vector< std::shared_ptr<Actor> >::value_type(particle));
        particlesOnScreen++;
    }

    // draw all
    for (const auto & i : actorPool) {
        window.draw(*i->shape);
    }

    // evt. handle input -> need to implement member function


    // report frame time
    frameTimeAvg = 0.95f * frameTimeAvg + 0.05f * t.elapsed() * 1000;
    printf( "frame time: %5.2fms\n", frameTimeAvg );

}
