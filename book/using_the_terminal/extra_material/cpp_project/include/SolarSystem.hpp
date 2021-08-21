#ifndef __SolarSystem_hpp__
#define __SolarSystem_hpp__

#include <armadillo>
#include <string>
#include <map>
#include "CelestialBody.hpp"
#include <vector>
#include <assert.h>


class SolarSystem
{
  private:

    std::vector<CelestialBody> _bodies;
    std::map<std::string,int> _body_indices;
    double _kin_energy;
    double _pot_energy;
    int _ndim;
    double _beta;
    bool _use_GR_correction;
    static constexpr double _G = 39.47841760435743;  // = 4 pi^2, with units (AU)^3 / ((yr)^2 * M_sun)

  public:

    // Constructor
    SolarSystem(int ndim_in, double beta_in=2.0, bool use_GR_correction_in=false);


    // Add a celestial body and return a reference
    CelestialBody& add_celestial_body(std::string name_in, double m_in, arma::vec r_in, arma::vec v_in, bool fixed_in=false);

    // Get number of bodies
    int number_of_bodies();

    // Get reference to a body by index
    const CelestialBody& get_body(int i);

    // Get reference to a body by name
    const CelestialBody& get_body(std::string name);

    // Get vector of body names
    std::vector<std::string> get_body_names();



    // The force on body_i from body_j
    arma::vec force(double m_i, double m_j, arma::vec r_i, arma::vec r_j, arma::vec v_i);

    // -- Same as above but with CelestialBody instances as input
    arma::vec force(const CelestialBody& body_i, const CelestialBody& body_j);

    // -- Same as above but with body indices as input
    arma::vec force(int i, int j);

    // The total force on body_i from all other bodies
    arma::vec total_force(int i);


    // The potential energy for body_i due to body_j
    double potential_energy_body(int i, int j);

    double potential_energy_system();

    double kinetic_energy_system();

    double total_energy_system();

    // Update the energies for all bodies
    void update_energies();

    // Set all positions and velocities relative to the baryocentric coordinate system (center of mass)
    void set_barycentric_coordinates();


    // 
    // Functions for evolving the system one timestep
    // 

    // Velocity Verlet
    void evolve_velocity_verlet(double dt);

    // Forward Euler
    void evolve_forward_euler(double dt);
};


#endif  // __SolarSystem_hpp__