#include <iostream>
#include <chrono>

#include "../include/Graph.h"
#include "../include/constants.h"
#include "../include/UserInterface.h"

//               BF        APPROXIMATION
//  TOURISM:    2600           2600
//  STADIUMS:   341            398.1
//  SHIPPING:   86.7           80.6

// STADIUM 0 1 2 10 5 4 8 7 6 9 3
// SHIPPING 0 1 5 7 8 6 4 2 3 9 10 12 11 13
// TOURISM 0 3 2 1 4

int main() {
 /*   Graph graph {};
    auto tstart1 = std::chrono::high_resolution_clock::now();
    auto tend2 = std::chrono::high_resolution_clock::now();
    // graph.fill(TOY_GRAPH_STADIUMS);
    graph.approximation(); */
    UserInterface ui {};
    ui.showMenu();
    return 0;
}