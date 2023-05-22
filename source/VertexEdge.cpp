#include "../include/VertexEdge.h"

/********************************** Vertex **********************************/

Vertex::Vertex(const int id): id(id) {}

Vertex::Vertex(const int id, std::string &name): id(id), name(name) {}

int Vertex::getId() const {
    return this->id;
}

void Vertex::setId(const int id) {
    this->id = id;
}

Edge *Vertex::addEdge(Vertex *dest, const double distance) {
    if (dest == nullptr || distance < 0) return nullptr;
    Edge* edge = new Edge(this, dest, distance);
    adj.push_back(edge);
    dest->incoming.push_back(edge);
    return edge;
}


/********************************** Edge **********************************/

Edge::Edge(Vertex *origin, Vertex *dest, const double distance): origin(origin), dest(dest), distance(distance) {}

Vertex *Edge::getOrigin() const {
    return this->origin;
}

void Edge::setOrigin(Vertex *origin) {
    this->origin = origin;
}

Vertex *Edge::getDest() const {
    return this->dest;
}

void Edge::setDest(Vertex *dest) {
    this->dest = dest;
}

double Edge::getDistance() const {
    return this->distance;
}

void Edge::setDistance(double distance) {
    this->distance = distance;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}
