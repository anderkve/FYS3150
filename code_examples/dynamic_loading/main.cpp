#include <dlfcn.h>    // Need this for dynamic loading
#include <stdexcept>  // Need this for std::runtime_error
#include <iomanip>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;


// Typedefs and forward declarations

typedef double (*integrand_fptr_type)(double);

double recursive_integrate(double x_min, double x_max, double eps, integrand_fptr_type integrand);



// 
// Main program
//
int main(int argc, const char* argv[])
{
  // Check number of command line arguments
  if (argc != 5)
  {
    cout << "Wrong number of input arguments." << endl;
    cout << "Usage: ./main <library path> <xmin> <xmax> <eps>" << endl;
    return 1;
  }

  // Store input arguments
  const string library_path = argv[1];
  const double xmin = atof(argv[2]);
  const double xmax = atof(argv[3]);
  const double eps = atof(argv[4]);

  // Expected library symbol name
  const string library_symbol = "integrand";


  // 
  // Try to dynamically load the library using dlopen
  // 

  cout << endl;
  cout << "Trying to load library at " << library_path << endl;
  void* phandle = dlopen(library_path.c_str(), RTLD_LAZY);
  
  // Did it work?
  if (phandle)
  {
    cout << endl;
    cout << "All good. phandle = " << phandle << " should now be pointing to " << library_path << endl;
  }
  else
  {
    string error_msg = dlerror();
    cout << endl;
    cout << "No good. dlerror() says: " << error_msg << endl; 
    return 1;
  }


  // 
  // Now try to connect a function pointer to the expected library symbol "integrand"
  // 

  // First get the pointer as a void pointer:
  void *temp = dlsym(phandle, library_symbol.c_str());

  // Then recast it to function pointer of the type we know it should be:
  integrand_fptr_type integrand = reinterpret_cast<integrand_fptr_type>(temp);


  // Did it work?
  if (integrand)
  {
    cout << endl;
    cout << "All good. Our pointer should now point to the library symbol " 
         << "'" << library_symbol << "'" << endl;
  }
  else
  {
    cout << endl;
    cout << "No good. Got a NULL pointer." << endl; 
    return 1;
  }


  // 
  // Now let's integrate this function
  // 

  cout << endl;
  cout << "Performing recursive integration..." << endl;

  double result = recursive_integrate(xmin, xmax, eps, integrand);

  cout << endl;
  cout << "Result: " << std::setprecision(14) << std::scientific << result << endl;

  // All good
  return 0;
}




// 
// Recursive 1D integrator
// 
double recursive_integrate(double x_min, double x_max, double eps, integrand_fptr_type integrand)
{
  // Only compute these the first time 
  static const double w1 = 1. / 3.;
  static const double w2 = 4. / 3.;

  // Compute T1
  double h = x_max - x_min;
  double T_1 = 0.5 * h * (integrand(x_min) + integrand(x_max));

  // Compute T2
  h = 0.5 * h;
  double x_mid = x_min + h;
  double T_2 = 0.5 * T_1 + h * integrand(x_mid);

  // Relative difference
  double rel_diff = fabs((T_2 - T_1) / (T_1 + 0.001 * eps));

  // Should I stay or should I go?
  if (rel_diff < eps)
  {
    // cout << "Done with this part." << endl;
    return w2 * T_2 - w1 * T_1; // Simpson's rule
  }
  else
  {
    // cout << "Split this part." << endl;
    return recursive_integrate(x_min, x_mid, eps, integrand) + recursive_integrate(x_mid, x_max, eps, integrand);
  }

  throw runtime_error("Problem in function recursive_integrate...");
}


