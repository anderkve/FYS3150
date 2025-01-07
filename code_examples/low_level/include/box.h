//
// Created by Nils Enric Canut Taugbøl on 07/01/2025.
//

#ifndef BOX_H
#define BOX_H

#include "precomp.h"

class Box
{
public:
    void Init();
    // static data, for global access
    static inline std::vector<Actor*> actorPool;
    static inline std::vector<Hole*> holes;
    static inline arma::vec2 boxSize = {1920, 1080};
};

#endif //BOX_H
