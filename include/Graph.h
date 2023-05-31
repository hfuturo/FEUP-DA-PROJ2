#ifndef DA_PROJ2_GRAPH_H
#define DA_PROJ2_GRAPH_H

#include <vector>
#include <unordered_map>

#include "../include/VertexEdge.h"

/**
 * @brief Represents a graph where the nodes are locations related to shipping deliveries, tourism, ... And the edges represent the connection between these nodes.
 */
class Graph {
    /**
     * @brief Stores all nodes of the graph.
     */
    std::unordered_map<int, Vertex*> vertexSet;
public:
    /**
     * @brief Creates an empty graph.
     *
     * @note: Complexity time: O(1)
     */
    Graph();

    /**
     * @brief Get the unordered_map where all the stations are stored.
     *
     * @note Complexity time: O(1).
     *
     * @return An unordered_map containing all the stations of the graph.
     */
    const std::unordered_map<int, Vertex*>& getVertexSet() const;

     /**
      * @brief Adds a vertex to the graph.
      *
      * @param id The vertex id
      *
      * @note Complexity time: O(V)
      *
      * @return True if the vertex was successfully added.
      * @return False otherwise.
      */
     bool addVertex(const int id);

     /**
      * @brief Adds a vertex in info from a real graph
      *
      * @note Complexity time: O(V)
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
      * @note Complexity time: O(V)
      *
      * @param origin The vertex of origin.
      * @param dest The vertex of destination.
      * @param distance The distance of the edge
      *
      * @return True if the edge was successfully added.
      * @return False otherwise.
      */
     bool addBidirectionalEdge(const int origin, const int  dest, const double distance);

    /**
     * @brief Populates the graph with the information from the csv files in the dataset.
     *
     * @note O(V+E)
     *
     * @param path The file path
     * @param isRealGraph Boolean telling if file is from Real Graph.
     */
     void fill(const std::string& path, bool isRealGraph);

     /**
      * @brief Reads the vertices from the file and adds them to the graph.
      *
      * @note Complexity time: O(V)
      *
      * @param path The file path
      * @param isRealGraph Boolean telling if file is from Real Graph.
      */
     void readVertices(const std::string& path, bool isRealGraph);

     /**
      * @brief Reads the edges from the file and adds them into the graph.
      *
      * @param path The file path
      *
      * @note Complexity time: O(E)
      */
     void readEdges(const std::string& path);

     /**
      * @brief Does the recursive work of tspBT
      *
      * @note Complexity time: O(V!)
      *
      * @param vertex The root of the TSP problem
      * @param minDist The minimal distance of the TSP problem
      * @param distance The current distance of the TSP
      * @param count The number of the nodes visited in the current path
      * @param path The current path
      */
     void tspBTRec(Vertex* vertex, double& minDist, double distance, unsigned int count, std::vector<int>& path);

     /**
      * @brief Executes a backtracking algorithm to solve the TSP problem.
      *
      * @note Complexity time: O(V!)
      *
      * @param path The path of nodes corresponding to the minimal distance.
      *
      * @return The minimal distance.
      */
     double tspBT(std::vector<int>& path);

     /**
      * @brief Executes prim's algorithm to compute MST
      *
      * @note Complexity time: O(E Log V)
      */
     void prim();

     /**
      * @brief Executes Depth First Search (DFS) algorithm to compute pre-order of graph
      *
      * @param vertex The root of DFS
      * @param preOrder The order of DFS
      *
      * @note Complexity time: O(V+E)
      */
     void dfsPreOrder(Vertex* vertex, std::vector<Vertex*>& preOrder);

     /**
      * @brief Finds the preOrder of a graph
      *
      * @note Complexity time: O(V+E)
      *
      * @return Vector with vertices in pre-order
      */
     std::vector<Vertex*> preOrder();

     /**
      * @brief Executes an approximation algorithm for TSP
      *
      * @note Complexity time: O(V+E)
      *
      * @param path The path corresponding to the best value
      * @return The approximation value.
      */
     double approximation(std::vector<Vertex*>& path);

     /**
      * @brief Calculates the distance between two vertices using their latitude and longitude
      *
      * @note Complexity time: O(1)
      *
      * @param v1 The first vertex
      * @param v2 The second vertex
      * @return The distance between these vertices
      */
     double haversine(Vertex* v1, Vertex* v2);

     /**
      * @brief Converts a coordinate to radians
      *
      * @note Complexity time: O(1)
      *
      * @param coord The coordinate
      * @return The coordinate in radians
      */
     double convert_to_rads(double coord);

     /**
      * @brief Calculates a possible TSP solution visiting the closest neighbor.
      *
      * @param path The path of the possible TSP solution.
      * @return The distance upon success or -1 otherwise.
      */
     double otherHeuristics(std::vector<int>& path);

     /**
      * @brief Executes the "heavy work" of the heuristic. Visits every node using the shortest edge using recursion.
      *
      * @param vertex The root
      * @param distance The current distance
      * @param path The current path
      * @param count The number of nodes already visited
      * @param validApproximation Flag telling is graph is complete or incomplete. If complete this variable is set to true and false otherwise.
      */
     void otherHeuristicsRec(Vertex* vertex, double& distance, std::vector<int>& path, unsigned int count, bool& validApproximation);

};

#endif //DA_PROJ2_GRAPH_H
