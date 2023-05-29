#include "../include/VertexEdge.h"

/********************************** Vertex **********************************/

Vertex::Vertex(const int id): id(id), distance(0), visited(false), path(nullptr)  {}

Vertex::Vertex(const int id, std::string &name): id(id), name(name), distance(0), visited(false), path(nullptr) {}

int Vertex::getId() const {
    return this->id;
}

void Vertex::setId(const int id) {
    this->id = id;
}

std::vector<Edge *> Vertex::getAdj() const {
    return this->adj;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

double Vertex::getDistance() const {
    return this->distance;
}

void Vertex::setDistance(double distance) {
    this->distance = distance;
}

bool Vertex::isVisited() const {
    return this->visited;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

Edge *Vertex::getPath() const {
    return this->path;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

bool Vertex::operator<(Vertex &vertex) const {
    return this->distance < vertex.getDistance();
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
