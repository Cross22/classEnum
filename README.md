Java enums are really nice at providing type safety while also
offering enumeration over all values. Furthermore as first-class objects
you can augment them with arbitrary functionality. These features are
sorely lacking from C++ enum "classes".
https://docs.oracle.com/javase/tutorial/java/javaOO/enum.html

PlanetSample1 shows one way to get similar behavior in C++. Downsides to 
this approach:
 - cannot use fake enums in switch statements or where constexpr is needed
 - definition file required (Planets.cpp) instead of being header-only
 - all objects are instantiated whether used or not and live forever
 - static initialization order is undefined

PlanetSample2 is another way to get similar behavior in C++. Downsides to 
that approach:
 - no way to get a complete list of all enums (might be possible in C++14!)
 - object construction is inlined at all points of use, so it is slightly slower
   than approach #1

main.cpp demonstrates some typical usages
