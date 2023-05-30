#ifndef DA_PROJ2_GRAPH_H
#define DA_PROJ2_GRAPH_H

#include <vector>
#include <unordered_map>

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
      * @brief Adds a vertex in info from a real graph
      *
      * @param id The vertex id
      * @param longitude The longitude of the vertex
      * @param latitude The latitude of the vertex
      * @return True if the vertex was successfully added.
      * @return False otherwise.
      */
      bool addVertexRealGraph(const int id, const double longitude, const double latitude);

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
     void fill(const std::string& path, bool isRealGraph);

     /**
      * @brief Reads the vertices from the file and adds them to the graph.
      *
      * @note Complexity time: O(V)
      */
     void readVertices(const std::string& path, bool isRealGraph);

     /**
      * @brief Reads the edges from the file and adds them into the graph.
      *
      * @note Complexity time: O(E)
      */
     void readEdges(const std::string& path);

     /**
      * @brief Performs a brute force algorithm to finds the tsp of a graph
      *
      * @note Complexity time: O(V*V!)
      */
     double tspBF(std::vector<int>& path);

     /**
      * @brief Executes prim's algorithm to compute MST
      */
     void prim();

     /**
      * @brief Executes Depth First Search (DFS) algorithm to compute pre-order of graph
      */
     void dfsPreOrder(Vertex* vertex, std::vector<Vertex*>& preOrder);

     /**
      * @brief Finds the preOrder of a graph
      *
      * @return Vector with vertices in pre-order
      */
     std::vector<Vertex*> preOrder();

     /**
      * @brief Executes an approximation algorithm for TSP
      *
      * @return The approximation value.
      */
     double approximation(std::vector<Vertex*>& path);

     /**
      * @brief Calculates the distance between two vertices using their latitude and longitude
      *
      * @param v1 The first vertex
      * @param v2 The second vertex
      * @return The distance between these vertices
      */
     double haversine(Vertex* v1, Vertex* v2);

     /**
      * @brief Converts a coordinate to radians
      *
      * @param coord The coordinate
      * @return The coordinate in radians
      */
     double convert_to_rads(double coord);

     void tspBTRec(Vertex* vertex, double& minDist, double distance, unsigned int count, std::vector<int>& path);

     double tspBT(std::vector<int>& path);
};

#endif //DA_PROJ2_GRAPH_H
