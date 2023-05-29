#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>

#include "../include/Graph.h"
#include "../include/MutablePriorityQueue.h"
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
        bool validPath = true;
        double distance = 0;
      //  std::cout << "NEW" << std::endl;
        for (int i = 0; i < getVertexSet().size(); i++) {
           // std::cout << getVertexSet().at(order.at(i))->getId() << std::endl;
          //  std::cout << "\tTO: ";
            auto edges = getVertexSet().at(order.at(i))->getAdj();
            auto prevDistance = distance;

            if (i == getVertexSet().size() - 1) {
                for (auto& e : edges) {
                    if (e->getDest()->getId() == 0) {
                        distance += e->getDistance();
                    //    std::cout << " 0 com distancia: " << distance << std::endl;
                    }
                }
            }
            else {
                for (auto &e: edges) {
                    if (e->getDest()->getId() == getVertexSet().at(order.at(i+1))->getId()) {
                        distance += e->getDistance();
                    //    std::cout << e->getDest()->getId() << " com distancia: " << distance << std::endl;
                    }
                }
            }
            if (distance == prevDistance) {
                validPath = false;
            }
        }

        //std::cout << "VP: " << validPath << std::endl;
        if (distance < minDistance && validPath) {
            minDistance = distance;
            std::cout << distance << std::endl;
            path.clear();
            for (int i = 0; i < order.size(); i++) {
                path.push_back(getVertexSet().at(order.at(i))->getId());
                std::cout << getVertexSet().at(order.at(i))->getId() << " ";
            }
            std::cout << std::endl;
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

void Graph::prim() {
    for (auto& v : getVertexSet()) {
        v->setVisited(false);
        v->setDistance(INT_MAX);
        v->setPath(nullptr);
    }

    std::sort(vertexSet.begin(), vertexSet.end());

    Vertex* root = getVertexSet().front();
    root->setDistance(0);

    MutablePriorityQueue<Vertex> q;

    for (auto& v : getVertexSet()) {
        q.insert(v);
    }

    while (!q.empty()) {
        Vertex* vertex = q.extractMin();
        vertex->setVisited(true);
        for (auto& e : vertex->getAdj()) {
            Vertex* neighbor = e->getDest();
            if (!neighbor->isVisited() && e->getDistance() < neighbor->getDistance()) {
                neighbor->setPath(e);
                neighbor->setDistance(e->getDistance());
                q.decreaseKey(neighbor);
            }
        }
    }
}

void Graph::dfsPreOrder(Vertex *vertex, std::vector<Vertex *> &preOrder) {
    preOrder.push_back(vertex);
    vertex->setVisited(true);

    for (auto& v : getVertexSet()) {
        if (v->getPath() && v->getPath()->getOrigin()->getId() == vertex->getId() && !v->isVisited()) {
            dfsPreOrder(v, preOrder);
        }
    }
}

void Graph::preOrder() {
    for (auto& v : getVertexSet()) {
        v->setVisited(false);
    }

    std::vector<Vertex*> order;

    dfsPreOrder(getVertexSet().front(), order);

    for (auto& v : order) {
        std::cout << v->getId() << " ";
    }
}