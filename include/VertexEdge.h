#ifndef DA_PROJ2_VERTEXEDGE_H
#define DA_PROJ2_VERTEXEDGE_H

#include <vector>

class Edge;

/*************************************** Vertex ***************************************/

class Vertex {
private:
    /**
     * @brief Represents the id of the vertex.
     */
    int id;

    /**
     * @brief A vector with the outgoing edges.
     */
    std::vector<Edge*> adj;

    /**
     * @brief A vector with the incoming edges.
     */
    std::vector<Edge*> incoming;

public:
    /**
     * @brief Constructor that initializes a vertex.
     *
     * @param id The vertex id.
     */
    Vertex(const int id);

    /**
     * @brief Returns the id of a vertex.
     *
     * @return The vertex id.
     */
    int getId() const;

    /**
     * @brief Sets the id of a vertex.
     *
     * @param id The new vertex id.
     */
    void setId(const int id);

    /**
     * @brief Connects two vertices by adding an edge.
     *
     * @param dest The destination vertex.
     * @param distance  The distance of the edge.
     *
     * @return The edge if it was successfully created.
     * @return nullptr otherwise.
     */
    Edge* addEdge(Vertex* dest, const double distance);


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
      * @brief The edge that connects the destination station to this station
      */
     Edge* reverse;

public:
    /**
     * @brief Constructor that initializes an edge.
     *
     * @param origin The origin of the edge.
     * @param dest The destinations of the edge.
     * @param distance The distance of the edge.
     */
    Edge(Vertex* origin, Vertex* dest, const double distance);

    /**
     * @brief Returns the origin of the edge.
     *
     * @return The origin of the edge.
     */
    Vertex* getOrigin() const;

    /**
     * @brief Sets the origin of the edge.
     *
     * @param origin The origin of the edge.
     */
    void setOrigin(Vertex* origin);

    /**
     * @brief Returns the destination of the edge.
     *
     * @return The destination of the edge.
     */
    Vertex* getDest() const;

    /**
     * @brief Sets the destination of the edge.
     *
     * @param dest The destination of the edge.
     */
     void setDest(Vertex* dest);


     /**
      * @brief Returns the distance of the edge.
      *
      * @return The distance of the edge.
      */
     double getDistance() const;

     /**
      * @brief Sets the distance of the edge.
      *
      * @param distance The distance of the edge.
      */
     void setDistance(double distance);

     /**
      * @brief Returns the reverse edge that connects the destination station to this station.
      *
      * @return The resverse edge.
      */
     Edge* getReverse() const;

     /**
      * @brief Sets the reverse edge that connects the destination station to this station.
      *
      * @param reverse The reverse edge.
      */
     void setReverse(Edge* reverse);

};



#endif //DA_PROJ2_VERTEXEDGE_H
