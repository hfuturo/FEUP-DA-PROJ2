#include <iostream>
#include "../include/Graph.h"
#include "../include/constants.h"

int main() {
    Graph graph;
    graph.fill(TOY_GRAPH_STADIUMS);
    graph.prim();

    for (auto& v : graph.getVertexSet()) {
        if (v->getPath()) {
            std::cout << v->getPath()->getOrigin()->getId();
        }
        std::cout << " -> " << v->getId() << std::endl;
    }
}