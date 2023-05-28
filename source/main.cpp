#include <iostream>
#include "../include/Graph.h"
#include "../include/constants.h"

int main() {
    Graph graph;
    graph.fill(TOY_GRAPH_SHIPPING);
    graph.tspBF();
/*
    for (auto& v : graph.getVertexSet()) {
        std::cout << v->getId() << " : " << "\n\t";
        for (auto&e : v->getAdj()) {
            std::cout << e->getDest()->getId() <<  " ";
        }
        std::cout << std::endl;
    } */
}