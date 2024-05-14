#pragma once

#ifndef _UWEIGHTEDGRAPH_HPP_
#define _UWEIGHTEDGRAPH_HPP_

#include "../headers/CellStates.hpp"
#include <vector>
#include <queue>
#include <stack>
#include <functional>
#include <SFML/Graphics.hpp>

/// \struct PointComparator
/// \brief Functor for comparing points in priority queues.
template<typename T>
struct PointComparator {
	bool operator()(const std::pair<T, sf::Vector2i>& a, const std::pair<T, sf::Vector2i>& b) const {
		return a.first > b.first;
	}
};

/// \class UnweightedGraph
/// \brief Class for representing an unweighted graph and running various algorithms on it.
class UnweightedGraph {
public:
	/// \brief Constructor to initialize the unweighted graph with vertices, starting point, and ending point.
	/// \param vertices_of_the_graph The grid representing the vertices of the graph, the grid.
	/// \param starting_point The starting point of the graph.
	/// \param ending_point The ending point of the graph.
	UnweightedGraph(const std::vector<std::vector<CellState>>& vertices_of_the_graph, const sf::Vector2i& starting_point, const sf::Vector2i& ending_point);

	/// \brief Run Breadth First Search algorithm.
	void RunBFS();

	/// \brief Run Depth First Search algorithm.
	void RunDFS();

	/// \brief Run Dijkstra's algorithm.
	void RunDijkstra();

	/// \brief Run A* algorithm.
	void RunAStar();

	/// \brief Run Greedy Best-First Search algorithm.
	void RunGBFS();

	/// \brief Set up Breadth First Search algorithm.
	void SetUpBFS();

	/// \brief Set up Depth First Search algorithm.
	void SetUpDFS();

	/// \brief Set up Dijkstra's algorithm.
	void SetUpDijkstra();

	/// \brief Set up A* algorithm.
	void SetUpAStar();

	/// \brief Set up Greedy Best-First Search algorithm.
	void SetUpGBFS();

	
	/// \brief Reset the algorithm and grid after the RouteHelper enums colored the grid differently.
	void ResetAlgorithm();

	/// \brief Trace the path from the starting node to the end.
	/// \return The path represented by a vector of vertices.
	std::vector<std::vector<CellState>> TraceShortestPath();
	
	/// \brief Check if a cell is available next to the given cell.
	/// \param row The row of the cell.
	/// \param col The column of the cell.
	/// \return True if the cell is valid, otherwise false.
	bool CheckCellValidity(const int& row, const int& col);
	
	/// \brief Get the grid representing the vertices of the graph.
	/// \return The grid representing the vertices.
	std::vector<std::vector<CellState>> getVertices();

	/// \brief Check if an algorithm has finished.
	/// \return True if the algorithm has finished, otherwise false.
	bool getFinished();
	
	/// \brief Set the starting point of the graph.
	/// \param starting_point The starting point to set.
	void setStart(const sf::Vector2i& starting_point);

	/// \brief Set the ending point of the graph.
	/// \param ending_point The ending point to set.
	void setEnd(const sf::Vector2i& ending_point);

	/// \brief Set the obstacles on the graph.
	/// \param obstacles The obstacles to set.
	void setObstacles(const std::vector<std::vector<CellState>>& obstacles);

private:
	bool finished;                                 ///< Flag indicating if an algorithm has finished.

	const int row_adder[4] = { -1, 0, 1, 0 };      ///< Helper array for row movement.
	const int col_adder[4] = { 0, 1, 0, -1 };      ///< Helper array for column movement.

	sf::Vector2i start;                            ///< Start point of the graph.
	sf::Vector2i end;                              ///< End point of the graph.

	int column_size;                               ///< Number of columns in the grid.
	int row_size;                                  ///< Number of rows in the grid.

	std::vector<std::vector<CellState>> vertices;  ///< Grid representing the vertices of the graph.
	std::vector<std::vector<int>> distances;       ///< Matrix of distances between vertices.
	std::vector<std::vector<bool>> visited;        ///< Matrix indicating visited vertices.

	std::queue<sf::Vector2i> bfs_queue;            ///< Queue for Breadth First Search.
	std::stack<sf::Vector2i> dfs_stack;            ///< Stack for Depth First Search.
	std::priority_queue<std::pair<int, sf::Vector2i>, std::vector<std::pair<int, sf::Vector2i>>, PointComparator<int>> dijkstra_priority_queue;  ///< Priority queue for Dijkstra's algorithm.
	std::priority_queue<std::pair<float, sf::Vector2i>, std::vector<std::pair<float, sf::Vector2i>>, PointComparator<float>> astar_priority_queue;  ///< Priority queue for A* algorithm.
	std::priority_queue<std::pair<float, sf::Vector2i>, std::vector<std::pair<float, sf::Vector2i>>, PointComparator<float>> gbfs_priority_queue;    ///< Priority queue for Greedy Best-First Search algorithm.
};

#endif
