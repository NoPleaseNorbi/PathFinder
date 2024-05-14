#pragma once 

#ifndef _RANDOMMAZE_HPP_
#define _RANDOMMAZE_HPP_

#include "CellStates.hpp"
#include <vector>
#include <cstdlib>
#include <stack>
#include <SFML/Graphics.hpp>

/// \class RandomMaze
/// \brief Class for generating random mazes.
class RandomMaze {
private:
	int rows;												///< Number of rows in the maze.
	int cols;												///< Number of columns in the maze.
	std::vector<std::vector<CellState>> grid;				///< Grid representing the maze.
	bool finished;											///< Flag indicating if maze generation is finished.

	int current_row_for_random_maze;						///< Current row during random maze generation.
	int current_col_for_random_maze;						///< Current column during random maze generation.
	std::stack<std::pair<int, int>> backtracker_maze_stack; ///< Stack used for backtracking in maze generation.

	sf::Vector2i start;										///< Start position in the maze.
	sf::Vector2i end;										///< End position in the maze.
public:
	/// \brief Constructor to initialize the RandomMaze object with specified dimensions.
	/// \param rows_number The number of rows in the maze.
	/// \param cols_number The number of columns in the maze.
	RandomMaze(const int& rows_number, const int& cols_number);

	/// \brief Get neighboring cells of a given cell.
	/// \param x The x-coordinate of the cell.
	/// \param y The y-coordinate of the cell.
	/// \return A vector of neighboring cells.
	std::vector<std::pair<int, int>> getNeighbors(const int& x, const int& y);

	/// \brief Generate a maze using the recursive backtracker algorithm.
	void GenerateRecursiveBacktrackerMaze();

	/// \brief Generate a random maze, which uses just a basic random function.
	void GenerateRandomMaze();
	
	/// \brief Set up the simulation using the recursive backtracker algorithm.
	/// \param starting_point The starting point of the maze.
	/// \param ending_point The ending point of the maze.
	void SetUpRecursiveBacktrackerMaze(const sf::Vector2i& starting_point, const sf::Vector2i& ending_point);

	/// \brief Set up a random maze.
	void SetUpRandomMaze();
	
	/// \brief Set the grid of the maze.
	/// \param replacement_grid The grid to replace the current maze grid with.
	void setGrid(const std::vector<std::vector<CellState>>& replacement_grid);

	/// \brief Check if maze generation is finished.
	/// \return True if maze generation is finished, otherwise false.
	bool getFinished();

	/// \brief Get the grid representing the maze.
	/// \return The grid representing the maze.
	std::vector<std::vector<CellState>> getGrid();


};

#endif