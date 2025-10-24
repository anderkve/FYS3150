//
// Created by Nils Enric Canut Taugbøl on 07/01/2025.
//

#include "../../include/aos/box.h"

// for the generation of particles and holes
std::random_device rd;
std::mt19937 gen(rd());

std::uniform_real_distribution massDistribution(MIN_MASS, MAX_MASS);
std::uniform_int_distribution particleStartSide(0, 3);
std::uniform_real_distribution startParticleXDistribution(0.f, (float) SCRNWIDTH);
std::uniform_real_distribution startParticleYDistribution(0.f, (float) SCRNHEIGHT);
std::uniform_real_distribution posXDistribution(0.1f * (float) SCRNWIDTH, 0.9f * (float) SCRNWIDTH);
std::uniform_real_distribution posYDistribution(0.1f * (float) SCRNHEIGHT, 0.9f * (float) SCRNHEIGHT);
std::uniform_real_distribution radiusDistribution(MIN_RADIUS, MAX_RADIUS);
std::uniform_real_distribution velocityDistribution(MIN_START_VEL, MAX_START_VEL);

void Box::Init() {
    // working with smart pointers
    // generate the holes
    for (int i = 0; i < N_HOLES; i++) {
        std::shared_ptr<Hole> hole = generateHole();

        holes.push_back(std::vector< std::shared_ptr<Hole> >::value_type(hole));
        actorPool.push_back(std::vector< std::shared_ptr<Actor> >::value_type(hole));
    }

    // generate the particles
    for (int i = 0; i < PARTICLE_WAVE; i++) {
        std::shared_ptr<Particle> particle = generateParticle();

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

void Box::update(double dt) {
    Timer t;

    // update all actors
    for (int i = 0; i < (int) actorPool.size(); i++) {
        if (!actorPool[i]->update(dt)) {
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
        std::shared_ptr<Particle> particle = generateParticle();

        actorPool.push_back(std::vector< std::shared_ptr<Actor> >::value_type(particle));
        particlesOnScreen++;
    }

    // report frame time
    frameTimeAvg = 0.95f * frameTimeAvg + 0.05f * t.elapsed() * 1000;
    printf( "update time: %5.2fms\n", frameTimeAvg );

}

void Box::render() {
    window.clear();

    // draw all
    for (const auto & i : actorPool) {
        window.draw(*i->shape);
    }

    // evt. handle input -> need to implement member function

    window.display();
}

arma::vec2 Box::startSide(int start) {
    if (start == 0) {
        // start left side
        return arma::vec2 {0.0, startParticleYDistribution(gen)};
    }
    if (start == 1) {
        // start top
        return arma::vec2 {startParticleXDistribution(gen), 0.0};
    }
    if (start == 2) {
        // start right side
        return arma::vec2 {(double) SCRNWIDTH-1., startParticleYDistribution(gen)};
    }
    if (start == 3) {
        // bottom start
        return arma::vec2 {startParticleXDistribution(gen), (double) SCRNHEIGHT - 1.};
    }

    return arma::vec2 {0.0, 0.0};
}

std::shared_ptr<Hole> Box::generateHole() {
    arma::vec2 start_pos = arma::vec2{posXDistribution(gen), posYDistribution(gen)};
    float radius = radiusDistribution(gen);
    double mass = massDistribution(gen);

    bool okay = false;

    // cannot generate a hole above another one
    while (!okay && (int) actorPool.size() >  0) {
        for (const auto & i : actorPool) {
            if (norm(start_pos - i->pos) <= i->radius + radius) {
                okay = false;
                start_pos = arma::vec2{posXDistribution(gen), posYDistribution(gen)};
                radius = radiusDistribution(gen);
                break;
            }
            okay = true;
        }
    }

    return std::make_shared<Hole>(start_pos, mass, radius);
}

std::shared_ptr<Particle> Box::generateParticle() {
    arma::vec2 start_pos = startSide(particleStartSide(gen));
    arma::vec2 start_vel = {velocityDistribution(gen), velocityDistribution(gen)};

    auto particle = std::make_shared<Particle>(start_pos, start_vel, part_mass);


    bool okay = false;

    // cannot generate a hole above another one
    while (!okay && (int) actorPool.size() >  0) {
        for (const auto & i : actorPool) {
            if (norm(start_pos - i->pos) <= i->radius + part_radius) {
                okay = false;
                start_pos = startSide(particleStartSide(gen));
                break;
            }
            okay = true;
        }
    }

    return std::make_shared<Particle>(start_pos, start_vel, part_mass);
}