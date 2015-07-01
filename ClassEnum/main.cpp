//
//  main.cpp
//  ClassEnum
//
//  Created by Marco Grubert on 6/30/15.

#include "PlanetSample1.h"
#include "PlanetSample2.h"
#include <iostream>
#include <iomanip>

// Please look in PlanetSample1.h for the interesting parts. This file
// just shows general usage.

void runSample1Tests() {
    // Easy access to name
    cout << (string) Planets.VENUS << endl;
    
    // Iterate over all "enums"
    for (auto pPlanet : Planets.values() ) {
        auto p = *pPlanet;
        
        // Access to associated attributes
        cout << setw(10) << left
        << (string) p << "has a mass of " << p.m_mass << " kg." << endl;
        
        // Equality works fine, but you cannot do switch statements :-(
        // Using "constexpr static" declarations instead you can do switch but then there
        // is no values() list.
        if (p==Planets.SATURN) {
            cout << "^---- That one has rings!"<<endl;
        }
       
    }
}

void runSample2Tests() {
    // Easy access to name
    cout << endl << (string) OtherPlanets::VENUS << endl;
    auto somePlanet = OtherPlanets::JUPITER;
    
    switch (somePlanet) {
        case OtherPlanets::MARS :
            break;
        default:
            cout << "somePlanet is not MARS" << endl;
    }
    
    if (somePlanet==OtherPlanets::JUPITER) {
        cout << "somePlanet is JUPITER, with a mass of " << somePlanet.m_mass << endl;
    }
}

int main(int argc, const char * argv[]) {
    runSample1Tests();
    runSample2Tests();
    return 0;
}
