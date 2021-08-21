#include "CelestialBody.hpp"

using namespace std;
using namespace arma;


// Constructor with vectors
CelestialBody::CelestialBody(string name_in, double m_in, vec r_in, vec v_in, bool fixed_in)
{
  init(name_in, m_in, r_in, v_in, fixed_in);
}


// Initializer
void CelestialBody::init(string name_in, double m_in, vec r_in, vec v_in, bool fixed_in)
{
  name = name_in;
  m = m_in;

  fixed = fixed_in;
  r = r_in;
  v = v_in;

  int ndim = r.n_elem;
  assert(v.n_elem == ndim);

  a = vec(ndim, fill::zeros);
  F = vec(ndim, fill::zeros);

  kin_energy = 0.0;
  pot_energy = 0.0;
}
