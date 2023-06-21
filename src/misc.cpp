#include "misc.h"

float mod2pi(const float &alpha)
{
  return fmodf(2.f * M_PI + fmodf(alpha, 2.f * M_PI), 2.f * M_PI);
}

float rangeSymm(const float &alpha) { return -M_PI + mod2pi(alpha - M_PI); }
