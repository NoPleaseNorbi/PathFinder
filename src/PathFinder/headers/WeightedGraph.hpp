#pragma once

#ifndef _WEIGHTEDGRAPH_HPP_
#define _WEIGHTEDGRAPH_HPP_

#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <SFML/Graphics.hpp>

/// \struct PointComparator
/// \brief Functor for comparing points in priority queues.
struct PointComparator {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second > b.second;
    }
};

/// \class WeightedGraph
/// \brief Class for representing a weighted graph and running various algorithms on it.
class WeightedGraph {
private:
    std::unordered_map<int, std::vector<std::pair<int, int>>> adjacency_list;  ///< Adjacency list representing the graph.

    std::vector<sf::CircleShape> vertices;             ///< Vector of vertices in the graph.
    std::vector<sf::Text> vertex_numbers;              ///< Vector of texts representing vertex numbers.
    std::vector<sf::VertexArray> edges;                ///< Vector of edge graphics.
    std::vector<sf::Text> edge_weights;                ///< Vector of texts representing edge weights.
    std::vector<sf::ConvexShape> edge_going_to_signaling_triangles;  ///< Vector of triangles indicating edge directions.

    std::vector<bool> visited;                         ///< Vector indicating visited nodes.
    std::vector<int> distances;                        ///< Vector to save distances of nodes from each other.
    std::vector<int> parents;                          ///< Vector to save parents of each node.

    bool finished;                                     ///< Flag indicating if an algorithm has finished.

    int bellman_curr_vertex;                           ///< Current vertex during Bellman-Ford algorithm execution.
    int bellman_curr_edge;                             ///< Current edge during Bellman-Ford algorithm execution.
    std::queue<int> bfs_queue;                         ///< Queue for Breadth First Search.
    std::stack<int> dfs_stack;                         ///< Stack for Depth First Search.
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, PointComparator> dijkstra_priority_queue;  ///< Priority queue for Dijkstra's algorithm.



public:
    /// \brief Default constructor to initialize WeightedGraph object.
    WeightedGraph();

    /// \brief Add an edge to the graph.
    void AddEdge(const int& from, const int& to, const int& weight, const sf::VertexArray& edge, const sf::Text& weight_graphics);
    
    /// \brief Clear the vectors containing graph elements.
    void Clear();

    /// \brief Add a vertex to the graph.
    void AddVertex(const sf::CircleShape& vertex, const sf::Text& vertex_number);

    /// \brief Add a signaling triangle to indicate direction of an edge.
    void AddTriangle(const sf::ConvexShape& triangle);

    /// \brief Change color of a vertex.
    void ChangeVertexColor(const sf::Color& color, const int& index);

    /// \brief Draw the graph on a given render window.
    void Draw(sf::RenderWindow& window);

    /// \brief Run Dijkstra's algorithm.
    void RunDijkstra();

    /// \brief Run Breadth First Search algorithm.
    void RunBFS();

    /// \brief Run Depth First Search algorithm.
    void RunDFS();

    /// \brief Run Bellman-Ford algorithm.
    void RunBellmanFord();

    /// \brief Set up Dijkstra's algorithm.
    void SetUpDijkstra();

    /// \brief Set up Breadth First Search algorithm.
    void SetUpBFS();

    /// \brief Set up Depth First Search algorithm.
    void SetUpDFS();

    /// \brief Set up Bellman-Ford algorithm.
    void SetUpBellmanFord();

    /// \brief Trace the shortest path found by the algorithm.
    void TracePath();

    /// \brief Reset the graph and algorithm states.
    void Reset();

    /// \brief Get the vertices of the graph.
    /// \return Vector of vertices.
    std::vector<sf::CircleShape> getVertices();

    /// \brief Get the adjacency list of a vertex.
    /// \param vertex The vertex whose adjacency list is to be retrieved.
    /// \return The adjacency list of the vertex.
    std::vector<std::pair<int, int>> getAdjacencyList(const int& vertex);

    /// \brief Check if an algorithm has finished.
    /// \return True if the algorithm has finished, otherwise false.
    bool getFinished();
};

#endif