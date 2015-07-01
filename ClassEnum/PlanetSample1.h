#pragma once

// Java enums are really nice at providing type safety while also
// offering enumeration over all values. Furthermore as first-class objects
// you can augment them with arbitrary functionality. These features are
// sorely lacking from C++ enum "classes".
// https://docs.oracle.com/javase/tutorial/java/javaOO/enum.html

// Here is one way to get similar behavior in C++. Downsides to this approach:
// - cannot use fake enums in switch statements or where constexpr is needed
// - definition file required (Planets.cpp) instead of being header-only
// - all objects are instantiated whether used or not and live forever
// - static initialization order is undefined

// Check out PlanetSample2.h for a different approach

#include <vector>
#include <string>

using namespace std;

//------------------------------------------------------------------------------
// Ugly stuff here; scroll down and look at the pretty struct instead.

class TBaseEnum {
public:
    operator string() const { return m_name; }
    constexpr operator uint32_t() const { return m_hash; }
    constexpr bool operator==(const TBaseEnum& rhs) const { return m_hash==rhs.m_hash; }
    
    protected :
    // Only allow char literals here
    template<size_t N>
    constexpr explicit TBaseEnum(const char(&name)[N]) :
    m_name(name), m_hash(recursive_hash(name)) {}
    
    const char* const   m_name;
    const uint32_t      m_hash;
    
    // Hash is a workaround to get a unique ID. Unfortunately constexpr
    // does not allow reinterpret_cast or we could just use (int)m_name.
    constexpr uint32_t recursive_hash(char const *input) const {
        return *input ?
        static_cast<unsigned int>(*input) + 33 * recursive_hash(input + 1) :
        5381;
    }
};

//------------------------------------------------------------------------------
// A "class enum" with some custom attributes
// In C++ 11 this constructor has to be non-const :-(
struct TPlanet : public TBaseEnum {
    template<size_t N>
    explicit TPlanet(const char(&name)[N],
                                    float mass, float radius) :
    TBaseEnum(name),m_mass(mass), m_radius(radius) {
        s_allInstances.push_back(this);
    }
    
    const float     m_mass;
    const float     m_radius;
    
    static vector<const TPlanet*> s_allInstances;
};


//------------------------------------------------------------------------------
// Version #1
extern struct TPlanets {
    const TPlanet
    MERCURY {"MERCURY",3.303e+23, 2.4397e6},    // Duplication sucks. No way around
    VENUS   {"VENUS",4.869e+24, 6.0518e6},      // it without macros.
    EARTH   {"EARTH",5.976e+24, 6.37814e6},     // Macros suck even more.
    MARS    {"MARS",6.421e+23, 3.3972e6},
    JUPITER {"JUPITER",1.9e+27,   7.1492e7},
    SATURN  {"SATURN",5.688e+26, 6.0268e7},
    URANUS  {"URANUS",8.686e+25, 2.5559e7},
    NEPTUNE {"NEPTUNE",1.024e+26, 2.4746e7};
    
    // All known planet instances
    static const vector<const TPlanet*>& values()
    { return TPlanet::s_allInstances; }
} Planets;

