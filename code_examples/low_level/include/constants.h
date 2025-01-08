//
// Created by Nils Enric Canut Taugbøl on 07/01/2025.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

inline constexpr double PIXELSPAU = 1000.;    // pixels = 1 AU
inline constexpr double G = 39.4784176044 * PIXELSPAU * PIXELSPAU * PIXELSPAU;
inline constexpr double dt = 1e-10; // of a year
inline constexpr int SCRNWIDTH = 500;
inline constexpr int SCRNHEIGHT = 500;
inline constexpr int N_PARTICLES = 2500;
inline constexpr int PARTICLE_WAVE = 100;
inline constexpr int N_HOLES = 5;

inline constexpr float MIN_START_VEL = 10 * PIXELSPAU; // pixels per frame
inline constexpr float MAX_START_VEL = 1000. * PIXELSPAU;
inline constexpr float MIN_RADIUS = 0.00465046726 * PIXELSPAU; // radius of the sun
inline constexpr float MAX_RADIUS = 20.0 * MIN_RADIUS;
inline constexpr double MIN_MASS = 1.0;
inline constexpr double MAX_MASS = 1e10;


#endif //CONSTANTS_H
