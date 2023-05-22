#include <iostream>
#include "../include/Graph.h"
#include "../include/constants.h"

int main() {
    Graph graph;
    graph.fill(TOY_GRAPH_TOURISM);
    for (auto v : graph.getVertexSet()) {
        std::cout << v->getId() << std::endl;
    }
}