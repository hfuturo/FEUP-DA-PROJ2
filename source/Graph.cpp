#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <map>

#include "../include/Graph.h"
#include "../include/MutablePriorityQueue.h"
#include "../include/constants.h"


Graph::Graph() {}

const std::unordered_map<int, Vertex *> &Graph::getVertexSet() const {
    return this->vertexSet;
}

bool Graph::addVertex(const int id) {
    vertexSet[id] = new Vertex(id);
    return true;
}

bool Graph::addVertexRealGraph(const int id, const double longitude, const double latitude) {
    vertexSet[id] = new Vertex(id, longitude, latitude);
    return true;
}

bool Graph::addBidirectionalEdge(const int origin, const int dest, const double distance) {
    if (distance < 0 || origin < 0 || dest < 0) return false;
    auto v1 = vertexSet.find(origin);
    auto v2 = vertexSet.find(dest);
    if (v1 == vertexSet.end() || v2 == vertexSet.end()) return false;
    auto e1 =  v1->second->addEdge(v2->second, distance);
    auto e2 = v2->second->addEdge(v1->second, distance);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void Graph::readVertices(const std::string& path, bool isRealGraph) {
    std::ifstream file(path);

    if (file.fail()) return;

    int count = 0;
    std::string id, dest, distance, longitude, latitude, fileLine, trash;

    getline(file, fileLine);
    std::stringstream ssTrash(fileLine);

    while (getline(ssTrash, trash, ',')) count ++;

    if (isRealGraph) {
        while (getline(file, fileLine)) {
            std::stringstream ss(fileLine);
            getline(ss, id, ',');
            getline(ss, longitude, ',');
            getline(ss, latitude);
            addVertexRealGraph(std::stoi(id), std::stod(longitude), std::stod(latitude));
        }
    }
    else {
        while (getline(file, fileLine)) {
            std::stringstream ss(fileLine);
            getline(ss, id, ',');
            getline(ss, dest, ',');
            getline(ss, distance, ',');
            if (count == 5) {
                getline(ss, trash, ',');
                getline(ss, trash);
            }
            addVertex(std::stoi(id));
            addVertex(std::stoi(dest));
        }
    }

    file.close();
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

    file.close();

}

void Graph::fill(const std::string& path, bool isRealGraph) {
    if (isRealGraph) {
        readVertices(path + "/nodes.csv", true);
        readEdges(path + "/edges.csv");
    }
    else {
        readVertices(path, isRealGraph);
        readEdges(path);
    }
}

void Graph::prim() {
    for (auto& v : getVertexSet()) {
        v.second->setVisited(false);
        v.second->setDistance(INF);
        v.second->setPath(nullptr);
    }

    auto root = getVertexSet().find(0);
    root->second->setDistance(0);

    MutablePriorityQueue<Vertex> q;

    for (auto& v : getVertexSet()) {
        q.insert(v.second);
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
        if (v.second->getPath() && v.second->getPath()->getOrigin()->getId() == vertex->getId() && !v.second->isVisited()) {
            dfsPreOrder(v.second, preOrder);
        }
    }
}

std::vector<Vertex*> Graph::preOrder() {
    for (auto& v : getVertexSet()) {
        v.second->setVisited(false);
    }

    std::vector<Vertex*> order;

    dfsPreOrder(getVertexSet().find(0)->second, order);

    return order;
}

double Graph::approximation(std::vector<Vertex*>& path) {
    prim();
    path = preOrder();
    double distance = 0;

    for (int i = 0; i < path.size(); i++) {
        auto v = path.at(i);
        bool edgesConnected = false;
        for (auto& e : v->getAdj()) {
            if (i == path.size() - 1) {
                if (e->getDest()->getId() == 0) {
                    distance += e->getDistance();
                    edgesConnected = true;
                }
            }
            else {
                if (e->getDest()->getId() == path.at(i + 1)->getId()) {
                    distance += e->getDistance();
                    edgesConnected = true;
                }
            }
        }
        if (!edgesConnected) {
            distance += i == path.size() - 1 ? haversine(v, getVertexSet().find(0)->second) : haversine(v, path.at(i+1));
            std::cout << "USED HAVERSINE\n\t" << v->getId();
            if (i == path.size() - 1) {
                std::cout << " to 0 with distance: " << haversine(v, getVertexSet().find(0)->second) << "\n";
            }
            else {
                std::cout << " to " << path.at(i+1)->getId() << " with distance: " << haversine(v, path.at(i+1))<< std::endl;
            }
        }
    }

    return distance;
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

void Graph::tspBTRec(Vertex * vertex, double &minDist, double distance, unsigned int count, std::vector<int> &path) {
    if (distance >= minDist) return;

    if (count == getVertexSet().size() - 1) {
        for (auto& e : vertex->getAdj()) {
            if (e->getDest()->getId() == 0) {
                minDist = std::min(minDist, distance + e->getDistance());
                return;
            }
        }
    }

    for (auto& e : vertex->getAdj()) {
        if (!e->getDest()->isVisited()) {
            e->getDest()->setVisited(true);
            tspBTRec(e->getDest(), minDist, distance + e->getDistance(), count + 1, path);
            e->getDest()->setVisited(false);
        }
    }
}

double Graph::tspBT(std::vector<int> &path) {
    for (auto& v : getVertexSet()) {
        v.second->setVisited(false);
    }

    double minDist = INF;
    double distance = 0;
    unsigned int count = 0;
    auto root = getVertexSet().find(0)->second;
    root->setVisited(true);
    tspBTRec(root, minDist, distance, count, path);

    return minDist;
}

void Graph::otherHeuristicsRec(Vertex *vertex, double& distance, std::vector<int>& path, unsigned int count, bool& validApproximation) {
    if (!validApproximation) return;

    auto edges = vertex->getAdj();
    double minDist = INF;
    Edge* e = nullptr;

    for (auto& edge : edges) {
        if (count == getVertexSet().size() - 1) {
            if (edge->getDest()->getId() == 0) {
                distance += edge->getDistance();
                return;
            }
        }
        else {
            if (edge->getDistance() < minDist && !edge->getDest()->isVisited()) {
                minDist = edge->getDistance();
                e = edge;
            }
        }
    }

    if (!e) {
        validApproximation = false;
        otherHeuristicsRec(nullptr, distance, path, count + 1, validApproximation);
    }
    else {
        e->getDest()->setVisited(true);
        path.push_back(e->getDest()->getId());
        distance += minDist;
        otherHeuristicsRec(e->getDest(), distance, path, count + 1, validApproximation);
    }
}

double Graph::otherHeuristics(std::vector<int>& path) {
    double distance = 0;
    unsigned int count = 0;
    bool validApproximation = true;

    for (auto& v : getVertexSet()) {
        v.second->setVisited(false);
    }

    auto root = getVertexSet().find(0);
    root->second->setVisited(true);
    path.push_back(root->first);
    otherHeuristicsRec(root->second, distance, path, count, validApproximation);

    return validApproximation ? distance : -1;
}