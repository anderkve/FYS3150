#ifndef __CelestialBody_hpp__
#define __CelestialBody_hpp__

#include <armadillo>
#include <string>
#include <assert.h>

class CelestialBody
{
  public:
    std::string name;
    double m;
    arma::vec r;
    arma::vec v;
    arma::vec a;
    arma::vec F;
    bool fixed;
    double kin_energy;
    double pot_energy;

    // Constructor with vectors
    CelestialBody(std::string name_in, double m_in, arma::vec r_in, arma::vec v_in, bool fixed_in=false);

    // Initializer
    void init(std::string name_in, double m_in, arma::vec r_in, arma::vec v_in, bool fixed_in=false);
};


#endif  // __CelestialBody_hpp__