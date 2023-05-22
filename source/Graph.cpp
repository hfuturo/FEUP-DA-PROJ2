#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "../include/Graph.h"
#include "../include/VertexEdge.h"

Graph::Graph() {}

std::vector<Vertex *> Graph::getVertexSet() const {
    return this->vertexSet;
}

bool Graph::addVertex(const int id) {
    vertexSet.push_back(new Vertex(id));
    return true;
}

Vertex *Graph::findVertex(const int id) const {
    for (auto &v: getVertexSet())
        if (v->getId() == id) return v;

    return nullptr;
}

bool Graph::addEdge(const int origin, const int dest, const double distance) {
    if (distance < 0 || origin < 0 || dest < 0) return false;
    auto v1 = findVertex(origin);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr) return false;
    auto e1 =  v1->addEdge(v2, distance);
    auto e2 = v2->addEdge(v1, distance);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void Graph::readVertices(const std::string& path) {
    std::ifstream file(path);

    if (file.fail()) return;

    std::string id, dest, distance, name, fileLine, destName;

    getline(file, fileLine);
    if (fileLine.size() == 52) {
        while (getline(file, fileLine)) {
            std::stringstream ss(fileLine);
            getline(ss, id, ',');
            getline(ss, dest, ',');
            getline(ss, distance, ',');
            getline(ss, name, ',');
            getline(ss, destName);

            if (findVertex(std::stoi(id)) != nullptr) continue;
            addVertex(std::stoi(id));
        }
    }
}

void Graph::fill(const std::string& path) {
    readVertices(path);
}
