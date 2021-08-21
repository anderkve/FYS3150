#include "SolarSystem.hpp"
#include <iomanip>


using namespace std;
using namespace arma;


// Constructor
SolarSystem::SolarSystem(int ndim_in, double beta_in, bool use_GR_correction_in)
{
  _ndim = ndim_in;
  _beta = beta_in;
  _use_GR_correction = use_GR_correction_in;

  _bodies.clear();
  _kin_energy = 0.0;
  _pot_energy = 0.0;
}


// Add a celestial body and return a reference
CelestialBody& SolarSystem::add_celestial_body(string name_in, double m_in, vec r_in, vec v_in, bool fixed_in)
{
  // Check that the number of dimensions is correct
  assert(r_in.n_elem == _ndim);
  assert(v_in.n_elem == _ndim);

  // Create a new CelestialBody and add it in the 'bodies' vector
  CelestialBody new_body = CelestialBody(name_in, m_in, r_in, v_in, fixed_in);
  _bodies.push_back( CelestialBody(name_in, m_in, r_in, v_in, fixed_in) );

  // Also add the name and vector index to the _body_indices map;
  int bi = _bodies.size() - 1;
  _body_indices[new_body.name] = bi;

  // Since we added a new body, we should update all energies
  update_energies();

  // Return a reference to the CelestialBody we just added
  return _bodies.back();
}


// Get number of bodies
int SolarSystem::number_of_bodies()
{
  return _bodies.size();
}


// Get reference to a body by index
const CelestialBody& SolarSystem::get_body(int i)
{
  return _bodies[i];
}


// Get reference to a body by name
const CelestialBody& SolarSystem::get_body(string name)
{
  int bi = _body_indices.at(name);
  return _bodies[bi];
}


// Get vector of body names
vector<string> SolarSystem::get_body_names()
{
  vector<string> body_names;

  for (const CelestialBody& body : _bodies)
  {
    body_names.push_back(body.name);
  }

  return body_names;
}


// The force on body_i from body_j
vec SolarSystem::force(double m_i, double m_j, vec r_i, vec r_j, vec v_i)
{
  vec r_ij = r_i - r_j;   // r_ij is a vector pointing from body_j to body_i
  double r_ij_norm = norm(r_ij, 2);
  double v_i_norm = norm(v_i, 2);

  // Newtonian gravity
  vec F = -_G * m_i * m_j / pow(r_ij_norm, _beta + 1) * r_ij; // negative sign for attractive force

  // Add GR correction?
  if (_use_GR_correction)
  {
    static const double cc = pow(63239.7263,2);  // cc = (speed of light [AU/yr])^2
    double l = norm(cross(r_i, v_i), 2);  // l = |r_i x v_i|
    double GR_corr_factor = (1. + (3. * l * l) / (pow(r_ij_norm, _beta) * cc));  // [1 + (3 l^2)/(r^2 c^2)]
    // cout << "DEBUG: "<< endl;
    // cout << "DEBUG: r_ij_norm = " << std::setprecision(10) << std::scientific << r_ij_norm << endl;
    // cout << "DEBUG: r_ij_norm^2 = " << std::setprecision(10) << std::scientific << pow(r_ij_norm, _beta) << endl;
    // cout << "DEBUG: v_i_norm = " << std::setprecision(10) << std::scientific << v_i_norm << endl;
    // cout << "DEBUG: r_ij_norm * v_i_norm = " << std::setprecision(10) << std::scientific << r_ij_norm * v_i_norm << endl;
    // cout << "DEBUG: l = " << std::setprecision(10) << std::scientific << l << endl;
    // cout << "DEBUG: l*l = " << std::setprecision(10) << std::scientific << l*l << endl;
    // cout << "DEBUG: cc = " << std::setprecision(10) << std::scientific << cc << endl;
    // cout << "DEBUG: GR_corr_factor = " << std::setprecision(10) << std::scientific << GR_corr_factor << endl;
    F *= GR_corr_factor;
  }

  return F;
}

// -- Same as above but with CelestialBody instances as input
vec SolarSystem::force(const CelestialBody& body_i, const CelestialBody& body_j)
{
  return force(body_i.m, body_j.m, body_i.r, body_j.r, body_i.v);
}

// -- Same as above but with body indices as input
vec SolarSystem::force(int i, int j)
{
  return force(_bodies[i], _bodies[j]);
}


// The total force on body_i from all other bodies
vec SolarSystem::total_force(int i)
{
  vec F_tot(_ndim, fill::zeros);

  for (int j=0; j < _bodies.size(); j++)
  {
    // If body_i and body_j are the same body, skip to the next one
    if (i==j) continue;

    // When j is not i, add the force to F_tot
    F_tot += force(i, j);
  }

  return F_tot;
}


// The potential energy for body_i due to body_j
double SolarSystem::potential_energy_body(int i, int j)
{
  const CelestialBody& body_i = _bodies[i];
  const CelestialBody& body_j = _bodies[j];

  vec r_ij = body_i.r - body_j.r;   // r_ij is a vector pointing from body_j to body_i
  double r_ij_norm = norm(r_ij, 2);
  double pot_energy_ij = -(1. / (_beta - 1.)) * _G * body_i.m * body_j.m / pow(r_ij_norm, _beta - 1.);
  return pot_energy_ij;
}

double SolarSystem::potential_energy_system()
{
  return _pot_energy;
}

double SolarSystem::kinetic_energy_system()
{
  return _kin_energy;
}

double SolarSystem::total_energy_system()
{
  return _kin_energy + _pot_energy;
}


// Update the energies for all bodies
void SolarSystem::update_energies()
{
  // Reset toten energies for the system
  _kin_energy = 0.0;
  _pot_energy = 0.0;

  for (int i=0; i < _bodies.size(); i++)
  {
    // Get body_i
    CelestialBody& body_i = _bodies[i];

    // Reset energies
    body_i.kin_energy = 0.0;
    body_i.pot_energy = 0.0;

    // Calculate potential energy of body_i adding contributions due to all other bodies
    for (int j=0; j < _bodies.size(); j++)
    {
      // If body_i and body_j are the same body, skip to the next one
      if (i==j) continue;

      // When j is not i, add the potential energy
      double pot_energy_ij = potential_energy_body(i, j);
      body_i.pot_energy += pot_energy_ij;

      // If j > i, add the potential energy to the total potential energy of the *system*
      // (The requirement j>i avoids double-counting.)
      if(j > i)
      {
        _pot_energy += pot_energy_ij;
      }

    }

    // Calculate kinetic energy for body_i
    double vi_norm = norm(body_i.v, 2);
    body_i.kin_energy = 0.5 * body_i.m * pow(vi_norm, 2);

    // Add this kinetic energy to the total kinetic energy of the *system*
    _kin_energy += body_i.kin_energy;
  }
}


// Set all positions and velocities relative to the baryocentric coordinate system (center of mass)
void SolarSystem::set_barycentric_coordinates()
{
  // Calculate the total mass of the system (M),
  // and the position (r_bc) and velocity (v_bc) of the center of mass.
  vec r_bc = vec(_ndim, fill::zeros);
  vec v_bc = vec(_ndim, fill::zeros);
  double M = 0.0;
  for(const CelestialBody& b : _bodies)
  {
    r_bc += b.r * b.m;
    v_bc += b.v * b.m;
    M += b.m;
  }
  r_bc /= M;
  v_bc /= M;

  // Change to a coordinate system where the center of mass is at rest
  // at the origin. This system is shifted and has a constant velocity
  // relative to our original coordinate system. Hence, to change 
  // coordinate system we need to adjust the positions and velocities 
  // of all bodies in the system:
  for(CelestialBody& b : _bodies)
  {
    b.r -= r_bc;
    b.v -= v_bc;
  }
}



// 
// Functions for evolving the system one timestep
// 

// Velocity Verlet
void SolarSystem::evolve_velocity_verlet(double dt)
{
  const double dtdt = dt*dt;

  // Loop over all bodies
  for (int i=0; i < _bodies.size(); i++)
  {
    // Current body:
    CelestialBody& body_i = _bodies[i];

    // If body is fixed, skip to next one
    if (body_i.fixed) continue;

    // Save current acceleration
    vec a_old = body_i.a;

    // VV step 1: update position, using current velocity and acceleration
    body_i.r = body_i.r + dt * body_i.v + 0.5 * dtdt * body_i.a;

    // VV step 2: update the acceleration (and force), using the new position
    body_i.F = total_force(i);
    body_i.a = body_i.F / body_i.m;

    // VV step 3: update the velocity, using both the new and the old acceleration
    body_i.v = body_i.v + 0.5 * dt * (body_i.a + a_old);

    // Update energies
    update_energies();
  }
}


// Forward Euler
void SolarSystem::evolve_forward_euler(double dt)
{
  // Loop over all bodies
  for (int i=0; i < _bodies.size(); i++)
  {
    // Current body:
    CelestialBody& body_i = _bodies[i];

    // If body is fixed, skip to next one
    if (body_i.fixed) continue;

    // Get current acceleration for current body i
    body_i.F = total_force(i);
    body_i.a = body_i.F / body_i.m;

    // FE step 1: update position, , using current velocity
    body_i.r = body_i.r + dt * body_i.v;

    // FE step 2: update velocity, using current acceleration
    body_i.v = body_i.v + dt * body_i.a;

    // Update energies
    update_energies();
  }
}
