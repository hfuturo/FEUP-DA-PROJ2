#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>

#include "../include/Graph.h"
#include "../include/MutablePriorityQueue.h"
#include "../include/VertexEdge.h"
#include "../include/constants.h"


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
    std::string id, dest, distance, fileLine, trash;

    getline(file, fileLine);
    std::stringstream ssTrash(fileLine);

    while (getline(ssTrash, trash, ',')) count ++;

    while (getline(file, fileLine)) {
        std::stringstream ss(fileLine);
        getline(ss, id, ',');
        getline(ss, dest, ',');
        getline(ss, distance, ',');
        if (count == 5) {
            getline(ss, trash, ',');
            getline(ss, trash);
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

    // possivel melhoria -> em vez de fazer sort (nlogn) percorrer vetor (n)
    std::sort(vertexSet.begin(), vertexSet.end(), [](Vertex* v1, Vertex*v2) {return v1->getId() < v2->getId();});

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

    for (auto& v  :getVertexSet()) {
        if (v->getPath()) std::cout << v->getPath()->getOrigin()->getId() << "->" << v->getId() << std::endl;
    }
    std::cout << std::endl;
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

std::vector<Vertex*> Graph::preOrder() {
    for (auto& v : getVertexSet()) {
        v->setVisited(false);
    }

    std::vector<Vertex*> order;

    dfsPreOrder(getVertexSet().front(), order);

    return order;
}

void Graph::approximation() {
    prim();
    std::vector<Vertex*> order = preOrder();
    double distance = 0;

    for (int i = 0; i < order.size(); i++) {
        auto v = order.at(i);
        double prevDistance = distance;
        for (auto& e : v->getAdj()) {
            if (i == order.size() - 1) {
                if (e->getDest()->getId() == 0) {
                    distance += e->getDistance();
                }
            }
            else {
                if (e->getDest()->getId() == order.at(i + 1)->getId()) {
                    distance += e->getDistance();
                }
            }
        }
        if (prevDistance == distance) {
            distance += i == order.size() - 1 ? haversine(v, findVertex(0)) : haversine(v, order.at(i+1));
            std::cout << "USED HAVERSINE\n\t" << v->getId();
            if (i ==order.size() - 1) {
                std::cout << " to 0 with distance: " << haversine(v, findVertex(0)) << "\n";
            }
            else {
                std::cout << " to " << order.at(i+1)->getId() << " with distance: " << haversine(v, order.at(i+1))<< std::endl;
            }
        }
    }

    for (auto& v : order) {
        std::cout << v->getId() << " ";
    }

    std::cout << std::endl;
    std::cout << distance << std::endl;
}

double Graph::haversine(Vertex *v1, Vertex *v2) {
    if (!v1 || !v2) return -1;

    double rad_lon1 = convert_to_rads(v1->getLongitude());
    double rad_lat1 = convert_to_rads(v1->getLatitude());
    double rad_lon2 = convert_to_rads(v2->getLongitude());
    double rad_lat2 = convert_to_rads(v2->getLatitude());

    double delta_lat = rad_lat2 - rad_lat1;
    double delta_lon = rad_lon2 - rad_lon1;

    double aux = std::pow(std::sin(delta_lat / 2), 2) + std::cos(rad_lat1) *
                    std::cos(rad_lat2) * std::pow(std::sin(delta_lon / 2), 2);

    double c = 2.0 * std::atan2(std::sqrt(aux), std::sqrt(1.0 - aux));
    double distance = EARTH_RADIUS * c;
    return distance;
}

double Graph::convert_to_rads(double coord) {
    return coord * M_PI / 180;
}