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
    virtual bool update() = 0;
    virtual uint getType() = 0;
    arma::vec2 pos, vel;        // vec2 since we are working in 2D
    double mass;
    std::unique_ptr<sf::CircleShape> shape;           // we will be drawing
};

class Particle : public Actor
{
public:
    Particle(const arma::vec2& pos, const arma::vec2& vel, double mass);
    bool update() override;
    uint getType() override { return Actor::Particle_n; }
private:
    arma::vec2 acceleration(const arma::vec2& positionOverride = arma::vec2());
    arma::vec2 new_position;
};

class Hole : public Actor
{
public:
    Hole(const arma::vec2& pos, double mass, float radius);
    Hole(const arma::vec2& pos, const arma::vec2& vel, double mass, float radius);
    bool update() override;
    uint getType() override { return Actor::Hole_n; }
    float radius;
};

#endif //ACTOR_H
