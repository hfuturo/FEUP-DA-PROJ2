#ifndef DA_PROJ2_VERTEXEDGE_H
#define DA_PROJ2_VERTEXEDGE_H

#include <vector>
#include <string>
#include <limits>

class Edge;

/*************************************** Vertex ***************************************/

/**
 * @brief Represents the maximum number representable by a double.
 */
#define INF std::numeric_limits<double>::max()

/**
 * @brief Represents a vertex in the graph.
 */
class Vertex {
private:
    /**
     * @brief Represents the id of the vertex.
     */
    int id;

    /**
     * @brief The longitude of the vertex.
     */
    double longitude;

    /**
     * @brief The latitude of the vertex.
     */
    double latitude;

    /**
     * @brief A vector with the outgoing edges.
     */
    std::vector<Edge*> adj;

    /**
     * @brief A vector with the incoming edges.
     */
    std::vector<Edge*> incoming;

    /**
     * @brief Vertex already been visited
     */
    bool visited;

    /**
     * @brief The distance it takes to get to this vertex.
     */
    double distance;

    /**
     * @brief Edge that connects this vertex to the previous one
     */
    Edge* path;

public:
    /**
     * @brief Constructor that initializes a vertex with id.
     *
     * @note Used for Toy-graphs and Medium Graphs
     * @note Complexity time: O(1)
     *
     * @param id The vertex id.
     */
    Vertex(const int id);

    /**
     * @brief Constructor that initializes a vertex with id, longitude and latitude.
     *
     * @note Used for Real-world Graphs
     * @note Complexity time: O(1)
     *
     * @param id The id
     * @param longitude The longitude
     * @param latitude The latitude
     */
    Vertex(const int id, const double longitude, const double latitude);

    /**
     * @brief Returns the id of a vertex.
     *
     * @note Complexity time: O(1)
     *
     * @return The vertex id.
     */
    int getId() const;

    /**
     * @brief Return the longitude of the vertex
     *
     * @note Complexity time: O(1)
     *
     * @return The longitude
     */
    double getLongitude() const;

    /**
     * @brief Returns the latitude of the vertex
     *
     * @note Complexity time: O(1)
     *
     * @return The latitude
     */
    double getLatitude() const;

    /**
     * @brief Sees if a vertex has benn visited.
     *
     * @note Complexity time: O(1)
     *
     * @return True if visited, False otherwise.
     */
    bool isVisited() const;

    /**
     * @brief Sets a vertex as visited or not.
     *
     * @note Complexity time: O(1)
     *
     * @param visited The visited attribute.
     */
    void setVisited(bool visited);

    /**
     * @brief Gets the distance it takes to get to this vertex.
     *
     * @note Complexity time: O(1)
     *
     * @return The distance.
     */
    double getDistance() const;

    /**
     * @brief Sets the distance it takes to get to this vertex.
     *
     * @note Complexity time: O(1)
     *
     * @param distance The distance.
     */
    void setDistance(double distance);

    /**
     * @brief Gets the edge that connects this vertex to the previous one.
     *
     * @note Complexity time: O(1)
     *
     * @return The Edge if the Vertex is connected. nullptr otherwise.
     */
    Edge* getPath() const;

    /**
     * @brief Sets the edge that connects this vertex to the previous one.
     *
     * @note Complexity time: O(1)
     *
     * @param path The edge that connects this vertex to the previous one.
     */
    void setPath(Edge* path);

    /**
     * @brief Connects two vertices by adding an edge.
     *
     * @note Complexity time: O(1)
     *
     * @param dest The destination vertex.
     * @param distance  The distance of the edge.
     *
     * @return The edge if it was successfully created.
     * @return nullptr otherwise.
     */
    Edge* addEdge(Vertex* dest, const double distance);

    /**
     * @brief Gets the outgoing edges of this vertex.
     *
     * @note Complexity time: O(1)
     *
     * @return Vector with the outgoing edges.
     */
    std::vector<Edge*> getAdj() const;

    /**
     * @brief Compares this vertex's cost to another vertex's cost.
     *
     * @note Complexity time: O(1).
     *
     * @param vertex The another vertex that we are going  to compare with.
     * @return True if this vertex's cost is fewer than the other vertex's cost. False otherwise.
     */
    bool operator<(Vertex& vertex) const;

    /**
    * @brief Index of this vertex in Priority Queue. Need for Prim.
    */
    int queueIndex;
};


/*************************************** Edge ***************************************/

/**
 * @brief Represents an edge between two vertices.
 */
class Edge {
private:
    /**
     * @brief The origin of the edge.
     */
    Vertex* origin;

    /**
     * @brief The destination of the edge.
     */
     Vertex* dest;

     /**
      * @brief The distance of the edge.
      */
     double distance;

     /**
      * @brief The edge that connects the destination station to this station.
      */
     Edge* reverse;

public:
    /**
     * @brief Constructor that initializes an edge.
     *
     * @note Used for all graphs.
     * @note Complexity time: O(1)
     *
     * @param origin The origin of the edge.
     * @param dest The destinations of the edge.
     * @param distance The distance of the edge.
     */
    Edge(Vertex* origin, Vertex* dest, const double distance);

    /**
     * @brief Returns the origin of the edge.
     *
     * @note Complexity time: O(1)
     *
     * @return The origin of the edge.
     */
    Vertex* getOrigin() const;

    /**
     * @brief Returns the destination of the edge.
     *
     * @note Complexity time: O(1)
     *
     * @return The destination of the edge.
     */
    Vertex* getDest() const;

     /**
      * @brief Returns the distance of the edge.
      *
      * @note Complexity time: O(1)
      *
      * @return The distance of the edge.
      */
     double getDistance() const;

     /**
      * @brief Sets the reverse edge that connects the destination station to this station.
      *
      * @note Complexity time: O(1)
      *
      * @param reverse The reverse edge.
      */
     void setReverse(Edge* reverse);
};



#endif //DA_PROJ2_VERTEXEDGE_H
