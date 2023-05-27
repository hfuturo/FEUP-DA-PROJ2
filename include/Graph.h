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
     bool addBidirectionalEdge(const int origin, const int  dest, const double distance);

     /**
      * @brief Searches all the vertices and returns one if the given id exists.
      *
      * @param id The id of the vertex we are looking for
      *
      * @return The vertex if exists. Nullptr otherwise.
      */
     Vertex* findVertex(const int id) const;

    /**
     * @brief Populates the graph with the information from the csv files in the dataset.
     *
     * @note Complexity time: O(V^2).
     */
     void fill(const std::string& path);

     /**
      * @brief Reads the vertices from the file and adds them to the graph.
      *
      * @note Complexity time: O(V)
      */
     void readVertices(const std::string& path);

     /**
      * @brief Reads the edges from the file and adds them into the graph.
      *
      * @note Complexity time: O(E)
      */
     void readEdges(const std::string& path);

     /**
      * @brief Performs a brute force algorithm to finds the tsp of a graph
      *
      * @note Complexity time: O(n*n!)
      */
     void tspBF();
};

#endif //DA_PROJ2_GRAPH_H
