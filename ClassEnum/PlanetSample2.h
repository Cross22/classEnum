#pragma once

// Java enums are really nice at providing type safety while also
// offering enumeration over all values. Furthermore as first-class objects
// you can augment them with arbitrary functionality. These features are
// sorely lacking from C++ enum "classes".
// https://docs.oracle.com/javase/tutorial/java/javaOO/enum.html

#include "PlanetSample1.h"

using namespace std;

// Here is another way to get similar behavior in C++. Downsides to this approach:
// - no way to get a complete list of all enums (might be possible in C++14!)
// - object construction is inlined at all points of use, so it is slightly slower
//   than approach #1

//------------------------------------------------------------------------------
// A "class enum" with some custom attributes

struct TOtherPlanet : public TBaseEnum {
    template<size_t N>
    constexpr explicit TOtherPlanet(const char(&name)[N],
                                    float mass, float radius) :
    TBaseEnum(name),
    m_mass(mass),
    m_radius(radius) {}
    
    const float     m_mass;
    const float     m_radius;
};

//------------------------------------------------------------------------------
// Version #2
// These are constant literals that get instantiated by the compiler as needed:

namespace OtherPlanets {
    constexpr static TOtherPlanet
        MERCURY {"MERCURY",3.303e+23, 2.4397e6},
        VENUS   {"VENUS",4.869e+24, 6.0518e6},
        EARTH   {"EARTH",5.976e+24, 6.37814e6},
        MARS    {"MARS",6.421e+23, 3.3972e6},
        JUPITER {"JUPITER",1.9e+27,   7.1492e7},
        SATURN  {"SATURN",5.688e+26, 6.0268e7},
        URANUS  {"URANUS",8.686e+25, 2.5559e7},
        NEPTUNE {"NEPTUNE",1.024e+26, 2.4746e7};
};