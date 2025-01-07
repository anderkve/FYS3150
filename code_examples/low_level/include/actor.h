//
// Created by Nils Enric Canut Taugbøl on 07/01/2025.
//

#ifndef ACTOR_H
#define ACTOR_H

class Actor
{
public:
    enum {Hole_n = 0, Particle_n};
    Actor() = default;          // makes sure initialisation is consistent since the classes will have different constructors
    ~Actor() = default;
    virtual bool update() = 0;
    virtual uint getType() = 0;
    arma::vec2 pos, vel;        // vec2 since we are working in 2D
    int mass;
    float dt = 1e-4;
    bool to_be_deleted = false;
};

class Particle : public Actor
{
    Particle(const arma::vec2& pos, const arma::vec2& vel, int mass);
    bool update() override;
    uint getType() override { return Actor::Particle_n; }
    arma::vec2 acceleration(const arma::vec2& positionOverride = arma::vec2());
};

class Hole : public Actor
{
    Hole(const arma::vec2& pos, int mass, float radius);
    Hole(const arma::vec2& pos, const arma::vec2& vel, int mass, float radius);
    uint getType() override { return Actor::Hole_n; }
public:
    float radius;
};

#endif //ACTOR_H
