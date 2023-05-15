#ifndef DA_PROJ2_GRAPH_H
#define DA_PROJ2_GRAPH_H

#include <vector>

#include "../include/VertexEdge.h"

class Graph {
    std::vector<Vertex*> vertexSet;

public:
    /**
     * @brief Creates an empty graph.
     */
    Graph();

    /**
     * @brief Get the vector where all the stations are stored.
     *
     * @note Complexity time: O(1).
     *
     * @return A vector containing all the stations of the graph.
     */
     std::vector<Vertex*> getVertexSet() const;

     /**
      * @brief Adds a vertex to the graph.
      *
      * @param id The vertex id
      *
      * @return True if the vertex was successfully added.
      * @return False otherwise.
      */
     bool addVertex(const int id);

     /**
      * @brief Adds an edge to the graph.
      *
      * @param origin The vertex of origin.
      * @param dest The vertex of destination.
      * @param distance The distance of the edge
      *
      * @return True if the edge was successfullu added.
      * @return False otherwise.
      */
     bool addEdge(const int origin, const int  dest, const double distance);

     Vertex* findVertex(const int id) const;
};

#endif //DA_PROJ2_GRAPH_H
