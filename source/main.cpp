#include <iostream>
#include "../include/Graph.h"
#include "../include/constants.h"

int main() {
    Graph graph;
    graph.fill(TOY_GRAPH_TOURISM);
    graph.prim();

    for (auto& v : graph.getVertexSet()) {
        if (v->getPath()) {
            std::cout << v->getPath()->getOrigin()->getId() << " -> " << v->getId() << std::endl;
        }
    }

    std::vector<Vertex*> preOrder;

    for (auto& v : graph.getVertexSet()) {
        v->setVisited(false);
    }

    graph.dfs(graph.getVertexSet().front(), preOrder);

    for (auto& v : preOrder) {
        std::cout << v->getId() << " ";
    }
    std::cout << std::endl;
}