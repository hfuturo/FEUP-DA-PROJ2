#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>

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

bool Graph::addBidirectionalEdge(const int origin, const int dest, const double distance) {
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

    int count = 0;
    std::string id, dest, name, destName, distance, fileLine, trash;

    getline(file, fileLine);
    std::stringstream ssTrash(fileLine);

    while (getline(ssTrash, trash, ',')) count ++;

    while (getline(file, fileLine)) {
        std::stringstream ss(fileLine);
        getline(ss, id, ',');
        getline(ss, dest, ',');
        getline(ss, distance, ',');
        if (count == 5) {
            getline(ss, name, ',');
            getline(ss, destName);
        }
        if (findVertex(std::stoi(id)) == nullptr) addVertex(std::stoi(id));
        if (findVertex(std::stoi(dest)) == nullptr) addVertex(std::stoi(dest));
    }
}

void Graph::readEdges(const std::string &path) {
    std::ifstream file(path);

    if (file.fail()) return;

    int count = 0;
    std::string fileLine, id, dest, distance, name, destName;

    getline(file, fileLine);
    std::stringstream ssTrash(fileLine);

    while (getline(ssTrash, fileLine, ',')) count++;

    while (getline(file, fileLine)) {
        std::stringstream ss(fileLine);
        getline(ss, id, ',');
        getline(ss, dest, ',');
        getline(ss, distance, ',');
        if (count == 5) {
            getline(ss, name, ',');
            getline(ss, destName);
        }

        addBidirectionalEdge(std::stoi(id), std::stoi(dest), std::stod(distance));
    }

}

void Graph::tspBF() {
    if (getVertexSet().empty()) return;
    std::cout << "calculating ...\n";
    double minDistance = INT_MAX;

    std::vector<int> path;
    std::vector<int> order;

    for (int i = 0; i < getVertexSet().size(); i++) {
        order.push_back(i);
    }

    std::sort(order.begin(), order.end());
    do {
        double distance = 0;
        for (int i = 0; i < getVertexSet().size(); i++) {
            auto edges = getVertexSet().at(order.at(i))->getAdj();

            if (i == getVertexSet().size() - 1) {
                for (auto& e : edges) {
                    if (e->getDest()->getId() == 0) {
                        distance += e->getDistance();
                    }
                }
            }
            else {
                for (auto& e : edges) {
                    if (e->getDest()->getId() == order.at(i+1)) {
                        distance += e->getDistance();
                    }
                }
            }
        }

        if (distance < minDistance) {
            minDistance = distance;
            path.clear();
            for (int i = 0; i < order.size(); i++) {
                path.push_back(order.at(i));
            }
        }
    } while (std::next_permutation(order.begin() + 1, order.end()));


    for (int i = 0; i < path.size(); i++) {
        std::cout << path.at(i) << " ";
    }
    std::cout << minDistance << std::endl;
}

void Graph::fill(const std::string& path) {
    readVertices(path);
    readEdges(path);
}
