//
// Created by Nils Enric Canut Taugbøl on 24/10/2025.
//

#pragma once

#if defined(USE_AOS)
  #include "aos/box.h"
#elif defined(USE_SOA)
  #include "soa/box.h"
#else
  #error "Define either USE_AOS or USE_SOA"
#endif